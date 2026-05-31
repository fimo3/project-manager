#include "Task.h"
#include <vector>

class Project {
private:
    std::string name;
    std::vector<Task> tasks;
    int nextId;

public:
    Project(std::string name);

    void addTask(std::string title, int priority, chrono::system_clock::time_point due);
    void show();
    void sortByPriority();
    void sortByDate();
    void markTaskDone(int id);
};