#include <iostream>

#include <algorithm>
#include <vector>
#include <string>

#include <fstream>
#include <filesystem>

// find directories in the specified path
std::vector<std::string> find_directories(const std::string& path){
    std::vector<std::string> directories;
    try{
        for (const auto& entry : std::filesystem::directory_iterator(path)){
            directories.push_back(entry.path().string());
        }
    } catch (const std::filesystem::filesystem_error &e){
        std::cout << "Error accessing directory : " << path << "\n";
    }
    return directories;
}

// choose a random directory path from the provided list
std::string random_directory(const std::vector<std::string>& directories){
    std::vector<std::string> valid_directories;

    // filter valid directories
    std::copy_if(
        directories.begin(), 
        directories.end(), 
        std::back_inserter(valid_directories),
        [] (const std::string& p){
            return p.find('.') == std::string::npos || p.find('.') == 0;
        }
    );

    // randomly choose a valid directory path
    std::string chosen_dir;
    
    if (!valid_directories.empty()){
        chosen_dir = valid_directories[rand_int(0, valid_directories.size()-1)] + "/";

        return chosen_dir;
    }

    return "";
}

// create files in the specified directory
std::vector<std::string> create_files(const std::string& directory, const std::string& name, const std::string& content, int num_files){
    std::vector<std::string> all_file_path;
    
    for (int i = 0; i < num_files; ++i){
        std::string file_path = directory + name + "_" + std::to_string(i) + ".txt";
        std::ofstream ofs;

        ofs.open(file_path);

        if (ofs.is_open()){
            ofs << content;
            all_file_path.push_back(file_path);
            std::cout << "File created : " << file_path << "\n";
        } else {
            std::cout << "Error creating file : " << file_path << "\n";
        }
    }

    return all_file_path;
}