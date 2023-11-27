#include <iostream>
#include <cctype>

using namespace std;

bool isValidIdentifier(const string &identifier) {
    if (identifier.empty()) {
        return false;
    }

    if (!isalpha(identifier[0]) && identifier[0] != '_') {
        return false;
    }

    for (char ch : identifier) {
        if (!isalnum(ch) && ch != '_') {
            return false;
        }
    }

    return true;
}

int main() {
    string input;
    
    cout << "Enter an identifier: ";
    cin >> input;

    if (isValidIdentifier(input)) {
        cout << input << " is a valid identifier.\n";
    } 
    else {
        cout << input << " is not a valid identifier.\n";
    }

    return 0;
}
