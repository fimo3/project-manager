#include "Task.h"
#include <vector>
using namespace std;

class Project {
private:
    std::string name;
    std::vector<Task> tasks;
    int nextId;

public:
    Project(std::string name);

    std::string getName() const;

    void addTask(std::string title, int priority, chrono::system_clock::time_point due);
    void show();
    void sortByPriority();
    void sortByDate();
    void markTaskDone(int id);
};