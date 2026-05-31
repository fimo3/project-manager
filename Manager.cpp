#include "Manager.h"
#include <iostream>

void Manager::addProject(std::string name) {
    projects.push_back(Project(name));
}

Project* Manager::findProject(std::string name) {
    for (auto &p : projects)
        if (p.getName() == name)
            return &p;
    return nullptr;
}