#pragma once
#include <string>
#include <fstream>
#include <memory>
#include <mutex>

class Logger {
public:
    static Logger& getInstance();
    ~Logger();
    void log(const std::string& message);
    
private:
    Logger();
    std::ofstream logFile;
    std::mutex mtx;
};
