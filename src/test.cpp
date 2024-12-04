#include "../include/file_utils.hpp"
#include <iostream>
#include <fstream>

#include <filesystem>

#include <vector>
#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>

#include "../include/logger.hpp"

using namespace std;

namespace fs = std::filesystem;


int main()
{
    fs::path folder (get_user_root("Erwan"));

    int len = folder.string().size();

    for (fs::directory_entry const& dir_entry : fs::recursive_directory_iterator(folder)) {
        cout << (const char *)(dir_entry.path().string().c_str() + len+1);
        if (fs::is_directory(dir_entry)) cout << dir_entry.path().preferred_separator;
        cout << endl;
    }

    // Logger logger ("test-log.txt");

    // logger.info("This is a log");
    // logger.warn("Client sent wrong packet");
    // logger.debug("Deeeeebugging");
    // logger.error("Error !!!");

    // fs::path folder = get_user_root("TESTUSER");
    // fs::path folder2 = get_user_root("TESTUSER");

    // folder2 /= "a";

    // cout << "Relative paths: " << fs::relative(folder2, folder) << endl;
    // cout << "Is " << folder2 <<" in " << folder << ": " << is_path_in_folder(folder2, folder) << endl;

    // folder2 = folder;
    // folder2 /= "file.txt";

    // cout << "Relative paths: " << fs::relative(folder2, folder) << endl;
    // cout << "Is " << folder2 <<" in " << folder << ": " << is_path_in_folder(folder2, folder) << endl;

    // fs::path uroot = get_user_root("TESTUSER");

    // cout << "fs::exists(uroot): " << fs::exists(uroot) << endl;
    // cout << "fs::is_directory(uroot): " << fs::is_directory(uroot) << endl;

    // fs::path filepath = uroot;
    // filepath /= "test-out.bin";

    // cout << "filepath: " << filepath<<endl;

    // ofstream outfile;
    // outfile.open(filepath, ios::binary | ios::out);

    // cout << "outfile open: " << outfile.is_open() << endl;
    // cout << "outfile tellp: " << outfile.tellp() << endl;

    // outfile.write("abc!", 4);

    // outfile.close();

    // string path = "server_root/Erwan/hello.txt";
    // cout << path << " size: " << get_file_size(path) << endl;

    // fs::path fspath = ("server_root/Erwan/hello.txt");
    // cout << path << " size: " << get_file_size(fspath) << endl;

    // cout << "filepath.native(): "<< filepath.native() << endl;

    // filepath.append("abc");
    // cout << "filepath.append(\"abc\"): " << filepath << endl;

    // fs::path erwan_path = get_user_root("Erwan");
    // cout << erwan_path << endl;
    // erwan_path /= "";
    // cout << erwan_path << endl;
    // // erwan_path /= "MyFolder";
    // // cout << erwan_path << endl;

    // const char *entry_prefix[] = {
    //     "<FILE>\t",
    //     "<DIR>\t"
    // };

    // cout << "iterator on folder Erwan:" << endl;

    // for (auto const& dir_entry : fs::directory_iterator{erwan_path}) {
    //     if (fs::is_directory(dir_entry)) {
    //         cout << entry_prefix[fs::is_directory(dir_entry)] << dir_entry.path().stem().string() << ", " << dir_entry.path() << endl;
    //     } else {
    //         cout << entry_prefix[fs::is_directory(dir_entry)] << dir_entry.path().filename().string() << ", " << dir_entry.path() << endl;
    //     }
    // }

    // cout << "Directory contents from file_utils:" << endl;
    // cout << list_directory_content(erwan_path) << endl;

    return 0;
}
