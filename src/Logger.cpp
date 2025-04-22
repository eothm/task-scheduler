#include "Logger.h"
#include <iostream>
#include <chrono>
#include <ctime>

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}
Logger::Logger() {
    logFile.open("log.txt", std::ios::out | std::ios::trunc);
    if (!logFile) {
        std::cerr << "Failed to open log file." << std::endl;
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::log(const std::string& message) {
    std::lock_guard<std::mutex> lock(mtx);
    std::time_t now = std::time(nullptr);
    std::string ts = std::ctime(&now);
    ts.pop_back();

    if (logFile.is_open()) {
        logFile << "[" << ts << "] " << message << std::endl;
    } else {
        std::cerr << "[" << ts << "] " << message << std::endl;
    }
}
