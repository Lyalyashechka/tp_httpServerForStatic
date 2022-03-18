#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>

#include "parser.h"
#include "common.h"
#include "FSManager.h"


struct Config {
    int threadLimit;
    std::string documentRoot;
};

class Server
{

public:
    Server(Config conf);

    ~Server();

    short Start(struct sockaddr_in &saun);

    void WaitAccept();

private:
    void OnAccept(int _addressConnnected);

    void Read(int _addressConnnected);

    void OnRead(int _addressConnnected, HTTPRequest message);
    
    int _socket;

    FSManager fsManager;
    Parser parser;
    Config conf;
    
    std::vector<std::thread> threadRequest;
};