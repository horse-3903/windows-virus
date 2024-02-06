#include <iostream>
#include <cstdlib>
#include <ctime>
#include <experimental/random>

#include <string>
#include <vector>

#include <fstream>
#include <filesystem>
#include <direct.h>
#include <Windows.h>

std::vector<std::string> find_dir(const std::string path){
    std::vector<std::string> dir;

    // if (path)

    for (auto const &entry : std::filesystem::directory_iterator(path)){
        dir.push_back(entry.path().string());
    }

    return dir;
}

std::string random_path(const std::vector<std::string> dir){
    std::experimental::reseed();

    return dir[std::experimental::randint(0, (int) dir.size()-1)];
}

int main(){
    std::string path = "C:";
    std::string name = "3eb41f79481d39b1d85de0b546ef209b";
    std::string content = "e8aa5769216a6823d8216d8df2696677";
    
    for (int i = 0; i < 100; i++){
        std::srand(std::rand());
        bool stop = std::rand() % 2;

        path = random_path(find_dir(path + "\\"));
        // std::ofstream ofs;

        // ofs.open(path)
        std::cout << path << std::endl;
    }
    
    // for (int i = 0; i < 1000; i++){
    //     h++;
    //     std::ofstream Virus; 
    //     std::cout << path + std::to_string(h) + ".txt" << std::endl;
    //     Virus.open(path + std::to_string(h) + ".txt", std::ios_base::out);
    //     Virus << str;
    //     Virus.close();
    // }
}