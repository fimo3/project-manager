#include "Project.h"
#include <algorithm>
#include <iostream>

Project::Project(std::string name) {
    this->name = name;
    nextId = 1;
}

void Project::addTask(std::string title, int priority, chrono::system_clock::time_point due) {
    tasks.push_back(Task(nextId++, title, priority, due));
}