#include "Logger.h"
#include <iostream>
#include <chrono>
#include <ctime>

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::setLogFile(const std::string& filePath) {
    std::lock_guard<std::mutex> lock(mtx);
    logFile.open(filePath, std::ios::app);
}

void Logger::log(const std::string& message) {
    std::lock_guard<std::mutex> lock(mtx);

    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string timestamp = std::ctime(&now);
    timestamp.pop_back(); 

    std::string output = "[" + timestamp + "] " + message;

    Logger::getInstance().log(output);

    if (logFile.is_open()) {
        logFile << output << std::endl;
    }
}
