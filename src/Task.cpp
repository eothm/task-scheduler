#include "Task.h"
#include <string>
#include<iostream>
#include<fstream>
using namespace std;

int Task::getPriority() const{
    return priority;
}
bool Task::operator<(Task t){
    return (getPriority() < t.getPriority());
}

void Task::serialize(const string& filename){
    {
        ofstream file(filename, ios::binary);
        if (!file.is_open()) {
            cerr
                << "Error: Failed to open file for writing."
                << endl;
            return;
        }
        string line= to_string(id) + "," + name + "," + to_string(priority) + "," + to_string(estimated_time_ms);
        file.write(line.c_str(), line.size());
        file.close();
        Logger::getInstance().log("Object serialized successfully.");
    }

}

void Task::setId(int id){
    this->id = id;
}
void Task::setPriority(int priority){
    this->priority = priority;
}
void Task::setName(string name){
    this->name = name;
}
void Task::setEstimatedTime(int estimated_time){
    this->estimated_time_ms = estimated_time;
}