#include <string>

class FSManager
{
private:
    /* data */
public:
    std::string getFile(std::string& fileName, int& error);
    
    FSManager(/* args */);
    ~FSManager();
};


