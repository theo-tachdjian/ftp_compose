#include "../include/logger.hpp"

#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>

#include "../include/file_utils.hpp"

using namespace std;

Logger::Logger() {
    size_limit = LOG_DEFAULT_SIZE_LIMIT;
    filename = "log.txt";
    log_file = ofstream(filename, ios::app);
    if (!log_file.is_open()) throw runtime_error("Could not open log file !");
}

Logger::Logger(const string &filename): filename{ filename } {
    size_limit = LOG_DEFAULT_SIZE_LIMIT;
    log_file = ofstream(filename, ios::app);
    if (!log_file.is_open()) throw runtime_error("Could not open log file !");
}

Logger::Logger(const string &filename, unsigned int size_limit = LOG_DEFAULT_SIZE_LIMIT): size_limit{ size_limit }, filename{ filename } {
    log_file = ofstream(filename, ios::app);
    if (!log_file.is_open()) throw runtime_error("Could not open log file !");
}

Logger::~Logger() {
    log_file.close();
}


void Logger::check_purge() {
    if (log_file.is_open() && get_file_size(filename) > size_limit) {
        cout << "Removing log file " << filename << endl;

        log_file.close();
        fs::remove(filename);
        log_file = ofstream(filename, ios::app);

        if (!log_file.is_open()) throw runtime_error("Could not open log file !");
    }
}


void Logger::log(const string &level, const string &message) {
    check_purge();

    time_t now = time(0);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));

    ostringstream line;
    line << "[" << timestamp << "] " << level << ": " << message;

    cout << line.str() << endl;

    if (log_file.is_open()) {
        log_file << line.str() << endl;
        log_file.flush();
    }
}

void Logger::info(const string &message) { log("INFO", message); }
void Logger::info(const ostringstream &message) { log("INFO", message.str()); }
void Logger::debug(const string &message) { log("DEBUG", message); }
void Logger::debug(const ostringstream &message) { log("DEBUG", message.str()); }
void Logger::warn(const string &message) { log("WARN", message); }
void Logger::warn(const ostringstream &message) { log("WARN", message.str()); }
void Logger::error(const string &message) { log("ERROR", message); }
void Logger::error(const ostringstream &message) { log("ERROR", message.str()); }



void log_info(ostringstream &msg, Logger *logger) {
    if (logger) logger->info(msg);
    else cout << msg.str() << endl;
}
void log_info(const string &msg, Logger *logger) {
    if (logger) logger->info(msg);
    else cout << msg << endl;
}

void log_debug(ostringstream &msg, Logger *logger) {
    if (logger) logger->debug(msg);
    else cout << msg.str() << endl;
}
void log_debug(const string &msg, Logger *logger) {
    if (logger) logger->debug(msg);
    else cout << msg << endl;
}

void log_warn(ostringstream &msg, Logger *logger) {
    if (logger) logger->warn(msg);
    else cout << msg.str() << endl;
}
void log_warn(const string &msg, Logger *logger) {
    if (logger) logger->warn(msg);
    else cout << msg << endl;
}

void log_error(ostringstream &msg, Logger *logger) {
    if (logger) logger->error(msg);
    else cerr << msg.str() << endl;
}
void log_error(const string &msg, Logger *logger) {
    if (logger) logger->error(msg);
    else cerr << msg << endl;
}
