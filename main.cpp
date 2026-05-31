#include "Manager.h"
#include <iostream>

int main() {
    Manager m;
    int choice;

    while (true) {
        std::cout << "1. Add project\n";
        std::cout << "2. Show projects\n";
        std::cout << "3. Exit\n";
        std::cin >> choice;

        if (choice == 1) {
            std::string name;
            std::cin >> name;
            m.addProject(name);
        }

        if (choice == 2) {
            m.showAll();
        }

        if (choice == 3) break;
    }
}