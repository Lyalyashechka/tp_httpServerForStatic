#include "server.h"
#include <unistd.h>

#define MAX_SIZE_MESSAGE 10'000

Server::Server() 
{
    _socket = socket(AF_INET, SOCK_STREAM, 0);
    if (_socket < 0) {
        std::cerr << "socket error\n";
    }
};

short Server::Start(struct sockaddr_in& saun)
{
    if (::bind(_socket, (struct sockaddr *)&saun, sizeof(saun)) < 0) {
        std::cerr << "bind error\n";
        return -1;
    }

    if (::listen(_socket, SOMAXCONN) < 0) {
        std::cerr << "listen error\n";
        return -1;
    }

    return 0;
};

void Server::WaitAccept()
{
    int len;
    _addressAccept = ::accept(_socket, (struct sockaddr *)&_addressConnnected, (socklen_t *)&len);
    if (_addressAccept < 0) {
        std::cerr << "address accept error";
    }
    OnAccept();
    WaitAccept();
}

void Server::OnAccept()
{
    Read();
}

void Server::Read() 
{
    char *readData = new char [MAX_SIZE_MESSAGE];   
    if (::read(_addressAccept, readData, MAX_SIZE_MESSAGE) < 0)
    {
        std::cerr << "error read header";
    }
    
    //debug - need remove 
    std::cout << readData;

    short error;
    message parsedData = parser.ParseHTTP(readData, error);
    if (error < 0) {
        log_debug("Error parse http with code: %d", error);
    }
    
    log_debug("Method: %s\nPath: %s\nProtocol: %s\n",
     parsedData.method.c_str(), parsedData.path.c_str(), parsedData.protocol.c_str());
}

Server::~Server() 
{
    close(_socket);
}