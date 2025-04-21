#pragma once
#include <string>
#include <fstream>
#include <memory>
#include <mutex>

class Logger {
public:
    static Logger& getInstance();

    void log(const std::string& message);
    void setLogFile(const std::string& filePath);
    
private:
    Logger() = default;  // Singleton
    std::ofstream logFile;
    std::mutex mtx;
};
