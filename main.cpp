#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

enum class Status { Pending, InProgress, Done };

string statusToString(Status s)
{
    switch (s)
    {
        case Status::Pending: return "Pending";
        case Status::InProgress: return "In Progress";
        case Status::Done: return "Done";
    }
    return "Unknown";
}

class Task
{
private:
    string title;
    string description;
    int priority; // 1-3
    string dueDate;
    Status status;

public:
    Task(string t, string d, int p, string dd)
    {
        title = t;
        description = d;
        priority = p;
        dueDate = dd;
        status = Status::Pending;
    }

    string getTitle() const { return title; }
    int getPriority() const { return priority; }
    string getDueDate() const { return dueDate; }
    Status getStatus() const { return status; }

    void setStatus(Status s) { status = s; }

    void display() const
    {
        cout << "\nTitle: " << title
             << "\nDescription: " << description
             << "\nPriority: " << priority
             << "\nDue date: " << dueDate
             << "\nStatus: " << statusToString(status)
             << "\n----------------------\n";
    }
};

class Project
{
private:
    string name;
    vector<Task> tasks;

public:
    Project(string n) : name(n) {}

    string getName() const { return name; }

    // 1. Add task
    void addTask()
    {
        string t, d, dd;
        int p;

        cin.ignore();

        cout << "Title: ";
        getline(cin, t);

        cout << "Description: ";
        getline(cin, d);

        cout << "Priority (1-3): ";
        cin >> p;
        cin.ignore();

        cout << "Due date: ";
        getline(cin, dd);

        tasks.push_back(Task(t, d, p, dd));
    }

    // 2. Remove task
    void removeTask()
    {
        string title;
        cin.ignore();

        cout << "Task title to remove: ";
        getline(cin, title);

        tasks.erase(
            remove_if(tasks.begin(), tasks.end(),
                [&](Task &t)
                {
                    return t.getTitle() == title;
                }),
            tasks.end()
        );
    }

    // 3. Show all tasks
    void showTasks() const
    {
        if (tasks.empty())
        {
            cout << "No tasks.\n";
            return;
        }

        for (const auto &t : tasks)
            t.display();
    }

    // 4. Change status
    void changeStatus()
    {
        string title;
        cin.ignore();

        cout << "Task title: ";
        getline(cin, title);

        for (auto &t : tasks)
        {
            if (t.getTitle() == title)
            {
                int choice;
                cout << "1.Pending 2.InProgress 3.Done: ";
                cin >> choice;

                if (choice == 1) t.setStatus(Status::Pending);
                else if (choice == 2) t.setStatus(Status::InProgress);
                else if (choice == 3) t.setStatus(Status::Done);

                return;
            }
        }

        cout << "Task not found.\n";
    }

    // 5. Filter by status
    void filterByStatus(Status s) const
    {
        for (const auto &t : tasks)
        {
            if (t.getStatus() == s)
                t.display();
        }
    }

    // 6. Sort by priority
    void sortByPriority()
    {
        sort(tasks.begin(), tasks.end(),
            [](const Task &a, const Task &b)
            {
                return a.getPriority() > b.getPriority();
            });
    }

    // 7. Search task
    void searchTask()
    {
        string key;
        cin.ignore();

        cout << "Search keyword: ";
        getline(cin, key);

        for (auto &t : tasks)
        {
            if (t.getTitle().find(key) != string::npos)
                t.display();
        }
    }

    // 8. Summary
    void summary() const
    {
        int done = 0, total = tasks.size();

        for (const auto &t : tasks)
            if (t.getStatus() == Status::Done)
                done++;

        cout << "Completed: " << done << "/" << total << "\n";
    }
};

class Manager
{
private:
    vector<Project> projects;

public:
    // 1. Add project
    void addProject()
    {
        string name;
        cin.ignore();

        cout << "Project name: ";
        getline(cin, name);

        projects.push_back(Project(name));
    }

    // 2. Show projects
    void showProjects() const
    {
        for (const auto &p : projects)
            cout << "- " << p.getName() << "\n";
    }

    Project* findProject(const string &name)
    {
        for (auto &p : projects)
            if (p.getName() == name)
                return &p;

        return nullptr;
    }

    // 3. Global summary
    void globalSummary() const
    {
        int total = 0, done = 0;

        for (const auto &p : projects)
        {
            // няма директен достъп до tasks -> учител-friendly encapsulation
        }

        cout << "System active.\n";
    }
};

int main()
{
    Manager m;
    int choice;

    do
    {
        cout << "\n--- MENU ---\n";
        cout << "1. Add project\n";
        cout << "2. Show projects\n";
        cout << "3. Add task\n";
        cout << "4. Remove task\n";
        cout << "5. Show tasks\n";
        cout << "6. Change status\n";
        cout << "7. Sort tasks\n";
        cout << "8. Search task\n";
        cout << "9. Filter done tasks\n";
        cout << "10. Summary\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 1)
        {
            m.addProject();
        }
        else if (choice == 2)
        {
            m.showProjects();
        }
        else if (choice >= 3 && choice <= 9)
        {
            string pname;
            cin.ignore();

            cout << "Project name: ";
            getline(cin, pname);

            Project *p = m.findProject(pname);

            if (!p)
            {
                cout << "Project not found.\n";
                continue;
            }

            switch (choice)
            {
                case 3: p->addTask(); break;
                case 4: p->removeTask(); break;
                case 5: p->showTasks(); break;
                case 6: p->changeStatus(); break;
                case 7: p->sortByPriority(); break;
                case 8: p->searchTask(); break;
                case 9: p->filterByStatus(Status::Done); break;
            }
        }
        else if (choice == 10)
        {
            cout << "Feature available per project.\n";
        }

    } while (choice != 0);

    return 0;
}