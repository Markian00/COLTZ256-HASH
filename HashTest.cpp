#include "ColtzHash.h"
#include <iostream>
#include <fstream>

int main(int argc, char * argv[]) {
    if (argc != 2){
        std::cout << "Usage: ./hash <filename>" << std::endl;
        exit(1);
    }
    else{
        std::ifstream file;
        file.open(argv[1]);
        if (!file.is_open()){
            std::cout << "Error Reading File: " << argv[1] << std::endl;
            exit(1);
        }
        std::string input_total;
        std::string input;
        std::cout << "Input:" << std::endl;
        while(std::getline(file, input, '\n')){
            std::cout << input << std::endl;
            input_total.append(input);
        }
        std::cout << "Hash:" << std::endl;
        std::cout << coltz256Hash(input_total) << std::endl;
        file.close();
    }
}