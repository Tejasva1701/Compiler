#include <iostream>
#include <string>

using namespace std;

bool isValidString(const string &input) {
    int countA = 0;
    int countB = 0;

    for (char ch : input) {
        if (ch == 'a') {
            countA++;
        } 
        else if (ch == 'b') {
            countB++;
        } 
        else {
            return false;
        }
    }

    return countA % 3 == 0;
}

int main() {
    string input;

    cout << "Enter a string: ";
    cin >> input;

    if (isValidString(input)) {
        cout << input << " belongs to the grammar.\n";
    } else {
        cout << input << " does not belong to the grammar.\n";
    }

    return 0;
}


//grammar that accepts strings having a's in multiple of three.