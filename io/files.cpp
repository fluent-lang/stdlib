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
#include <optional>
#include <filesystem>
#include "../lang/result.hpp"
#include "../lang/err.hpp"

using namespace std;

Result<bool, GenericErr> write_file(const string* path, const string* content) {

    // First check if the file exists
    if (!file_exists(path).unwrap(f, l)) {
        return Result(false, optional<GenericErr>(GenericErr("File does not exist")));
    }

    // Open the file
    ofstream file;
    file.open(*path);

    // Something went wrong
    if (!file.is_open()) {
        return Result(false, optional<GenericErr>(GenericErr("Failed to create file")));
    }

    // Directly write the content to the file
    file << content;

    // Don't forget to close the file!
    file.close();

    return Result<bool, GenericErr>(true, nullopt);

}

Result<string, GenericErr> read_file(const string* path) {

    // First check if the file exists
    if (!file_exists(path).unwrap(f, l)) {
        return Result(string(""), optional<GenericErr>(GenericErr("File does not exist")));
    }

    // Open the file
    ifstream file;
    file.open(*path);

    if (!file.is_open()) {
        return Result<string>("", optional<GenericErr>(GenericErr("Failed to open file")));
    }

    string content;
    string line;

    // Read line by line
    while (getline()) {
        content += line + "\n";
    }

    // Don't forget to close the file!
    file.close();

    return Result<string, GenericErr>(move(content), nullopt);
}

Result<bool, GenericErr> delete_file(const string* path) {
    
    // First check if the file exists
    if (!file_exists(path).unwrap(f, l)) {
        return Result(false, optional<GenericErr>(GenericErr("File does not exist")));
    }

    // Remove the file
    if (remove(path->c_str()) != 0) {
        return Result(false, optional<GenericErr>(GenericErr("Failed to delete file")));
    }

    return Result<bool, GenericErr>(true, nullopt);

}

Result<vector<string>, GenericErr> walk_dir(const string* path) {

    // First check if the file exists
    if (!file_exists(path).unwrap(f, l)) {
        return Result(vector<string>(), optional<GenericErr>(GenericErr("File does not exist")));
    }

    // Check if it's a directory
    if (!is_dir(path).unwrap(f, l)) {
        return Result(
            vector<string>(),
            optional<GenericErr>(GenericErr("Path is not a directory"))
        );
    }

    // Open the directory
    DIR* dir = opendir(path->c_str());

    if (dir == NULL) {
        return Result(
            vector<string>(),
            optional<GenericErr>(GenericErr("Failed to open directory"))
        );
    }

    vector<string> files;

    // Read the directory
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        files.push_back(entry->d_name);
    }

    // Close the directory
    closedir(dir);

    return Result<vector<string>, GenericErr>(move(files), nullopt);

}

Result<bool, GenericErr> file_exists(const string* path) {

    // Check if the file exists
    if (filesystem::exists(*path)) {
        return Result<bool, GenericErr>(true, nullopt);
    }

    return Result<bool, GenericErr>(false, nullopt);

}

Result<bool, GenericErr> is_dir(const string* path) {

    // First check if the file exists
    if (!file_exists(path).unwrap(f, l)) {
        return Result(false, optional<GenericErr>(GenericErr("File does not exist")));
    }

    // Check if the path is a directory
    if (filesystem::is_directory(*path)) {
        return Result<bool, GenericErr>(true, nullopt);
    }

    return Result<bool, GenericErr>(false, nullopt);

}

Result<bool, GenericErr> remove_dir(const string* path) {

    // Remember that rmdir from unistd.h only works for empty directories
    // To fix that while still maintaning performance, we can use a queue
    // which has a complexity of O(n) instead of O(n^2) from the recursive approach

    vector<string> queue = { *path };

    while (!queue.empty()) {
        // Get always the first element
        string* current_path = &queue[0];
        Result<bool> is_dir_result = is_dir(current_path);

        // Cannot read the directory -> Return the error without crashing
        if (is_dir_result.has_error()) {
            return Result<bool, GenericErr>(false, optional<GenericErr>(is_dir_result.get_error(f, l)));
        }

        if (is_dir_result.unwrap(f, l)) {
            // See if the directory is empty
            Result<vector<string>> files = walk_dir(current_path);

            // Cannot read the directory -> Return the error without crashing
            if (files.has_error()) {
                return Result<bool, GenericErr>(false, optional<GenericErr>(files.get_error(f, l)));
            }

            vector<string> files_vec = files.unwrap(f, l);

            // If the directory is empty, remove it
            if (files_vec.size() == 2) {
                if (rmdir(current_path->c_str()) != 0) {
                    return Result<bool, GenericErr>(false, optional<GenericErr>(GenericErr("Failed to delete directory")));
                }
            } else {
                // Add all the files to the queue
                for (const string& file : files_vec) {
                    if (file != "." && file != "..") {
                        queue.push_back(*current_path + "/" + file);
                    }
                }

                // Add the directory to the end of the queue
                // After all files are deleted, the directory should be now empty
                queue.push_back(*current_path);
            }
        } else {
            // Try to remove the file
            Result<bool, GenericErr> delete_result = delete_file(current_path);

            // Cannot delete the file -> Return the error without crashing
            if (delete_result.has_error()) {
                return Result<bool, GenericErr>(false, optional<GenericErr>(delete_result.get_error(f, l)));
            }
        }

        // Pop the first element
        queue.erase(queue.begin());
    }

    return Result<bool, GenericErr>(true, nullopt);
}