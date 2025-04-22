#include "include/Scheduler.h"
#include "include/Timer.h"
#include "include/Logger.h"
#include <thread>
#include <vector>
#include <fstream>
#include <iostream>


int loadTasksFromFile(Scheduler& scheduler, const std::string& filename) {
    std::ifstream file(filename);
    std::string id;
    int priority, duration;

    if (!file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        Logger::getInstance().log("Failed to open task file.");
        return 1;
    }else{

    while (file >> id >> priority >> duration) {
        scheduler.addTask(std::make_shared<Task>(id, priority, duration));
    }

    Logger::getInstance().log("Tasks loaded from file: " + filename);
    return 0;
}}

int main() {
    Scheduler scheduler;
    int error = loadTasksFromFile(scheduler, "../tasks.txt");
    if(error==1){
        return 1;
    }

    std::vector<std::thread> threads;

    for (int i = 0; i < 3 && !scheduler.isEmpty(); ++i) {
        auto task = scheduler.getNextTask();
        if (task) {
            threads.emplace_back([task]() {
                Logger::getInstance().log("Running task in parallel: " + task->getId());
                task->execute();
            });
        } else {
            Logger::getInstance().log("Task is null, skipping...");
        }
    }
    for (auto& t : threads) {
        if (t.joinable()) t.join();
    }

    Logger::getInstance().log("Remaining task(s) will now run sequentially:");

    while (!scheduler.isEmpty()) {
        scheduler.runNextTask();
    }

    return 0;
}