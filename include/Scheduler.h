#pragma once
#include "Task.h"
#include <queue>
#include <vector>
#include <memory>
#include <functional>

class TaskComparator {
public:
    bool operator()(const std::shared_ptr<Task>& a, const std::shared_ptr<Task>& b) const {
        return a->getPriority() < b->getPriority();
    }
};

class Scheduler {
private:
    std::priority_queue<std::shared_ptr<Task>, std::vector<std::shared_ptr<Task>>, TaskComparator> taskQueue;

public:
    void addTask(const std::shared_ptr<Task>& task);
    void runNextTask();

    // New methods for parallel execution
    std::shared_ptr<Task> getNextTask();
    bool isEmpty() const;
};