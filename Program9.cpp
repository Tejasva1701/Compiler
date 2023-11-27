#include <iostream>
#include <unordered_map>
#include <stack>
#include <cctype>
using namespace std;

unordered_map<char, int> symbolTable;

void assignValue(char id, int value) {
    symbolTable[id] = value;
}

int retrieveValue(char id) {
    if (symbolTable.find(id) != symbolTable.end()) {
        return symbolTable[id];
    } else {
        cerr << "Error: Variable " << id << " not defined\n";
        return 0;
    }
}

void E() {
    int T_val = retrieveValue('T');
    assignValue('E', T_val);
}

void E_plus_T() {
    int E_val = retrieveValue('E');
    int T_val = retrieveValue('T');
    assignValue('E', E_val + T_val);
}

void T() {
    int F_val = retrieveValue('F');
    assignValue('T', F_val);
}

void T_times_F() {
    int T_val = retrieveValue('T');
    int F_val = retrieveValue('F');
    assignValue('T', T_val * F_val);
}

void F() {
    int id_val = retrieveValue('id');
    assignValue('F', id_val);
}

void F_paren_E() {
    int E_val = retrieveValue('E');
    assignValue('F', E_val);
}

int main() {
    cout << "Enter a mathematical expression with identifiers (e.g., id * (id + id)): ";
    string input;
    getline(cin, input);
    cout << "Enter the value for id: ";
    int id_value;
    cin >> id_value;
    assignValue('id', id_value);
    T_times_F();
    F_paren_E();
    E_plus_T();
    cout << "Result: " << retrieveValue('E') << endl;
    return 0;
}
