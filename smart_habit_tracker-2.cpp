#include <iostream>
#include <vector>
#include <string>
using namespace std;

class User {
private:
    string name;

public:
    User(string n) : name(n) {}

    string getName() {
        return name;
    }

    void greet() {
        cout << "\nWelcome, " << name << "! Let's track your habits.\n";
    }
};

class Habit {
private:
    string habitName;
    int    streak;
    bool   completedToday;

public:
    Habit(string name) : habitName(name), streak(0), completedToday(false) {}

    string getName()        { return habitName; }
    int    getStreak()      { return streak; }
    bool   isDoneToday()    { return completedToday; }

    void setCompleted(bool val) { completedToday = val; }
    void incrementStreak()      { streak++; }

    virtual void markComplete() {
        if (!completedToday) {
            completedToday = true;
            streak++;
            cout << "  Habit \"" << habitName << "\" marked complete! Streak: " << streak << "\n";
        } else {
            cout << "  Already completed today.\n";
        }
    }

    void showStatus() {
        cout << "  [" << (completedToday ? "DONE" : "    ") << "] "
             << habitName << " | Streak: " << streak << " day(s)\n";
    }

    virtual ~Habit() {}
};

class DailyHabit : public Habit {
private:
    string reminderTime;

public:
    DailyHabit(string name, string time) : Habit(name), reminderTime(time) {}

    string getReminderTime() { return reminderTime; }

    void markComplete() override {
        if (!isDoneToday()) {
            setCompleted(true);
            incrementStreak();
            cout << "  Daily habit \"" << getName()
                 << "\" done! (Reminder was " << reminderTime
                 << ")  Streak: " << getStreak() << "\n";
        } else {
            cout << "  Already completed today.\n";
        }
    }
};

class Tracker {
private:
    vector<DailyHabit> habits;

public:
    void addHabit(string name, string time) {
        habits.push_back(DailyHabit(name, time));
        cout << "  Habit \"" << name << "\" added (reminder: " << time << ")\n";
    }

    void completeHabit(int index) {
        if (index < 1 || index > (int)habits.size()) {
            cout << "  Invalid habit number.\n";
            return;
        }
        habits[index - 1].markComplete();
    }

    void showHabits() {
        if (habits.empty()) {
            cout << "  No habits yet.\n";
            return;
        }
        cout << "\n  --- Your Habits ---\n";
        for (int i = 0; i < (int)habits.size(); i++) {
            cout << "  " << (i + 1) << ". ";
            habits[i].showStatus();
        }
        cout << "  -------------------\n";
    }

    int count() { return (int)habits.size(); }
};

int main() {
    string userName;
    cout << "Enter your name: ";
    getline(cin, userName);

    User    user(userName);
    Tracker tracker;

    user.greet();

    int choice;
    do {
        cout << "\n===== Habit Tracker Menu =====\n";
        cout << "1. Add a habit\n";
        cout << "2. Mark habit as completed\n";
        cout << "3. Show all habits\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                string hName, hTime;
                cout << "  Habit name: ";
                getline(cin, hName);
                cout << "  Reminder time (e.g. 7:00 AM): ";
                getline(cin, hTime);
                tracker.addHabit(hName, hTime);
                break;
            }
            case 2: {
                tracker.showHabits();
                if (tracker.count() > 0) {
                    int num;
                    cout << "  Enter habit number to complete: ";
                    cin >> num;
                    cin.ignore();
                    tracker.completeHabit(num);
                }
                break;
            }
            case 3: {
                tracker.showHabits();
                break;
            }
            case 4: {
                cout << "\nGoodbye, " << user.getName() << "! Keep up the streak!\n";
                break;
            }
            default: {
                cout << "  Invalid choice. Try again.\n";
            }
        }
    } while (choice != 4);

    return 0;
}
