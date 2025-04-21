#include "Scheduler.h"
#include "Logger.h"

void Scheduler::addTask(const std::shared_ptr<Task>& task) {
    taskQueue.push(task);
    Logger::getInstance().log("Added task: " + task->getId());
}

void Scheduler::runNextTask() {
    if (!taskQueue.empty()) {
        auto task = taskQueue.top();
        taskQueue.pop();
        Logger::getInstance().log("Running task: " + task->getId());
        task->execute();
    }
}

std::shared_ptr<Task> Scheduler::getNextTask() {
    if (!taskQueue.empty()) {
        auto task = taskQueue.top();
        taskQueue.pop();
        return task;
    }
    return nullptr;
}

bool Scheduler::isEmpty() const {
    return taskQueue.empty();
}