#include <iostream>

#include <string>

std::string generate_content(long long size){
    std::string content;

    for (long long i = 0; i < size; i++){
        content += std::string(1, (char) (rand_int(32, 126)));
    }

    return content;
}