#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

bool startsWith(const string& str, const string& prefix) {
    return (str.compare(0, prefix.length(), prefix) == 0);
}

vector<string> removeLeftFactoring(const vector<string>& productions) {
    vector<string> resolvedProductions;
    for (const string& production : productions) {
        stringstream ss(production);
        string nonTerminal;
        ss >> nonTerminal;

        vector<string> alternatives;
        string symbol;
        ss >> symbol;

        while (ss >> symbol) {
            alternatives.push_back(symbol);
        }

        bool hasLeftFactoring = false;
        for (size_t i = 1; i < alternatives.size(); ++i) {
            if (startsWith(alternatives[i], alternatives[0])) {
                hasLeftFactoring = true;
                break;
            }
        }

        if (hasLeftFactoring) {
            string newNonTerminal = nonTerminal + "'";
            resolvedProductions.push_back(nonTerminal + " -> " + alternatives[0] + " " + newNonTerminal);
            for (size_t i = 1; i < alternatives.size(); ++i) {
                resolvedProductions.push_back(newNonTerminal + " -> " + alternatives[i].substr(alternatives[0].length()) + " | ε");
            }
        } else {
            resolvedProductions.push_back(production);
        }
    }
    return resolvedProductions;
}

int main() {
    vector<string> productions = {
        "S -> a A | a B",
        "A -> b X | ε",
        "B -> c X | ε",
        "X -> d"
    };

    cout << "Original Productions:" << endl;
    for (const string& production : productions) {
        cout << production << endl;
    }

    vector<string> resolvedProductions = removeLeftFactoring(productions);
    cout << "\nProductions after Left Factoring Removal:" << endl;
    for (const string& production : resolvedProductions) {
        cout << production << endl;
    }

    return 0;
}
