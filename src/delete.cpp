#include <iostream>

#include <windows.h>
#include <fstream>

int main(){
    std::ifstream ifs ("./all_files.txt");

    if (ifs.is_open()){
        std::string path;
        
        while (std::getline(ifs, path)){
            std::cout << "Deleting path : " << path << "\n";
            std::remove(path.c_str());
        }

    } else {
        std::cout << "Failed to open reference file : " << "./all_files.txt";
    }

    ifs.close();
    std::remove("./all_files.txt");
}