#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

bool startsWith(const string& str, const string& prefix) {
    return (str.compare(0, prefix.length(), prefix) == 0);
}

vector<string> removeLeftRecursion(const vector<string>& productions) {
    vector<string> resolvedProductions;
    for (const string& production : productions) {
        stringstream ss(production);
        string nonTerminal;
        ss >> nonTerminal;

        vector<string> withRecursion;
        vector<string> withoutRecursion;
        string symbol;
        ss >> symbol;

        while (ss >> symbol) {
            if (startsWith(symbol, nonTerminal)) {
                withRecursion.push_back(symbol.substr(nonTerminal.length()));
            } else {
                withoutRecursion.push_back(symbol);
            }
        }

        if (!withRecursion.empty()) {
            string newNonTerminal = nonTerminal + "'";
            resolvedProductions.push_back(nonTerminal + " -> " + withoutRecursion[0] + " " + newNonTerminal);
            resolvedProductions.push_back(newNonTerminal + " -> " + withRecursion[0] + " " + newNonTerminal + " | ε");
            for (size_t i = 1; i < withoutRecursion.size(); ++i) {
                resolvedProductions.push_back(nonTerminal + " -> " + withoutRecursion[i] + " " + newNonTerminal);
            }
        } else {
            resolvedProductions.push_back(production);
        }
    }
    return resolvedProductions;
}

int main() {
    vector<string> productions = {
        "E -> E + T | T",
        "T -> T * F | F",
        "F -> ( E ) | id"
    };

    cout << "Original Productions:" << endl;
    for (const string& production : productions) {
        cout << production << endl;
    }

    vector<string> resolvedProductions = removeLeftRecursion(productions);
    cout << "\nProductions after Left Recursion Removal:" << endl;
    for (const string& production : resolvedProductions) {
        cout << production << endl;
    }

    return 0;
}
