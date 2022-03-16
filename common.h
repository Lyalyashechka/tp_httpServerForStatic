#include <string>
#include <vector>

#include <iostream>


#define log_error(M, ...) fprintf(stderr, "[ERROR] (%s:%d) " M "\n", \
                                 __FILE__, __LINE__, ##__VA_ARGS__)

#ifndef NDEBUG
    #define log_debug(M, ...) fprintf(stderr, "[DEBUG] (%s:%d) " M "\n", \
                                 __FILE__, __LINE__, ##__VA_ARGS__)                                
#else
    #define log_debug(M, ...)
#endif