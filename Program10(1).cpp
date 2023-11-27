#include <iostream>
#include <cctype>
using namespace std;

struct TreeNode {
    char value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char val) : value(val), left(nullptr), right(nullptr) {}
};

TreeNode* expression(const string& input, size_t& pos);
TreeNode* term(const string& input, size_t& pos);
TreeNode* factor(const string& input, size_t& pos);
TreeNode* number(const string& input, size_t& pos);

TreeNode* expression(const string& input, size_t& pos) {
    TreeNode* left = term(input, pos);
    while (pos < input.size() && (input[pos] == '+' || input[pos] == '-')) {
        char op = input[pos++];
        TreeNode* right = term(input, pos);
        TreeNode* newNode = new TreeNode(op);
        newNode->left = left;
        newNode->right = right;
        left = newNode;
    }
    return left;
}

TreeNode* term(const string& input, size_t& pos) {
    TreeNode* left = factor(input, pos);
    while (pos < input.size() && (input[pos] == '*' || input[pos] == '/')) {
        char op = input[pos++];
        TreeNode* right = factor(input, pos);
        TreeNode* newNode = new TreeNode(op);
        newNode->left = left;
        newNode->right = right;
        left = newNode;
    }
    return left;
}

TreeNode* factor(const string& input, size_t& pos) {
    if (input[pos] == '(') {
        pos++;
        TreeNode* result = expression(input, pos);
        if (input[pos] == ')') {
            pos++;
            return result;
        } else {
            cerr << "Error: Missing ')'\n";
            return nullptr;
        }
    } else {
        return number(input, pos);
    }
}

TreeNode* number(const string& input, size_t& pos) {
    string numStr;
    while (pos < input.size() && (isdigit(input[pos]) || input[pos] == '.')) {
        numStr += input[pos++];
    }

    if (!numStr.empty()) {
        return new TreeNode(numStr[0]);
    } else {
        cerr << "Error: Expected a number\n";
        return nullptr;
    }
}

int main() {
    cout << "Enter a mathematical expression: ";
    string input;
    getline(cin, input);
    size_t pos = 0;
    TreeNode* root = expression(input, pos);
    cout << "Parse Tree: ";
    cout << root->value << " ";
    cout << root->left->value << " ";
    cout << root->right->value << "\n";
    delete root->left;
    delete root->right;
    delete root;
    return 0;
}
