#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

void addEdge(unordered_map<int, vector<int>>& graph, int u, int v) {
    graph[u].push_back(v);
}

void generateDOT(const unordered_map<int, vector<int>>& graph) {
    ofstream file("dag_graph.dot");
    if (file.is_open()) {
        file << "digraph DAG {\n";
        for (const auto& node : graph) {
            int u = node.first;
            file << " " << u << ";\n";
            for (int v : node.second) {
                file << " " << u << " -> " << v << ";\n";
            }
        }
        file << "}\n";
        file.close();
        cout << "DAG graph generated in 'DAG_graph.dot' file.\n";
    } else {
        cout << "Unable to create the DOT file.\n";
    }
}

int main() {
    unordered_map<int, vector<int>> graph;
    int vertices, edges;
    cout << "Enter the number of vertices: ";
    cin >> vertices;
    cout << "Enter the number of edges: ";
    cin >> edges;
    cout << "Enter the edges (from vertex, to vertex):\n";
    for (int i = 0; i < edges; ++i) {
        int u, v;
        cin >> u >> v;
        addEdge(graph, u, v);
    }
    generateDOT(graph);
    return 0;
}
