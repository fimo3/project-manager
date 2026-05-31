#include <string>
#include <chrono>
using namespace std;

class Task {
private:
    int id;
    std::string title;
    int priority;
    chrono::system_clock::time_point due;
    int status;

public:
    Task(int id, std::string title, int priority, chrono::system_clock::time_point due);

    void markDone();
    int getPriority();
    chrono::system_clock::time_point getDate();
    int getStatus();
};