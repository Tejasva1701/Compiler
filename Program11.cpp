#include <iostream>
#include <stack>
using namespace std;

int main() {
    stack<int> myStack;

    cout << "Pushing elements onto the stack: ";
    for (int i = 1; i <= 8; ++i) {
        myStack.push(i * 10);
        cout << i * 10 << " ";
    }
    cout << endl;

    cout << "Top element of the stack: " << myStack.top() << endl;

    cout << "Popping elements from the stack: ";
    while (!myStack.empty()) {
        cout << myStack.top() << " ";
        myStack.pop();
    }
    cout << endl;

    if (myStack.empty()) {
        cout << "The stack is empty." << endl;
    } else {
        cout << "The stack is not empty." << endl;
    }

    return 0;
}
