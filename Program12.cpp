#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <vector>
using namespace std;

void addDependency(unordered_map<string, vector<string>> &dependencies, const string &parent, const string &child) {
    dependencies[parent].push_back(child);
}

void generateDOT(const unordered_map<string, vector<string>> &dependencies) {
    ofstream file("dependency_graph.dot");
    if (file.is_open()) {
        file << "digraph DependencyGraph {\n";
        for (const auto &dependency : dependencies) {
            string parent = dependency.first;
            file << " \"" << parent << "\"";
            file << ";\n";
            for (const string &child : dependency.second) {
                file << " \"" << parent << "\" -> \"" << child << "\"";
                file << ";\n";
            }
        }
        file << "}\n";
        file.close();
        cout << "Dependency graph generated in 'dependency_graph.dot' file.\n";
    } else {
        cout << "Unable to create the DOT file.\n";
    }
}

int main() {
    unordered_map<string, vector<string>> dependencies;
    char choice;
    do {
        string parent, child;
        cout << "Enter parent: ";
        cin >> parent;
        cout << "Enter child: ";
        cin >> child;
        addDependency(dependencies, parent, child);
        cout << "Do you want to add another dependency? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');
    generateDOT(dependencies);
    return 0;
}
