#include <iostream>
#include <pqxx/pqxx>
#include <ctime>
#include <sstream>

void send_result(pqxx::connection connection, std::string name,bool ok){
    pqxx::work transaction(connection);
    std::ostreamstring format;
    format << "INSERT INTO tests(name, timestamp, result) VALUES (" << name << ", " << time(0) << ", " << static_cast<int>(ok) << ");";
    pqxx::result result = transaction.exec(format.str());
}

void testBasic(pqxx::connection connection) {
    char a = 2;
    char b = 3;
    send_result(connection, "testBasic", a+b==5);
}

int main() {
    try {
        const char* db_host = std::getenv("DB_ADDR");
        const char* db_port = std::getenv("DB_PORT");
        const char* db_name = std::getenv("DB_NAME");
        const char* db_user = std::getenv("DB_USER");
        const char* db_password = std::getenv("DB_PASSWD");

        std::string connection_string = 
            "host=" + std::string(db_host) +
            " port=" + std::string(db_port) +
            " dbname=" + std::string(db_name) +
            " user=" + std::string(db_user) +
            " password=" + std::string(db_password);
    
        pqxx::connection connection(connection_string);

        testBasic(connection);

    } catch (const std::exception &e) {
        std::cerr << "Erreur : " << e.what() << std::endl;
        return 1;
    }
    connection.disconnect();
    return 0;
}
