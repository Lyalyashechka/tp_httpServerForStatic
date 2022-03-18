#include "server.h"
#include <unistd.h>
#include <thread>
#include <filesystem>

#define MAX_SIZE_MESSAGE 10'000

Server::Server(Config _conf) 
{
    conf = _conf;
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

    if (::listen(_socket, conf.threadLimit) < 0) {
        std::cerr << "listen error\n";
        return -1;
    }

    return 0;
};

void Server::WaitAccept()
{
    while(1){
    int len;
    struct sockaddr_un _addressConnnected;
    int _addressAccept = ::accept(_socket, (struct sockaddr *)&_addressConnnected, (socklen_t *)&len);
    if (_addressAccept < 0) {
        std::cerr << "address accept error";
    } else {
        OnAccept(_addressAccept);
    }
    }
    WaitAccept();
}

void Server::OnAccept(int _addressAccept)
{
    Read(_addressAccept);
}

void Server::Read(int _addressAccept) 
{
    char *readData = new char [MAX_SIZE_MESSAGE];   
    if (::read(_addressAccept, readData, MAX_SIZE_MESSAGE) < 0) {
        std::cerr << "error read header";
    }

    short error;
    HTTPRequest parsedData = parser.ParseHTTP(readData, error);
    if (error < 0) {
        log_debug("Error parse http with code: %d", error);
    }
    log_debug("Method: %s\nPath: %s\nProtocol: %s\n",
     parsedData.method.c_str(), parsedData.path.c_str(), parsedData.protocol.c_str());
    delete []readData;
    std::thread tRequset(&Server::OnRead, this, _addressAccept, parsedData);
    tRequset.detach();
}

void Server::OnRead(int _addressConnnected, HTTPRequest mes)
{
    mes.path = parser.urlEncoding(mes.path);
    HTTPResponse response;
    if (mes.method == "HEAD" || mes.method == "GET") {
        if (mes.path.find("/httptest/../") != std::string::npos) {
            response.code = 403;
        } else {
            int error = 0; 
            std::string fileName = mes.path;
            std::string message = fsManager.getFile(fileName, error);
            if (error == -1) {
                response.code = 404;
                log_debug("file %s is not exist\n", mes.path.c_str());
            } else if (error == -2) {
                response.code = 403;
            } else {
                response.code = 200;
                response.contentLength = message.length();
                if (mes.method != "HEAD"){
                    response.data = message;
                }
                log_debug("ok file read %s\n", mes.path.c_str());
            }
            response.contentType = parser.getContentTypeByFileName(fileName);
        }
    } else {
        response.code = 405;
    }
    
    std::string responseString = parser.HTTPResponseToString(response);
    if (send(_addressConnnected, responseString.c_str(), responseString.size(), 0) < 0)
    {
        log_error("error send data");
    }
    close(_addressConnnected);
}

Server::~Server() 
{
    close(_socket);
}