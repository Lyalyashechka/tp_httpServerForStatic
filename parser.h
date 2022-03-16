#include "message.h"
#include "common.h"

class Parser
{
public:
    Parser() = default;

    HTTPRequest ParseHTTP(char *request, short &error);

    enum ParseError
    {
        BAD_METHOD = -3,
        BAD_PATH,
        BAD_PROTOCOL,
        OK,
    };

    std::string HTTPResponseToString(const HTTPResponse& message);

    std::string getContentTypeByFileName(const std::string& fileName);

    std::string urlEncoding(std::string &url);
private:
    bool isCorrectMethod(const std::string& method);
    
    std::string getDescriptionCode(int code);

    std::vector<std::string> supportedMethod {"GET", "HEAD"};
};