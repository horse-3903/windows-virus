# windows-virus

This project is a simple virus (without FreeConsole) implemented in C++. It creates a directory structure and generates random files within those directories based on specified parameters.

### Files and their functionalities:

1. **main.cpp**: This is the main file that orchestrates the entire process. It creates a directory structure, selects random directories, and generates files within them.

2. **util.cpp**: This file contains utility functions used in the project, such as generating random integers within a specified range.

3. **file_op.cpp**: It includes functions for file operations, such as finding directories, choosing random directories, and creating files with random content within those directories.

4. **content.cpp**: This file contains a function to generate random content for the files.

5. **delete.cpp**: It includes a simple program to delete all files listed in a reference file (`all_files.txt`).

### How to Use:

1. **Compilation**: Compile the project using a C++ compiler such as g++:

    ```bash
    g++ main.cpp -o random_file_generator
    ```

2. **Execution**: Run the compiled program:

    ```bash
    ./random_file_generator
    ```

3. **Customisation**: Modify the parameters in `main.cpp` such as `name`, `content`, and `default_path` according to your requirements.

4. **Cleanup**: To delete all generated files, compile and run `delete.cpp`.

### Notes:

- Make sure to customise the `name`, `content`, and `default_path` variables in `main.cpp` before running the program.
- The program creates a directory structure and generates files with random content within those directories.
- Directories are chosen randomly, and files are created with random content.
- The `all_files.txt` file contains a list of all generated files for reference.
- Use caution when running the program as it creates a large number of files.
