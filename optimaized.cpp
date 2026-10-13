
// Optimized Algorithm: Graph Coloring
#include <iostream> #include <vector> #include <map> #include <set> #include <string> #include <ctime>
using namespace std;
// Build graph map<string, set<string>> buildGraph( vector<string>& courses, map<string, vector<string>>& students) {
map<string, set<string>> graph;

for (auto& student : students) {
    vector<string>& enrolled = student.second;

    for (int i = 0; i < enrolled.size(); i++) {
        for (int j = i + 1; j < enrolled.size(); j++) {
            graph[enrolled[i]].insert(enrolled[j]);
            graph[enrolled[j]].insert(enrolled[i]);
        }
    }
}

return graph;
}
// Greedy coloring map<string, int> greedyColoring( map<string, set<string>>& graph, vector<string>& courses) {
map<string, int> result;

for (string course : courses) {
    set<int> usedColors;

    for (string neighbor : graph[course]) {
        if (result.count(neighbor)) {
            usedColors.insert(result[neighbor]);
        }
    }

    int color = 1;

    while (usedColors.count(color)) {
        color++;
    }

    result[course] = color;
}

return result;
}
// Main optimized function map<string, int> optimizedSchedule( vector<string>& courses, map<string, vector<string>>& students) {
map<string, set<string>> graph = buildGraph(courses, students);

return greedyColoring(graph, courses);
}
int main() { vector<string> courses = { "C1", "C2", "C3", "C4" };
map<string, vector<string>> students = {
    {"S1", {"C1", "C2"}},
    {"S2", {"C2", "C3"}},
    {"S3", {"C3", "C4"}}
};

clock_t start = clock();

map<string, int> result = optimizedSchedule(courses, students);

clock_t end = clock();

cout << "Optimized Schedule:\n";

for (auto& p : result) {
    cout << p.first << " -> Slot " << p.second << endl;
}

cout << "Execution Time: "
     << (double)(end - start) / CLOCKS_PER_SEC
     << " seconds\n";

return 0;
}
