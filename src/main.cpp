#include <iostream>

#include <algorithm>
#include <vector>
#include <string>

#include <fstream>
#include <filesystem>
#include <windows.h>

#include <sys/stat.h>

#include <typeinfo>

#include "util.cpp"

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
    if (!valid_directories.empty()){
        return valid_directories[rand_int(0, valid_directories.size())] + "/";
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

int main(){
    const std::string name = "3eb41f79481d39b1d85de0b546ef209b"; // change to random
    const std::string content = "e8aa5769216a6823d8216d8df2696677"; // change to random
    const std::string default_path = "./GitHub/windows-virus/test/";

    std::vector<std::string> all_files;

    std::string current_path = default_path;
    std::string last_path = default_path;

    struct stat sb;
    bool exist;

    // create default directory if not exists
    if (stat(default_path.c_str(), &sb) == 0){
        exist = true;
    } else if (sb.st_mode & S_IFDIR){
        exist = false;
    }
    
    if (!exist){
        std::cout << "Error finding directory : " << default_path << "\n";
        std::cout << "Creating test directory" << "\n";

        mkdir(default_path.c_str());

        for (int i = 0; i < 5; i++){
            std::string new_parent_path = default_path + std::to_string(i) + "/";
            std::cout << "Creating test directory : " << new_parent_path << "\n";
            mkdir(new_parent_path.c_str());
            for (int j = 0; j < 10; j++){
                std::string new_child_path = new_parent_path + std::string(1, (char) (j + 97)) + "/";
                std::cout << "Creating test directory : " << new_child_path << "\n";
                mkdir(new_child_path.c_str());
            }
        }
    }

    for (int i = 0; i < 100; ++i){
        // find directories in current path
        std::vector<std::string> directories = find_directories(current_path);

        if (directories.empty()){
            current_path = default_path;
            continue;
        }

        // generate random directory path
        std::string new_path = random_directory(directories);

        if (new_path.empty()){
            // check if directories exist
            current_path = default_path;
            continue;
        } else if (new_path == last_path){
            // check if directory repeated
            current_path = default_path;
        } else {
            current_path = new_path;
        }

        std::cout << "Selected path : " << current_path << "\n";

        std::cout << "womp" << "\n";
        
        bool choice = rand_int(0, 2);
        
        if (!choice){
            // ignore directory and continue
            last_path = current_path;
        } else if (choice == 1){
            // create files in directory
            int num_files = rand_int(1, 20);
            std::vector<std::string> files = create_files(current_path, name, content, num_files);

            std::cout << "womp womp" << "\n";
            all_files.insert(all_files.end(), files.begin(), files.end());
            std::cout << "womp womp womp" << "\n";

            last_path = current_path;
        } else if (choice == 2){
            // reset to default path
            last_path = default_path;
        }
    }

    std::ofstream ofs;
    ofs.open("./all_files.txt");

    if (ofs.is_open()){
        for (auto file: all_files){
            ofs << file << "\n";
        }
    }

    return 0;
}