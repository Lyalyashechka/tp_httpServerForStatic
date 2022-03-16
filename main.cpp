#include <iostream> 
#include "server.h"
#include <unistd.h>


int main () {
    char tmp[256];
    getcwd(tmp, 256);
    std::cout << "Current working directory: " << tmp << std::endl;
    Server server;
    struct sockaddr_in addr;

	addr.sin_family = AF_INET; 
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(80); 

    if (server.Start(addr) < 0) {
        log_error("Error start server");
        exit(-1);
    };
    server.WaitAccept();
    std::cout << "hello world";
}