#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "parser.h"
#include "common.h"

class Server
{

public:
    Server();

    ~Server();

    short Start(struct sockaddr_in &saun);

    void WaitAccept();

private:
    void OnAccept();

    void Read();

    int _socket;
    int _addressAccept;
    struct sockaddr_un _addressConnnected;

    Parser parser;
};