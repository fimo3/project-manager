#include "Project.h"
#include <vector>

class Manager {
private:
    std::vector<Project> projects;

public:
    void addProject(std::string name);
    Project* findProject(std::string name);
    void showAll();
};