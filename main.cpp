#include "include/Scheduler.h"
#include "include/Timer.h"
#include "include/Logger.h"
#include <thread>
#include <vector>
#include <fstream>

void loadTasksFromFile(Scheduler& scheduler, const std::string& filename) {
    std::ifstream file(filename);
    std::string id;
    int priority, duration;

    if (!file) {
        Logger::getInstance().log("Failed to open task file.");
        return;
    }

    while (file >> id >> priority >> duration) {
        scheduler.addTask(std::make_shared<Task>(id, priority, duration));
    }

    Logger::getInstance().log("Tasks loaded from file: " + filename);
}

int main() {
    Scheduler scheduler;
    loadTasksFromFile(scheduler, "tasks.txt");

    std::vector<std::thread> threads;

    // Run top 3 tasks in parallel
    for (int i = 0; i < 3 && !scheduler.isEmpty(); ++i) {
        auto task = scheduler.getNextTask();
        threads.emplace_back([task]() {
            Logger::getInstance().log("Running task in parallel: " + task->getId());
            task->execute();
        });
    }

    for (auto& t : threads) {
        if (t.joinable()) t.join();
    }

    Logger::getInstance().log("Remaining task(s) will now run sequentially:");

    // Run the rest sequentially
    while (!scheduler.isEmpty()) {
        scheduler.runNextTask();
    }

    return 0;
}