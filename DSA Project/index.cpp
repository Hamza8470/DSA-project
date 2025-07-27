#include <iostream>
#include <queue>
#include <stack>
#include <string>

using namespace std;

// Class to store one check-in record
class Checkin {
public:
    string date;
    int mood;
    int sleepHours;
    int stressLevel;
    string appetite;

    Checkin(string d, int m, int s, int stress, string a)
        : date(d), mood(m), sleepHours(s), stressLevel(stress), appetite(a) {}
// display function
    void display() const {
        cout << "Date: " << date
             << " | Mood: " << mood
             << " | Sleep: " << sleepHours << " hrs"
             << " | Stress: " << stressLevel
             << " | Appetite: " << appetite << endl;
    }
};

// Simulator class with only queue and stack
class MentalHealthSimulator {
private:
    queue<Checkin> last7Days;
    stack<Checkin> undoStack;

public:
    void addCheckin(const Checkin& c) {
        if (last7Days.size() == 7) {
            last7Days.pop();  // Keep only last 7 check-ins
        }
        last7Days.push(c);
        undoStack.push(c);
        cout << "\n✅ Check-in recorded.\n";
    }

    void undoLastCheckin() {
        if (!undoStack.empty()) {
            Checkin last = undoStack.top();
            undoStack.pop();

            // Rebuild the queue without the undone check-in
            queue<Checkin> tempQ, newQ;
            while (!last7Days.empty()) {
                Checkin temp = last7Days.front();
                last7Days.pop();
                if (temp.date != last.date) {
                    newQ.push(temp);
                }
            }
            last7Days = newQ;
            cout << "\n❌ Last check-in on " << last.date << " undone.\n";
        } else {
            cout << "\n⚠️ No check-ins to undo.\n";
        }
    }

    void showLast7Days() const {
        if (last7Days.empty()) {
            cout << "\n📭 No check-ins to display.\n";
            return;
        }

        cout << "\n📆 Last Check-ins:\n";
        queue<Checkin> temp = last7Days;
        while (!temp.empty()) {
            temp.front().display();
            temp.pop();
        }
    }

    void giveSuggestion(const Checkin& c) const {
        cout << "\n💡 Suggestion:\n";

        if (c.mood < 4) {
            cout << "- Mood is low. Talk to a friend or go for a walk.\n";
        }

        if (c.stressLevel > 7) {
            cout << "- High stress. Try relaxation techniques like deep breathing.\n";
        }

        if (c.sleepHours < 6) {
            cout << "- You need more rest. Aim for 7–8 hours of sleep.\n";
        }

        if (c.appetite == "Poor" || c.appetite == "poor") {
            cout << "- Try to eat small but frequent healthy meals.\n";
        }

        if (c.mood >= 7 && c.stressLevel <= 4 && c.sleepHours >= 7) {
            cout << "- You're doing great! Keep it up! 🌟\n";
        }
    }
};

// Main driver function
int main() {
    MentalHealthSimulator app;

    while (true) {
        cout << "\n====== Mental Health Check-in Menu ======\n";
        cout << "1. Add Today's Check-in\n";
        cout << "2. View Last 7 Check-ins\n";
        cout << "3. Undo Last Check-in\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        if (choice == 1) {
            string date, appetite;
            int mood, sleep, stress;

            cout << "\nEnter date (DD-MM-YYYY): ";
            cin >> date;
            cout << "Mood (1-10): ";
            cin >> mood;
            cout << "Sleep Hours: ";
            cin >> sleep;
            cout << "Stress Level (1-10): ";
            cin >> stress;
            cout << "Appetite (Poor/Okay/Good): ";
            cin >> appetite;

            Checkin c(date, mood, sleep, stress, appetite);
            app.addCheckin(c);
            app.giveSuggestion(c);
        }
        else if (choice == 2) {
            app.showLast7Days();
        }
        else if (choice == 3) {
            app.undoLastCheckin();
        }
        else if (choice == 4) {
            cout << "\n👋 Stay positive. Take care!\n";
            break;
        }
        else {
            cout << "⚠️ Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
