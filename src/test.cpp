#include <iostream>
#include <string>
#include <stdlib.h>

int main(){
    std::string command = "python -u util.py";
    std::system(command.c_str());

    std::cout << "a" << std::endl;
}