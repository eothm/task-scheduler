#pragma once
#include <memory>
#include "Task.h"

struct TaskComparator {
    bool operator()(const std::shared_ptr<Task>& a, const std::shared_ptr<Task>& b) const {
        return a->getPriority() < b->getPriority();  
    }
};
