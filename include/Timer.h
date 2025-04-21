#pragma once
#include <chrono>

class Timer {
public:
    void start();
    void stop();
    double elapsedMilliseconds() const;
    double elapsedSeconds() const;

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> endTime;
    bool running = false;
};
