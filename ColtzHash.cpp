
#include <iomanip>
#include "ColtzHash.h"

std::string coltz256Hash(std::string input) {

    //Stage 1: Input Formatting
    //Break input up into 32 sections that can each be interepreted as 8-bit integers.
    //Integer overflow is intentional, common with hashing functions
    size_t totalLength = input.length();

    while (totalLength < 32){
        input.append(input);
        totalLength = input.length();
    }
    size_t sectionLength = totalLength / 32;
    size_t partialLength = totalLength % 32;

    std::vector<uint64_t> sectionVal = std::vector<uint64_t>(32);
    int counter = 0;
    int curr_ind = 0;
    for (size_t i = 0; i < input.length(); i++){
        if (counter < sectionLength){
            sectionVal[curr_ind] += input[i];
            counter++;
        }
        else if (counter == sectionLength){
            if (partialLength > 0){
                sectionVal[curr_ind] += input[i];
                partialLength--;
            }
            curr_ind++;
            counter = 0;
        }
    }

    //Stage 2: Computing
    //We have summed the characters of each of the 32 substrings of the input, now we hash

    std::vector<uint8_t> sectionHash = std::vector<uint8_t>(32);
    for (int h = 0; h < 32; h++){
        sectionHash[h] = runCollatz(sectionVal[h]);
    }

    //Stage 3: Output Formatting
    //Now that we have the values, we will combine them into a single number and represent it in hex format
    // before returning a string containing it.
    std::stringstream output;
    for (int h = 0; h < 32; h++){
        output << std::setw(2) << std::setfill('0') << std::hex << int(sectionHash[h]);
    }

    return output.str();

}

uint8_t runCollatz(uint64_t value){
    uint8_t hash = 0;

    while (value > 1){
      if (value % 2 == 0){
          value = value/2;
      }
      else{
          value = value * 3 + 1;
      }
      hash++;
    }

    return hash;

}
