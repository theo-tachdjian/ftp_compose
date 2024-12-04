#include <iostream>
#include <stdexcept>
#include <cstring>
#include <unistd.h>

#include <netdb.h>
#include <arpa/inet.h>

#include "../include/LPTF_Net/LPTF_Socket.hpp"
#include "../include/LPTF_Net/LPTF_Utils.hpp"
#include "../include/client_actions.hpp"

#include <filesystem>

using namespace std;

namespace fs = std::filesystem;


void print_help() {
    cout << "Usage:" << endl;
    cout << "\tlpf <username>@<ip>:<port> <command> [args]" << endl;
    cout << endl << "Available Commands:" << endl;
    cout << "\t-upload <file> <path>" << endl;
    cout << "\t-download <file>" << endl;
    cout << "\t-delete <file>" << endl;
    cout << "\t-list <path>" << endl;
    cout << "\t-create <folder>" << endl;
    cout << "\t-rm <folder>" << endl;
    cout << "\t-rename <name> <folder>" << endl;
    cout << "\t-tree" << endl;
}


bool check_command(int argc, char const *argv[]) {
    if (strcmp(argv[2], "-upload") == 0) {
        if (argc < 4)
            return false;
        if (argc > 5) {
            cout << "Too much arguments !" << endl;
            return false;
        } else {
            return true;
        }
    } else if (strcmp(argv[2], "-download") == 0) {
        if (argc < 4)
            return false;
        if (argc != 4) {
            cout << "Too much arguments !" << endl;
            return false;
        } else {
            return true;
        }
    } else if (strcmp(argv[2], "-delete") == 0) {
        if (argc < 4)
            return false;
        if (argc != 4) {
            cout << "Too much arguments !" << endl;
            return false;
        } else {
            return true;
        }
    } else if (strcmp(argv[2], "-list") == 0) {
        if (argc < 3)
            return false;
        if (argc > 4) {
            cout << "Too much arguments !" << endl;
            return false;
        } else {
            return true;
        }
    } else if (strcmp(argv[2], "-create") == 0) {
        if (argc < 4)
            return false;
        if (argc != 4) {
            cout << "Too much arguments !" << endl;
            return false;
        } else {
            return true;
        }
    } else if (strcmp(argv[2], "-rm") == 0) {
        if (argc < 3)
            return false;
        if (argc > 4) {
            cout << "Too much arguments !" << endl;
            return false;
        } else {
            return true;
        }
    } else if (strcmp(argv[2], "-rename") == 0) {
        if (argc <= 4)
            return false;
        if (argc > 5) {
            cout << "Too much arguments !" << endl;
            return false;
        } else {
            return true;
        }
    } else if (strcmp(argv[2], "-tree") == 0) {
        if (argc > 3) {
            cout << "Too much arguments !" << endl;
            return false;
        } else return argc == 3;
    } else {
        cout << "Unknown command !" << endl;
    }

    return false;
}


bool login(LPTF_Socket *clientSocket, string username) {
    // send "login" packet
    LPTF_Packet pckt(LOGIN_PACKET, (void *)username.c_str(), username.size());
    clientSocket->write(pckt);
    // wait for server reply
    pckt = clientSocket->read();

    if (pckt.type() == REPLY_PACKET && get_refered_packet_type_from_reply_packet(pckt) == LOGIN_PACKET) {
        cout << get_reply_content_from_reply_packet(pckt);
        string password;
        cin >> password;
        LPTF_Packet password_packet = LPTF_Packet(MESSAGE_PACKET, (void *)password.c_str(), password.size());
        clientSocket->write(password_packet);
        
        LPTF_Packet auth_reply = clientSocket->read();
        if (auth_reply.type() == REPLY_PACKET && get_refered_packet_type_from_reply_packet(auth_reply) == LOGIN_PACKET) {
            cout << "Login successful." << endl;
            return true;
        } else if (auth_reply.type() == ERROR_PACKET) {
            cout << "Unable to log in: " << get_error_content_from_error_packet(auth_reply) << endl;
        }
    } else if (pckt.type() == MESSAGE_PACKET) {
        cout << (const char *)pckt.get_content();
        string new_password;
        cin >> new_password;
        LPTF_Packet new_password_packet = LPTF_Packet(MESSAGE_PACKET, (void *)new_password.c_str(), new_password.size());
        clientSocket->write(new_password_packet);
        
        LPTF_Packet create_reply = clientSocket->read();
        if (create_reply.type() == REPLY_PACKET && get_refered_packet_type_from_reply_packet(create_reply) == LOGIN_PACKET) {
            cout << "User created and logged in successfully." << endl;
            return true;
        } else if (create_reply.type() == ERROR_PACKET) {
            cout << "Unable to create user: " << get_error_content_from_error_packet(create_reply) << endl;
        }
    } else {
        cout << "Unexpected server packet ! Could not log in !" << endl;
    }

    return false;
}


int main(int argc, char const *argv[]) {
    string username;
    string ip;
    int port;
    
    // print help
    if (argc == 2 && (strcmp(argv[1], "-help") == 0 || strcmp(argv[1], "--help") == 0)) {
        print_help();
        return 0;
    } else if (argc < 3) {
        cout << "Too few arguments !" << endl;
        print_help();
        return 2;
    }

    string serv_arg = argv[1];
    size_t user_sep_index = serv_arg.find('@');

    if (user_sep_index == string::npos) {
        cout << "Server address is wrong !" << endl;
        print_help();
        return 2;
    }

    size_t ip_sep_index = serv_arg.find(':', user_sep_index);

    if (ip_sep_index == string::npos) {
        cout << "Server address is wrong !" << endl;
        print_help();
        return 2;
    }
    
    username = serv_arg.substr(0, user_sep_index);
    ip = serv_arg.substr(user_sep_index+1, ip_sep_index-user_sep_index-1);
    port = atoi(serv_arg.substr(ip_sep_index+1, serv_arg.size()).c_str());

    // FIXME check for ip and port later
    if (username.size() == 0) {
        cout << "Username is wrong !" << endl;
        print_help();
        return 2;
    }

    if (ip.size() == 0)
        ip = "127.0.0.1";
    if (port == 0)
        port = 12345;

    // resolve address
    struct hostent *he = gethostbyname(ip.c_str());
    if (he == NULL) {
        cerr << "Unable to resolve host address: " << ip << endl;
        return 2;
    }

    ip = string(inet_ntoa(*(struct in_addr*)he->h_addr_list[0]));

    cout << "Username: " << username << ", IP: " << ip << ", Port: " << port << endl;

    // check if command + args are valid before connecting to the server
    if (!check_command(argc, argv)) {
        print_help();
        return 2;
    }

    try {
        LPTF_Socket clientSocket = LPTF_Socket();

        struct sockaddr_in serverAddr;
        memset(&serverAddr, 0, sizeof(serverAddr));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = inet_addr(ip.c_str());
        serverAddr.sin_port = htons(port);

        clientSocket.connect(reinterpret_cast<struct sockaddr *>(&serverAddr), sizeof(serverAddr));

        // if login failed
        if (!login(&clientSocket, username)) {
            clientSocket.close();
            return 1;
        }

        if (strcmp(argv[2], "-upload") == 0) {

            string file = argv[3];
            string outfile;

            if (argc == 5) {
                // compose server path
                outfile = fs::path(argv[4]) / fs::path(argv[3]).filename();
            } else {
                // upload to root dir
                outfile = fs::path(argv[3]).filename();
            }

            cout << "Uploading File " << file << " as " << outfile << endl;

            return !upload_file(&clientSocket, outfile, file);

        } else if (strcmp(argv[2], "-download") == 0) {

            string file = argv[3];

            return !download_file(&clientSocket, file);

        } else if (strcmp(argv[2], "-delete") == 0) {

            string file = argv[3];

            return !delete_file(&clientSocket, file);

        } else if (strcmp(argv[2], "-list") == 0) {
            
            string path = "";

            if (argc == 4)
                path = argv[3];

            return !list_directory(&clientSocket, path);

        } else if (strcmp(argv[2], "-create") == 0) {

            string folder = argv[3];

            return !create_directory(&clientSocket, folder);
        } else if (strcmp(argv[2], "-rm") == 0) {
            
            string folder = "";     // rm on user root is allowed

            if (argc == 4)
                folder = argv[3];

            return !remove_directory(&clientSocket, folder);
        } else if (strcmp(argv[2], "-rename") == 0) {

            string newname = argv[3];
            string path = argv[4];

            return !rename_directory(&clientSocket, newname, path);
        } else if (strcmp(argv[2], "-tree") == 0) {

            return !list_tree(&clientSocket);
        }

    } catch (const exception &ex) {
        cerr << "Exception: " << ex.what() << endl;
        return 1;
    }

    return 0;
}
