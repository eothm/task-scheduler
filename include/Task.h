#pragma once
#include <string>
#include <chrono>
#include <thread>

class Task {
private:
    std::string id;
    int priority;
    int durationMs;  // Estimated execution time in milliseconds

public:
    Task(const std::string& id, int priority, int durationMs);

    std::string getId() const;
    int getPriority() const;
    int getDuration() const;

    void execute() const;
};
