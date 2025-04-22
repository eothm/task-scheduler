#include "Task.h"
#include "Logger.h"

Task::Task(const std::string& id, int priority, int durationMs)
    {
        this->id = id;
        this->priority = priority;
        this->durationMs = durationMs;
    }

std::string Task::getId() const {
    return id;
}

int Task::getPriority() const {
    return priority;
}

int Task::getDuration() const {
    return durationMs;
}

void Task::execute() const {
    Logger::getInstance().log("Executing " + id + " for " + std::to_string(durationMs) + "ms");
    std::this_thread::sleep_for(std::chrono::milliseconds(durationMs));
    Logger::getInstance().log(id + " completed");
}
