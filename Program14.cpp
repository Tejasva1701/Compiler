#include <iostream>
#include <unordered_map>
using namespace std;

class SymbolTable {
public:
    void insert(const string& name, const string& symbol_type, const string& scope) {
        if (table.find(name) != table.end()) {
            cerr << "Error: Symbol '" << name << "' already defined in the current scope." << endl;
        } else {
            table[name] = {symbol_type, scope};
            cout << "Symbol '" << name << "' inserted into the symbol table." << endl;
        }
    }

    pair<string, string> lookup(const string& name) {
        auto it = table.find(name);
        if (it != table.end()) {
            return it->second;
        } else {
            return {"", ""};
        }
    }

    void display() {
        cout << "Symbol Table:" << endl;
        cout << "{:<15} {:<15} {:<15}" << endl;
        cout << "---------------------------------------------" << endl;
        for (const auto& entry : table) {
            cout << "{:<15} {:<15} {:<15}" << entry.first << entry.second.first << entry.second.second
                 << endl;
        }
    }

private:
    unordered_map<string, pair<string, string>> table;
};

int main() {
    SymbolTable symbol_table;

    // Inserting symbols into the symbol table
    symbol_table.insert("x", "int", "global");
    symbol_table.insert("y", "float", "local");
    symbol_table.insert("x", "char", "local"); // This will print an error message

    // Looking up symbols
    auto result = symbol_table.lookup("x");
    if (result.first != "") {
        cout << "Symbol found: Type - " << result.first << ", Scope - " << result.second << endl;
    } else {
        cout << "Symbol not found." << endl;
    }

    // Displaying the symbol table
    symbol_table.display();

    return 0;
}
