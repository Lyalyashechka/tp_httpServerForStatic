#include "parser.h"

message Parser::ParseHTTP (char *request, short& error)
{
    error = 0;
    message result;

    size_t counterSpace = 0; 
    while(*request) {
        switch (*request)
        {
        case ' ':
            counterSpace++;
            break;
        case '\n':
            counterSpace++;
            break;
        default:
            if (counterSpace == 0) {
                result.method += *request;
            } else if (counterSpace == 1) {
                result.path += *request;
            } else if (counterSpace == 2) {
                result.protocol += *request;
            }
            break;
        }
        *request++;
    }
    if (!isCorrectMethod(result.method)) {
        error = BAD_METHOD;
    }

    return result;
}

bool Parser::isCorrectMethod(const std::string& method)
{
    for (const std::string& item : supportedMethod) {
        if (method == item) {
            return true;
        }
    }

    return false;
}