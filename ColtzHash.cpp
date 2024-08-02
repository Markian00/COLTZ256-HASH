
#include <iomanip>
#include <boost/thread.hpp>
#include "ColtzHash.h"

std::vector<uint8_t> SECTIONHASH = std::vector<uint8_t>(32);
boost::mutex* SHLOCK = new boost::mutex();
boost::mutex* COMPLETIONLOCK = new boost::mutex();
boost::mutex* CREATELOCK = new boost::mutex();
int threadsComplete = 0;
int threadNum = 0;
boost::condition_variable* CVCREATE = new boost::condition_variable();
boost::condition_variable* CVCOMPLETE = new boost::condition_variable();

std::string coltz256Hash(std::string input) {

    //Stage 1: Input Formatting
    //Break input up into 32 sections that can each be interpreted as 8-bit integers.
    //Integer overflow is intentional, common with hashing functions
    size_t totalLength = input.length();

    while (totalLength < 32){
        input.append(input);
        totalLength = input.length();
    }

    std::vector<uint64_t> sectionVal = std::vector<uint64_t>(32);
    int curr_ind = 0;
    for (size_t i = 0; i < input.length(); i++){
        if (curr_ind < 32){
            sectionVal[curr_ind] += input[i];
            curr_ind++;
        }
        else{
            curr_ind = 0;
        }
    }

    //Stage 2: Computing
    //We have summed the characters of each of the 32 substrings of the input, now we hash
    boost::unique_lock crl(*CREATELOCK);
    for (int h = 0; h < 32; h++){
        int oldthread = 0;
        boost::thread t(runCollatz, sectionVal[h]);
        t.detach();
        do{
            CVCREATE->wait(crl);
        } while (oldthread == threadNum);

    }
    crl.unlock();

    //Stage 2.5: Await completion of operations by other threads
    boost::unique_lock cl(*COMPLETIONLOCK);
    while(threadsComplete != 32){
        CVCOMPLETE->wait(cl);
    }
    cl.unlock();

    //Stage 3: Output Formatting
    //Now that we have the values, we will combine them into a single number and represent it in hex format
    // before returning a string containing it.
    std::stringstream output;
    for (int h = 0; h < 32; h++){
        output << std::setw(2) << std::setfill('0') << std::hex << int(SECTIONHASH[h]);
    }
    return output.str();

}

void runCollatz(uint64_t value){
    uint8_t hash = 0;
    CREATELOCK->lock();
    int threadn = threadNum;
    threadNum++;
    CVCREATE->notify_all();
    CREATELOCK->unlock();

    while (value > 1){
      if (value % 2 == 0){
          value = value/2;
          hash++;
      }
      else{
          value = value * 3 + 1;
          hash++;
          hash++;
      }

    }
    SHLOCK->lock();
    SECTIONHASH[threadn] = hash;
    SHLOCK->unlock();
    COMPLETIONLOCK->lock();
    threadsComplete += 1;
    if (threadsComplete == 32){
        CVCOMPLETE->notify_all();
    }
    COMPLETIONLOCK->unlock();
}
