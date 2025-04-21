#pragma once
#include<string>
#include"Logger.h"
using namespace std;
class Task{
    public:
        bool operator<(Task t);
        int getPriority() const;
        void serialize(const string& filename);
        static Task deserialize(const string& filename)
    {
        Task obj;
        ifstream file(filename, ios::binary);
        if (!file.is_open()) {
            cerr
                << "Error: Failed to open file for reading."
                << endl;
            return obj;
        }
        file.read(reinterpret_cast<char*>(&obj),
                  sizeof(obj));
        file.close();
        cout << "Object deserialized successfully." << endl;
        return obj;
    }
        void setId(int id);
        void setName(string name);
        void setEstimatedTime(int estimated_time);
        void setPriority(int priority);
        int getId() const{ return id;};
        string getName() const{return name;};
        int getEstimatedTime() const{return estimated_time_ms;};
        int getPriority() const{return priority;};
    
    private:
        int id;
        string name;
        int priority;
        int estimated_time_ms;

};