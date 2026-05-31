#include "Task.h"

Task::Task(int id, std::string title, int priority, chrono::system_clock::time_point due) {
    this->id = id;
    this->title = title;
    this->priority = priority;
    this->due = due;
    this->status = 0;
}

void Task::markDone() {
    status = 1;
}