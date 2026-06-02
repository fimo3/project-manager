#define NOMINMAX
#define _HAS_STD_BYTE 0
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <thread>
#include <chrono>

using namespace std;

#ifdef _WIN32
#include <windows.h>
void enableColors()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}
#else
void enableColors() {}
#endif

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define BOLD    "\033[1m"

void loading(string text)
{
    cout << CYAN << text << RESET;
    for (int i = 0; i < 3; i++)
    {
        cout << ".";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(300));
    }
    cout << "\n";
}

struct Date
{
    int d, m, y;

    bool operator<(const Date& o) const
    {
        if (y != o.y) return y < o.y;
        if (m != o.m) return m < o.m;
        return d < o.d;
    }
};

string dateStr(const Date& d)
{
    return (d.d < 10 ? "0" : "") + to_string(d.d) + "." +
           (d.m < 10 ? "0" : "") + to_string(d.m) + "." +
           to_string(d.y);
}

string statusStr(int s)
{
    if (s == 0) return "PENDING";
    if (s == 1) return "IN PROGRESS";
    return "DONE";
}

class Task
{
public:
    int id;
    string title;
    int priority;
    Date due;
    int status;

    Task(int i, string t, int p, Date d)
    {
        id = i;
        title = t;
        priority = p;
        due = d;
        status = 0;
    }
};

class Project
{
public:
    string name;
    vector<Task> tasks;
    int nextId = 1;

    Project(string n) : name(n) {}

    void addTask()
    {
        cin.ignore();

        string t;
        int p;
        Date d;

        cout << YELLOW << "Task title: " << RESET;
        getline(cin, t);

        cout << YELLOW << "Priority (1-3): " << RESET;
        cin >> p;

        cout << YELLOW << "Date (d m y): " << RESET;
        cin >> d.d >> d.m >> d.y;

        tasks.emplace_back(nextId++, t, p, d);

        loading("Adding task");
        cout << GREEN << "Task added successfully!\n" << RESET;
    }

    void show()
    {
        cout << BOLD << BLUE << "\n=== PROJECT: " << name << " ===\n" << RESET;

        if (tasks.empty())
        {
            cout << RED << "No tasks available\n" << RESET;
            return;
        }

        cout << CYAN << "ID | TITLE | PRIO | DUE | STATUS\n" << RESET;
        cout << "--------------------------------------\n";

        for (auto& t : tasks)
        {
            cout << t.id << " | "
                 << t.title << " | "
                 << t.priority << " | "
                 << dateStr(t.due) << " | "
                 << statusStr(t.status) << "\n";
        }
    }

    void changeStatus()
    {
        int id, s;
        cin >> id >> s;

        for (auto& t : tasks)
        {
            if (t.id == id)
            {
                t.status = s;
                cout << GREEN << "Status updated\n" << RESET;
                return;
            }
        }

        cout << RED << "Task not found\n" << RESET;
    }

    void sortPriority()
    {
        sort(tasks.begin(), tasks.end(),
            [](Task a, Task b)
            {
                return a.priority > b.priority;
            });

        cout << GREEN << "Sorted by priority\n" << RESET;
    }

    void sortDate()
    {
        sort(tasks.begin(), tasks.end(),
            [](Task a, Task b)
            {
                return a.due < b.due;
            });

        cout << GREEN << "Sorted by date\n" << RESET;
    }

    void markDone()
    {
        int id;
        cin >> id;

        for (auto& t : tasks)
        {
            if (t.id == id)
            {
                t.status = 2;
                cout << GREEN << "Marked as DONE\n" << RESET;
                return;
            }
        }
    }

    void summary()
    {
        int done = 0;

        for (auto& t : tasks)
            if (t.status == 2) done++;

        cout << CYAN << "Progress: " << done << "/" << tasks.size() << RESET << "\n";
    }
};

class Manager
{
public:
    vector<Project> projects;

    void addProject()
    {
        cin.ignore();

        string n;
        cout << YELLOW << "Project name: " << RESET;
        getline(cin, n);

        projects.emplace_back(n);

        loading("Creating project");
        cout << GREEN << "Project created\n" << RESET;
    }

    Project* find(string name)
    {
        for (auto& p : projects)
            if (p.name == name)
                return &p;
        return nullptr;
    }

    void show()
    {
        cout << BOLD << "\n=== PROJECT DASHBOARD ===\n" << RESET;

        if (projects.empty())
        {
            cout << RED << "No projects available\n" << RESET;
            return;
        }

        for (auto& p : projects)
        {
            cout << BLUE << "\n[" << p.name << "]\n" << RESET;

            if (p.tasks.empty())
            {
                cout << RED << "  No tasks\n" << RESET;
                continue;
            }

            for (auto& t : p.tasks)
            {
                cout << "  - " << t.title
                     << " (" << statusStr(t.status)
                     << ", P" << t.priority << ")\n";
            }
        }
    }
};

void menu(bool hasProjects)
{
    cout << BOLD << CYAN << "\n=== MENU ===\n" << RESET;

    cout << "1. Add project\n";
    cout << "2. Show projects\n";

    if (hasProjects)
    {
        cout << "3. Add task\n";
        cout << "4. Show project tasks\n";
        cout << "5. Change status\n";
        cout << "6. Sort by priority\n";
        cout << "7. Sort by date\n";
        cout << "8. Mark done\n";
        cout << "9. Summary\n";
    }

    cout << "0. Exit\n";
}

int main()
{
    enableColors();

    Manager m;
    int c;

    loading("Starting system");

    while (true)
    {
        menu(!m.projects.empty());

        cin >> c;

        if (c == 0)
        {
            cout << GREEN << "System closed\n" << RESET;
            break;
        }

        if (c == 1)
        {
            m.addProject();
        }
        else if (c == 2)
        {
            m.show();
        }
        else
        {
            if (m.projects.empty())
            {
                cout << RED << "No projects yet\n" << RESET;
                continue;
            }

            string name;
            cin >> name;

            Project* p = m.find(name);

            if (!p)
            {
                cout << RED << "Project not found\n" << RESET;
                continue;
            }

            if (c == 3) p->addTask();
            if (c == 4) p->show();
            if (c == 5) p->changeStatus();
            if (c == 6) p->sortPriority();
            if (c == 7) p->sortDate();
            if (c == 8) p->markDone();
            if (c == 9) p->summary();
        }
    }
}