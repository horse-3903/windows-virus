#include <iostream>

#include <algorithm>
#include <vector>
#include <string>

#include <fstream>
#include <filesystem>
#include <windows.h>

#include <sys/stat.h>

#include "util.cpp"
#include "file_op.cpp"
#include "content.cpp"

int main(){
    const std::string name = "3eb41f79481d39b1d85de0b546ef209b"; // change to random
    const std::string content = "e8aa5769216a6823d8216d8df2696677"; // change to random
    const std::string default_path = "C:/"; // CHANGE BEFORE COMMIT 

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
        std::vector<std::string> directories;

        directories = find_directories(current_path);

        if (directories.empty()){
            current_path = default_path;
            continue;
        }

        // generate random directory path
        std::string new_path;

         try {
            new_path = random_directory(directories);
        } catch (std::length_error) {
            std::cout << "boo 2" << "\n";
            return -1;
        }

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
        
        bool choice = 1; // rand_int(0, 2);
        
        if (!choice){
            // ignore directory and continue
            last_path = current_path;
        } else if (choice == 1){
            // create files in directory
            int num_files = rand_int(1, 20);
            std::vector<std::string> files = create_files(current_path, generate_content(100), generate_content(rand_int(100, 100000)), num_files);

            all_files.insert(all_files.end(), files.begin(), files.end());

            last_path = current_path;
        } else if (choice == 2){
            // reset to default path
            last_path = default_path;
        }
    }

    std::ofstream ofs("./all_files.txt");

    if (ofs.is_open()){
        for (int i = 0; i < all_files.size(); i++){
            ofs << all_files[i] << "\n";
        }
    }

    ofs.close();

    return 0;
}