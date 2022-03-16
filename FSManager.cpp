#include "FSManager.h"
#include <fstream>
#include <sstream>

FSManager::FSManager(/* args */)
{
}

FSManager::~FSManager()
{
}

std::string FSManager::getFile(std::string& fileName, int& error)
{
    fileName = ".." + fileName;
    std::string result;
    bool isIndexHTML = false;
    if (fileName.back() == '/') {
        if (fileName.find(".html") != std::string::npos) {
            error = -1;
            return result;
        }
        isIndexHTML = true;
        fileName += "index.html";
    }

    std::ifstream file(fileName, std::ios_base::binary);

    if (!file.is_open()) {
        error = -1;
        if (isIndexHTML) {
            error = -2;
        }
        return result;
    }

    std::stringstream fl;
    
    fl << file.rdbuf();

    result = fl.str();
    file.close();
    return result;
}