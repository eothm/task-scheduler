#pragma once
#include <vector>
#include <queue>
#include <thread>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <fstream>
#include <sstream>
#include "TaskComparator.hpp"
#include "Task.h"
#include "Timer.h"
#include "Logger.h"


class Scheduler{
    private:
        std::priority_queue<std::shared_ptr<Task>, std::vector<std::shared_ptr<Task>>, TaskComparator> task_queue;
        std::mutex queue_mutex;
        std::condition_variable cv;
        std::vector<std::thread> workers;
    public:
        void addTask(const Task& task);
        void start();
        void stop();
        void loadTasksFromFile(const std::string& filename);
        void saveTasksToFile(const std::string& filename);

};