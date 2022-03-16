#include "parser.h"
#include <chrono>
#include <filesystem>

HTTPRequest Parser::ParseHTTP (char *request, short& error)
{
    error = 0;
    HTTPRequest result;
    
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

std::string Parser::HTTPResponseToString(const HTTPResponse& message)
{

    std::string result = message.protocol + " " + std::to_string(message.code) + " " +
                        getDescriptionCode(message.code) + "\r\n" +
                        "Version: HTTP/1.1\r\n" + 
                        "Connection: " + message.connection + "\r\n" + 
                        "Server: " + message.server + "\r\n";
    auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
                    
    result += "Date: " + std::string(ctime(&t)); 

    if (message.code != 200) {
        result += "\r\n\r\n";
        return result;
    }
    result += "Content-Type: " + message.contentType + "\r\n";
    result += "Content-Length: " +std::to_string(message.contentLength) + "\r\n\r\n" + 
               message.data;
    
    return result;
}

std::string Parser::getDescriptionCode(int code)
{
    switch (code)
    {
    case 200:
        return "OK";
        break;
    case 405: 
        return "Method Not Allowed";
        break;
    case 403: 
        return "Forbidden";
        break;
    default:
        return "Not Found";
        break;
    }
    return "Not Found";

}

std::string Parser::getContentTypeByFileName(const std::string& fileName) 
{
    std::string extension = std::filesystem::path(fileName).extension();
	if (extension == ".txt")
		return "text/txt";
	else if (extension == ".css")
		return "text/css";
	else if (extension == ".html")
		return "text/html";
	else if (extension == ".js")
		return "application/javascript";
	else if (extension == ".jpeg" || extension == ".jpg")
		return "image/jpeg";
	else if (extension == ".png")
		return "image/png";
	else if (extension == ".gif")
		return "image/gif";
	else if (extension == ".swf")
		return "application/x-shockwave-flash";
	return "";
}

std::string Parser::urlEncoding(std::string& url) {
    std::string newUrl;
	char ch;
	int j;
	for (int i = 0; i < url.size(); i++) {
		if (url[i] == '%') {
			sscanf(url.substr(i + 1, 2).c_str(), "%x", &j);
			ch = static_cast<char>(j);
			newUrl += ch;
			i = i + 2;
		} else {
			newUrl += url[i];
		}
	}

    if (newUrl.find('?') != std::string::npos) {
        newUrl.erase(newUrl.find('?'));
    }
	return newUrl;
}