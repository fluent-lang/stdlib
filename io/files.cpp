/*
    These files are part of the Surf's standard library.
    They're bundled with the main program by the compiler
    which is then converted to machine code.

    -----
    License notice:

    This code is released under the GNU GPL v3 license.
    The code is provided as is without any warranty
    Copyright (c) 2024 Rodrigo R. & all Surf contributors
*/

#include "files.hpp"

#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <vector>
#include <dirent.h>
#include <filesystem>
#include "../lang/result.hpp"
#include "../lang/err.hpp"
#include "../lang/string.hpp"
#include "../lang/opt.hpp"

using namespace std;

Result<bool, GenericErr> write_file(const char* path, const char* content) {

    // First check if the file exists
    if (!file_exists(path).unwrap()) {
        return Result(false, Optional<GenericErr>(GenericErr("File does not exist")));
    }

    // Open the file
    ofstream file;
    file.open(path);

    // Something went wrong
    if (!file.is_open()) {
        return Result(false, Optional<GenericErr>(GenericErr("Failed to create file")));
    }

    // Directly write the content to the file
    file << content;

    // Don't forget to close the file!
    file.close();

    return Result<bool, GenericErr>(true, None<GenericErr>());

}

Result<String, GenericErr> read_file(const char* path) {

    // First check if the file exists
    if (!file_exists(path).unwrap()) {
        return Result(String(""), Optional<GenericErr>(GenericErr("File does not exist")));
    }

    // Open the file
    ifstream file;
    file.open(path);

    if (!file.is_open()) {
        return Result<String>(String(""), Optional<GenericErr>(GenericErr("Failed to open file")));
    }

    string content;
    string line;

    // Read line by line
    while (getline(file, line)) {
        content += line + "\n";
    }

    // Don't forget to close the file!
    file.close();

    return Result<String, GenericErr>(String(content.c_str()), None<GenericErr>());
}

Result<bool, GenericErr> delete_file(const char* path) {
    
    // First check if the file exists
    if (!file_exists(path).unwrap()) {
        return Result(false, Optional<GenericErr>(GenericErr("File does not exist")));
    }

    // Remove the file
    if (remove(path) != 0) {
        return Result(false, Optional<GenericErr>(GenericErr("Failed to delete file")));
    }

    return Result<bool, GenericErr>(true, None<GenericErr>());

}

Result<Vec<String>, GenericErr> walk_dir(const char* path) {

    // First check if the file exists
    if (!file_exists(path).unwrap()) {
        return Result(Vec<String>(), Optional<GenericErr>(GenericErr("File does not exist")));
    }

    // Check if it's a directory
    if (!is_dir(path).unwrap()) {
        return Result(
            Vec<String>(),
            Optional<GenericErr>(GenericErr("Path is not a directory"))
        );
    }

    // Open the directory
    DIR* dir = opendir(path);

    if (dir == NULL) {
        return Result(
            Vec<String>(),
            Optional<GenericErr>(GenericErr("Failed to open directory"))
        );
    }

    Vec<String> files;

    // Read the directory
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        files.push(entry->d_name);
    }

    // Close the directory
    closedir(dir);

    return Result<Vec<String>, GenericErr>(move(files), None<GenericErr>());

}

Result<bool, GenericErr> file_exists(const char* path) {

    // Check if the file exists
    if (filesystem::exists(path)) {
        return Result<bool, GenericErr>(true, None<GenericErr>());
    }

    return Result<bool, GenericErr>(false, None<GenericErr>());

}

Result<bool, GenericErr> is_dir(const char* path) {

    // First check if the file exists
    if (!file_exists(path).unwrap()) {
        return Result(false, Optional<GenericErr>(GenericErr("File does not exist")));
    }

    // Check if the path is a directory
    if (filesystem::is_directory(path)) {
        return Result<bool, GenericErr>(true, None<GenericErr>());
    }

    return Result<bool, GenericErr>(false, None<GenericErr>());

}   

Result<bool, GenericErr> remove_dir(const char* path) {

    // Remember that rmdir from unistd.h only works for empty directories
    // To fix that while still maintaning performance, we can use a queue
    // which has a complexity of O(n) instead of O(n^2) from the recursive approach

    Vec<String> queue = Vec<String>();
    queue.push(path);

    while (!queue.is_empty()) {
        // Get always the first element
        String current_path = queue.at(0).unwrap();
        Result<bool> is_dir_result = is_dir(current_path.to_data());

        // Cannot read the directory -> Return the error without crashing
        if (is_dir_result.has_error()) {
            return Result<bool, GenericErr>(false, Optional<GenericErr>(is_dir_result.get_error()));
        }

        if (is_dir_result.unwrap()) {
            // See if the directory is empty
            Result<Vec<String>> files = walk_dir(current_path.to_data());

            // Cannot read the directory -> Return the error without crashing
            if (files.has_error()) {
                return Result<bool, GenericErr>(false, Optional<GenericErr>(files.get_error()));
            }

            Vec<String> files_vec = files.unwrap();

            // If the directory is empty, remove it
            if (files_vec.length() == 2) {
                if (rmdir(current_path.to_data()) != 0) {
                    return Result<bool, GenericErr>(false, Optional<GenericErr>(GenericErr("Failed to delete directory")));
                }
            } else {
                // Add all the files to the queue
                for (const String& file : files_vec) {
                    if (file.compare_raw(".") && file.compare_raw("..")) {
                        queue.push(
                            current_path.join("/")
                                .join(file)
                        );
                    }
                }

                // Add the directory to the end of the queue
                // After all files are deleted, the directory should be now empty
                queue.push(current_path);
            }
        } else {
            // Try to remove the file
            Result<bool, GenericErr> delete_result = delete_file(current_path.to_data());

            // Cannot delete the file -> Return the error without crashing
            if (delete_result.has_error()) {
                return Result<bool, GenericErr>(false, Optional<GenericErr>(delete_result.get_error()));
            }
        }

        // Pop the first element
        queue.shift(1);
    }

    return Result<bool, GenericErr>(true, None<GenericErr>());
}