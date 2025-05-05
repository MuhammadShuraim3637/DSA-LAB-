#include <iostream>
#include <queue>
#include <string>
#include <limits>
#include <map>
#include <iomanip>
#include <windows.h>

using namespace std;

const int DAYS = 7;
const int HOURS_PER_DAY = 8;
const int MAX_TASKS = 100;

struct Task {
    string name;
    string category;
    int deadline;
    int priority;
    int duration;
    int hoursCompleted = 0;
    bool isFinished = false;

    bool operator<(const Task& t) const {
        if (priority != t.priority) return priority > t.priority; // Higher priority first
        if (deadline != t.deadline) return deadline > t.deadline; // Earlier deadline first
        return duration > t.duration; // Shorter duration first
    }
};

template<typename T>
T getValidInput(const string& prompt, T minVal, T maxVal) {
    T value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < minVal || value > maxVal) {
            cout << "Invalid input. Please enter between " << minVal << " and " << maxVal << ".\n";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        else {
            cin.ignore(1000, '\n');
            return value;
        }
    }
}

bool isNotEmpty(const string& input) {
    return !input.empty();
}

class Calendar {
private:
    string week[DAYS][HOURS_PER_DAY];
    int hourUsed[DAYS] = { 0 };
    map<string, pair<int, string>> taskInfo;
    vector<Task> taskStorage;

public:
    void schedule(priority_queue<Task> tasks) {
        for (auto& day : hourUsed) day = 0;
        taskInfo.clear();
        fill(&week[0][0], &week[0][0] + sizeof(week) / sizeof(week[0][0]), "");

        while (!tasks.empty()) {
            Task t = tasks.top();
            tasks.pop();

            int remaining = t.duration - t.hoursCompleted;
            if (remaining <= 0) continue;

            int maxDay = min(t.deadline - 1, DAYS - 1);

            for (int day = 0; day <= maxDay && remaining > 0; day++) {
                int available = HOURS_PER_DAY - hourUsed[day];
                if (available <= 0) continue;

                int allocate = min(available, remaining);
                for (int h = 0; h < allocate; h++) {
                    week[day][hourUsed[day]++] = t.name;
                }
                taskInfo[t.name] = { taskInfo[t.name].first + allocate, t.category };
                remaining -= allocate;

                for (auto& storedTask : taskStorage) {
                    if (storedTask.name == t.name) {
                        storedTask.hoursCompleted += allocate;
                        if (storedTask.hoursCompleted >= storedTask.duration) {
                            storedTask.isFinished = true;
                        }
                        break;
                    }
                }
            }

            if (remaining > 0) {
                cout << "[!] Warning: Task '" << t.name << "' not fully scheduled. "
                    << remaining << " hour(s) left.\n";
            }
        }
    }

    void addTask(const Task& t) {
        if (taskStorage.size() < MAX_TASKS) {
            taskStorage.push_back(t);
            cout << "Task '" << t.name << "' added successfully!\n";
        }
        else {
            cout << "Task limit reached!\n";
        }
    }

    void editTask() {
        if (taskStorage.empty()) {
            cout << "No tasks available to edit!\n";
            return;
        }

        cout << "\n--- Edit Task ---\n";
        for (size_t i = 0; i < taskStorage.size(); i++) {
            cout << i + 1 << ". " << taskStorage[i].name
                << " (" << taskStorage[i].hoursCompleted << "/"
                << taskStorage[i].duration << "h) "
                << "Priority: " << taskStorage[i].priority
                << ", Deadline: Day " << taskStorage[i].deadline << "\n";
        }

        int choice = getValidInput("Select task to edit (0 to cancel): ", 0, (int)taskStorage.size());
        if (choice == 0) return;

        Task& t = taskStorage[choice - 1];
        cout << "\nEditing: " << t.name << "\n"
            << "1. Name\n2. Category\n3. Deadline\n4. Priority\n5. Duration\n"
            << "6. Mark Hours\n7. Delete Task\nChoice: ";

        int opt = getValidInput("", 1, 7);
        cin.ignore();

        switch (opt) {
        case 1: {
            cout << "New name: ";
            string newName;
            while (true) {
                getline(cin, newName);
                if (isNotEmpty(newName)) {
                    t.name = newName;
                    break;
                }
                cout << "Task name cannot be empty! Please enter a valid name: ";
            }
            break;
        }
        case 2: {
            cout << "New category: ";
            string newCategory;
            while (true) {
                getline(cin, newCategory);
                if (isNotEmpty(newCategory)) {
                    t.category = newCategory;
                    break;
                }
                cout << "Category cannot be empty! Please enter a valid category: ";
            }
            break;
        }
        case 3:
            t.deadline = getValidInput("New deadline (1-7): ", 1, 7);
            break;
        case 4:
            t.priority = getValidInput("New priority (1-5): ", 1, 5);
            break;
        case 5:
            t.duration = getValidInput("New duration (1-8): ", 1, 8);
            break;
        case 6: {
            int hours = getValidInput("Hours completed: ", 0, t.duration);
            t.hoursCompleted = hours;
            t.isFinished = (hours >= t.duration);
            break;
        }
        case 7: {
            taskStorage.erase(taskStorage.begin() + (choice - 1));
            cout << "Task deleted successfully.\n";
            break;
        }
        }
    }

    void showProgress() {
        if (taskStorage.empty()) {
            cout << "No tasks available!\n";
            return;
        }

        cout << "\n--- Task Progress ---\n";
        for (const auto& task : taskStorage) {
            float progress = task.duration > 0 ? (float)task.hoursCompleted / task.duration : 0;
            cout << task.name << " ["
                << string(50 * progress, '=') << string(50 - (50 * progress), ' ') << "] "
                << int(progress * 100) << "% "
                << "(Priority: " << task.priority << ", Deadline: Day " << task.deadline << ")\n";
        }
    }

    void showByCategory(const string& category) {
        cout << "\n--- Category: " << category << " ---\n";
        bool found = false;
        for (const auto& task : taskStorage) {
            if (task.category == category) {
                found = true;
                cout << "- " << task.name << " ("
                    << task.hoursCompleted << "/"
                    << task.duration << "h) "
                    << "Priority: " << task.priority
                    << ", Deadline: Day " << task.deadline << "\n";
            }
        }
        if (!found) {
            cout << "No tasks found in this category.\n";
        }
    }

    void display() {
        if (taskStorage.empty()) {
            cout << "No tasks available to schedule!\n";
            return;
        }

        cout << "\n================== WEEKLY SCHEDULE ==================\n";
        for (int day = 0; day < DAYS; day++) {
            cout << "\n-------------------- Day " << (day + 1)
                << " (" << hourUsed[day] << "/8h) -------------------\n";

            string currentTask;
            int duration = 0;

            for (int hour = 0; hour < HOURS_PER_DAY; hour++) {
                if (hour < hourUsed[day]) {
                    if (week[day][hour] != currentTask) {
                        if (!currentTask.empty()) {
                            cout << "| " << setw(20) << left << currentTask
                                << " - " << duration << " hour(s) |\n";
                        }
                        currentTask = week[day][hour];
                        duration = 1;
                    }
                    else {
                        duration++;
                    }
                }
                else {
                    if (currentTask != "[Free Time]") {
                        if (!currentTask.empty()) {
                            cout << "| " << setw(20) << left << currentTask
                                << " - " << duration << " hour(s) |\n";
                        }
                        currentTask = "[Free Time]";
                        duration = 1;
                    }
                    else {
                        duration++;
                    }
                }
            }
            if (!currentTask.empty()) {
                cout << "| " << setw(20) << left << currentTask
                    << " - " << duration << " hour(s) |\n";
            }
        }
        displaySummary();
    }

    void displaySummary() {
        if (taskInfo.empty()) {
            cout << "\nNo tasks scheduled yet.\n";
            return;
        }

        cout << "\n-------------------- SUMMARY ----------------------\n";
        for (const auto& pair : taskInfo) {
            cout << "- " << setw(20) << left << pair.first
                << ": " << pair.second.first << " hour(s) "
                << "(" << pair.second.second << ")\n";
        }

        // Show unscheduled tasks
        vector<string> unscheduled;
        for (const auto& task : taskStorage) {
            if (taskInfo.find(task.name) == taskInfo.end() && !task.isFinished) {
                unscheduled.push_back(task.name);
            }
        }

        if (!unscheduled.empty()) {
            cout << "\nUnscheduled tasks:\n";
            for (const auto& taskName : unscheduled) {
                cout << "- " << taskName << "\n";
            }
        }
    }

    priority_queue<Task> getQueue() {
        priority_queue<Task> q;
        for (const auto& task : taskStorage) {
            if (!task.isFinished) {
                q.push(task);
            }
        }
        return q;
    }

    void listAllTasks() {
        if (taskStorage.empty()) {
            cout << "No tasks available!\n";
            return;
        }

        cout << "\n--- All Tasks ---\n";
        for (size_t i = 0; i < taskStorage.size(); i++) {
            const auto& task = taskStorage[i];
            cout << i + 1 << ". " << task.name << " ("
                << task.hoursCompleted << "/" << task.duration << "h) "
                << "Priority: " << task.priority
                << ", Deadline: Day " << task.deadline
                << ", Category: " << task.category
                << " [" << (task.isFinished ? "COMPLETED" : "PENDING") << "]\n";
        }
    }
};

void typewriter(string text, int padding) {
    cout << string(padding, ' ');
    for (char c : text) {
        cout << c;
        cout.flush();
        Sleep(50);
    }
    cout << endl;
}

void shimmerLine(int width) {
    for (int i = 0; i < width; i++) {
        cout << "=";
        cout.flush();
        Sleep(2);
    }
    cout << endl;
}

void showWelcomeAnimation() {
    system("cls");
    const int consoleWidth = 80;
    const int consoleHeight = 24;
    string welcome = "WELCOME TO WEEKLY TASK SCHEDULER";
    string subtitle = "Manage your tasks smartly and stay organized!";

    int padding1 = (consoleWidth - welcome.length()) / 2;
    int padding2 = (consoleWidth - subtitle.length()) / 2;
    int verticalPadding = (consoleHeight - 6) / 2;

    for (int i = 0; i < verticalPadding; i++) cout << endl;
    shimmerLine(consoleWidth);
    typewriter(welcome, padding1);
    shimmerLine(consoleWidth);
    cout << endl;
    typewriter(subtitle, padding2);

    Sleep(700);
    cout << "\n\n";
    cout << string((consoleWidth - 25) / 2, ' ') << "Loading... Please wait\n\n";

    int loadingWidth = 50;
    cout << string((consoleWidth - (loadingWidth + 2)) / 2, ' ') << "[";
    for (int i = 0; i < loadingWidth; i++) {
        cout << "=";
        cout.flush();
        Sleep(20);
    }
    cout << "]\n";

    Sleep(700);
    system("cls");
}

int main() {
    showWelcomeAnimation();
    Calendar cal;

    while (true) {
        system("cls");
        cout << "\n============== TASK SCHEDULER MENU ==============\n"
            << "1. Add Task\n2. Edit Task\n3. Show Schedule\n4. View Progress\n"
            << "5. View by Category\n6. List All Tasks\n7. Exit\n"
            << "===============================================\n";

        int choice = getValidInput("Select an option: ", 1, 7);
        system("cls");

        if (choice == 1) {
            Task t;
            cout << "Enter task name: ";
            while (true) {
                getline(cin, t.name);
                if (isNotEmpty(t.name)) break;
                cout << "Task name cannot be empty. Try again: ";
            }

            cout << "Enter category: ";
            while (true) {
                getline(cin, t.category);
                if (isNotEmpty(t.category)) break;
                cout << "Category cannot be empty. Try again: ";
            }

            t.deadline = getValidInput("Deadline (1-7): ", 1, 7);
            t.priority = getValidInput("Priority (1-5, 1=highest): ", 1, 5);
            t.duration = getValidInput("Duration (1-8 hours): ", 1, 8);
            t.hoursCompleted = 0;
            t.isFinished = false;

            cal.addTask(t);
            system("pause");
        }
        else if (choice == 2) {
            cal.editTask();
            system("pause");
        }
        else if (choice == 3) {
            cal.schedule(cal.getQueue());
            cal.display();
            system("pause");
        }
        else if (choice == 4) {
            cal.showProgress();
            system("pause");
        }
        else if (choice == 5) {
            string category;
            cout << "Enter category: ";
            getline(cin, category);
            cal.showByCategory(category);
            system("pause");
        }
        else if (choice == 6) {
            cal.listAllTasks();
            system("pause");
        }
        else if (choice == 7) {
            break;
        }
    }

    return 0;
}