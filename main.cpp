#include <iostream> 
#include "server.h"
#include <unistd.h>
#include <fstream>

const std::string configPath = "../httpd.conf";

Config ParseConfig(const std::string& path) {
    Config result;

    std::ifstream conf(path);
    std::string buf1, buf2;

    conf >> buf1 >> result.threadLimit >> buf2 >> result.documentRoot;

    conf.close();

    return result;
}

int main () {
    char tmp[256];
    getcwd(tmp, 256);
    std::cout << "Current working directory: " << tmp << std::endl;

    Config conf = ParseConfig(configPath);

    Server server(conf);
    struct sockaddr_in addr;

	addr.sin_family = AF_INET; 
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(80);

    std::cout << "Count thread: " << conf.threadLimit << "\n" <<conf.documentRoot;

    if (server.Start(addr) < 0) {
        log_error("Error start server");
        exit(-1);
    };
    server.WaitAccept();
    std::cout << "hello world";
}