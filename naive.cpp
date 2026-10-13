

#include <iostream> #include <vector> #include <map> #include <string> #include <ctime>
using namespace std;
// Check if assigning slot is safe bool isSafe(string course, int slot, map<string, int>& schedule, map<string, vector<string>>& students) {
for (auto& student : students) {
    vector<string>& enrolled = student.second;

    for (string c : enrolled) {
        if (c == course) {
            for (string other : enrolled) {
                if (schedule.count(other) && schedule[other] == slot) {
                    return false;
                }
            }
        }
    }
}

return true;
}
// Backtracking function bool backtracking(vector<string>& courses, map<string, vector<string>>& students, map<string, int>& schedule, int index, vector<int>& timeSlots) {
if (index == courses.size())
    return true;

string course = courses[index];

for (int slot : timeSlots) {
    if (isSafe(course, slot, schedule, students)) {
        schedule[course] = slot;

        if (backtracking(courses, students, schedule, index + 1, timeSlots))
            return true;

        // Backtrack
        schedule.erase(course);
    }
}

return false;
}
// Main scheduling function map<string, int> naiveSchedule( vector<string>& courses, map<string, vector<string>>& students, vector<int>& timeSlots) {
map<string, int> schedule;
backtracking(courses, students, schedule, 0, timeSlots);
return schedule;
}
int main() { vector<string> courses = { "C1", "C2", "C3", "C4" };
map<string, vector<string>> students = {
    {"S1", {"C1", "C2"}},
    {"S2", {"C2", "C3"}},
    {"S3", {"C3", "C4"}}
};

vector<int> timeSlots = { 1, 2, 3 };

clock_t start = clock();

map<string, int> result = naiveSchedule(courses, students, timeSlots);

clock_t end = clock();

cout << "Naive Schedule:\n";

for (auto& p : result) {
    cout << p.first << " -> Slot " << p.second << endl;
}

cout << "Execution Time: "
     << (double)(end - start) / CLOCKS_PER_SEC
     << " seconds\n";

return 0;
}
