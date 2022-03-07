#include <iostream> 
#include "server.h"


int main () {

    Server server;
    struct sockaddr_in addr;

	addr.sin_family = AF_INET; 
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(8084); 

    if (server.Start(addr) < 0) {
        log_error("Error start server");
        exit(-1);
    };
    server.WaitAccept();
    std::cout << "hello world";
}