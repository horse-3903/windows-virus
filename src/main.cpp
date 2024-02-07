#include <iostream>

#include <algorithm>
#include <vector>
#include <string>

#include <fstream>
#include <filesystem>
#include <sys/stat.h>

#include <random>

// find directories in the specified path
std::vector<std::string> find_directories(const std::string& path) {
    std::vector<std::string> directories;
    try {
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            directories.push_back(entry.path().string());
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cout << "Error accessing directory : " << path << "\n";
    }
    return directories;
}

// choose a random directory path from the provided list
std::string random_directory(const std::vector<std::string>& directories) {
    std::vector<std::string> valid_directories;

    // filter valid directories
    std::copy_if(
        directories.begin(), 
        directories.end(), 
        std::back_inserter(valid_directories),
        [] (const std::string& p) {
            return p.find('.') == std::string::npos || p.find('.') == 0;
        }
    );

    // randomly choose a valid directory path
    if (!valid_directories.empty()) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(0, static_cast<int>(valid_directories.size()) - 1);
        return valid_directories[dist(gen)] + "\\";
    }

    return "";
}

// create files in the specified directory
void create_files(const std::string& directory, const std::string& name, const std::string& content, int num_files) {
    for (int i = 0; i < num_files; ++i) {
        std::string file_path = directory + name + "_" + std::to_string(i) + ".txt";
        std::ofstream ofs;

        ofs.open(file_path);


        if (ofs.is_open()) {
            ofs << content;
            std::cout << "File created : " << file_path << "\n";
        } else {
            std::cout << "Error creating file : " << file_path << "\n";
        }
    }
}

int main() {
    const std::string name = "3eb41f79481d39b1d85de0b546ef209b"; // change to random
    const std::string content = "e8aa5769216a6823d8216d8df2696677"; // change to random
    const std::string default_path = "C:\\Users\\chong\\Desktop\\Coding\\GitHub\\windows-virus\\test\\";
    const int num_files = 1000;

    std::string current_path = default_path;
    std::string last_path = default_path;

    struct stat sb;
    bool exist;

    // create default directory if not exists
    if (stat(default_path.c_str(), &sb) == 0){
        exist = false;
    } else if (sb.st_mode & S_IFDIR){
        exist = true;
    } else {
        exist = false;
    }
    
    if (!exist){
        std::cout << "Error finding directory : " << default_path << "\n";
    }

    for (int i = 0; i < 100; ++i) {
        // find directories in current path
        std::vector<std::string> directories = find_directories(current_path);

        if (directories.empty()) {
            continue;
        }

        // generate random directory path
        std::string new_path = random_directory(directories);

        if (new_path.empty()) {
            continue;
        }

        // new path same as last path, reset to default path
        if (new_path == last_path) {
            current_path = default_path;
        } else {
            current_path = new_path;
        }

        std::cout << "Selected path : " << current_path << "\n";
        
        if (){
            // create files in directory
            create_files(current_path, name, content, num_files);
        }

        // update last path
        last_path = current_path;
    }

    return 0;
}