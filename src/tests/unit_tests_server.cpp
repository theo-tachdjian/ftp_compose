#include <iostream>
#include <ctime>
#include <pqxx/pqxx>


void send_result(pqxx::connection &cx, std::string name,bool ok) {
    pqxx::work transaction(cx);
    pqxx::result result = transaction.exec("INSERT INTO tests(name, timestamp, result) VALUES ($1, $2, $3)", pqxx::params{name, time(0), static_cast<int>(ok)});
    transaction.commit();
}

bool testBasic() {
    char a = 2;
    char b = 3;
    return a+b==5;
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
    
        pqxx::connection cx(connection_string);

        // run tests
        send_result(cx, "testBasic", testBasic());

        cx.close();

    } catch (const std::exception &e) {
        std::cerr << "Error when running tests : " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
