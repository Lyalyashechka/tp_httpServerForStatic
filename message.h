#include <string>

struct HTTPRequest
{
    std::string method; 
    std::string path;
    std::string protocol; 
};

struct HTTPResponse 
{
    std::string protocol = "HTTP/1.1";
    int code;
    std::string connection = "close";
    std::string server = "http_server";
    int contentLength;
    std::string data;
    std::string contentType;
};