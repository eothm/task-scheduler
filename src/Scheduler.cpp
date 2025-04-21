#include "Scheduler.h"

void Scheduler::addTask(const Task& task) {
    std::lock_guard<std::mutex> lock(queue_mutex);
    auto task_ptr = std::make_shared<Task>(task);
    task_queue.push(task_ptr);
    cv.notify_one();
}

void Scheduler::start(){
    for (int i = 0; i < std::thread::hardware_concurrency(); ++i) {
        workers.emplace_back([this]() {
            while (true) {
                std::shared_ptr<Task> task;
                {
                    std::unique_lock<std::mutex> lock(queue_mutex);
                    cv.wait(lock, [this] { return !task_queue.empty(); });
                    task = task_queue.top();
                    task_queue.pop();
                }
                // Simulate task execution
                Timer timer;
                timer.start();
                std::this_thread::sleep_for(std::chrono::milliseconds(task->getEstimatedTime()));
                timer.stop();
                Logger::getInstance().log("Task executed in " + std::to_string(timer.elapsedMilliseconds()) + " ms");
            }
        });
    }
}

void Scheduler::stop() {
    for (auto& worker : workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}
void Scheduler::loadTasksFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open file for reading." << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss;
        iss.str(line);
        Task task;
        std::string id_str, name, priority_str, estimated_time_str;
        std::getline(iss, id_str, ',');
        std::getline(iss, name, ',');
        std::getline(iss, priority_str, ',');
        std::getline(iss, estimated_time_str);
        task.setId(std::stoi(id_str));
        task.setName(name);
        task.setPriority(std::stoi(priority_str));
        task.setEstimatedTime(std::stoi(estimated_time_str));
        addTask(task);
    }
    file.close();
    Logger::getInstance().log("Tasks loaded from file successfully.");
}

void Scheduler::saveTasksToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Failed to open file for writing." << std::endl;
        return;
    }
    std::lock_guard<std::mutex> lock(queue_mutex);
    auto temp_queue = task_queue;
    while (!temp_queue.empty()) {
        auto task = temp_queue.top();
        file << task->getId() << "," << task->getName() << "," << task->getPriority() << "," << task->getEstimatedTime() << std::endl;
        temp_queue.pop();
    }
    file.close();
    Logger::getInstance().log("Tasks saved to file successfully.");
}