#include "Timer.h"

void Timer::start() {
    running = true;
    startTime = std::chrono::high_resolution_clock::now();
}

void Timer::stop() {
    running = false;
    endTime = std::chrono::high_resolution_clock::now();
}

double Timer::elapsedMilliseconds() const {
    auto end = running ? std::chrono::high_resolution_clock::now() : endTime;
    return std::chrono::duration<double, std::milli>(end - startTime).count();
}

double Timer::elapsedSeconds() const {
    auto end = running ? std::chrono::high_resolution_clock::now() : endTime;
    return std::chrono::duration<double>(end - startTime).count();
}
