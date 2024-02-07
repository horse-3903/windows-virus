#include <iostream>

#include <optional>

#include <cstdlib>
#include <ctime>
#include <experimental/random>

#include <string>
#include <algorithm>
#include <iterator>
#include <vector>

#include <fstream>
#include <filesystem>
#include <direct.h>
#include <Windows.h>

std::vector<std::string> find_dir(const std::string path){
    std::vector<std::string> dir;
    std::filesystem::directory_iterator dir_it;

    try{
        dir_it = std::filesystem::directory_iterator(path);
    } catch (std::filesystem::filesystem_error){
        std::cout << "File Directory '" << path << "' not accessible." << "\n";
        return std::vector<std::string>{};
    }

    for (auto const &entry : dir_it){
        dir.push_back(entry.path().string());
    }

    return dir;
}

std::string random_path(const std::vector<std::string> dir){
    std::vector<std::string> valid_dir;

    std::copy_if(dir.begin(), dir.end(), std::back_inserter(valid_dir), [](std::string p){auto d_it = p.find("."); return (d_it == std::string::npos) || (d_it == 0);});

    std::experimental::reseed();

    if (!valid_dir.size()){
        return "";
    } 

    std::string c_path = valid_dir[std::experimental::randint(0, (int) valid_dir.size()-1)];

    return c_path + "\\";
}

int main(){
    std::string name = "3eb41f79481d39b1d85de0b546ef209b";
    std::string content = "e8aa5769216a6823d8216d8df2696677";

    std::string default_path = "C:\\Users\\chong\\";
    std::string path = default_path;
    std::string last = default_path;
    
    for (int i = 0; i < 1; i++){
        std::srand(std::rand());
        bool stop = std::rand() % 2;
        
        std::vector<std::string> dir = find_dir(path);

        if (!dir.size()){
            continue;
        }
        
        if (!dir.size()){
            path = default_path;
        } else {
            path = random_path(dir);

            if (!path.length()){
                continue;
            }

            if (last == path){
                path = default_path;
            }
        }

        std::cout << path << "\n";

        last = path;

        // std::ofstream ofs;
        // ofs.open(path)
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