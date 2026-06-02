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

void Manager::showAll() {
    if (projects.empty()) {
        std::cout << "No projects available." << std::endl;
        return;
    }

    std::cout << "Projects:\n";
    for (const auto &project : projects) {
        std::cout << "- " << project.getName() << std::endl;
    }
}