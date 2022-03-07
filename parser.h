#include "message.h"
#include "common.h"

class Parser
{
public:
    Parser() = default;

    message ParseHTTP(char *request, short &error);

    enum ParseError
    {
        BAD_METHOD = -3,
        BAD_PATH,
        BAD_PROTOCOL,
        OK,
    };

private:
    bool isCorrectMethod(const std::string& method);

    std::vector<std::string> supportedMethod {"GET"};
};