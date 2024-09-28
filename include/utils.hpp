#pragma once

#ifdef DEBUG
    #define LOG_DEBUG(msg) std::cout << "[DEBUG] " << msg << std::endl;
#else
    #define LOG_DEBUG(msg)
#endif