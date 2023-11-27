#include <iostream>
#include <cctype>
#include <cstdlib>
using namespace std;

enum NodeType { OPERATOR, OPERAND };

struct TreeNode {
    char value;
    NodeType type;
    TreeNode* left;
    TreeNode* right;

    TreeNode(char val, NodeType t) : value(val), type(t), left(nullptr), right(nullptr) {}
    ~TreeNode() {
        delete left;
        delete right;
    }
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
        TreeNode* newNode = new TreeNode(op, OPERATOR);
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
        TreeNode* newNode = new TreeNode(op, OPERATOR);
        newNode->left = left;
        newNode->right = right;
        left = newNode;
    }
    return left;
}

TreeNode* factor(const string& input, size_t& pos) {
    if (pos < input.size() && input[pos] == '(') {
        pos++;
        TreeNode* result = expression(input, pos);
        if (pos < input.size() && input[pos] == ')') {
            pos++;
            return result;
        } else {
            cerr << "Error: Missing ')'\n";
            delete result;
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
        char* end;
        double value = strtod(numStr.c_str(), &end);
        if (*end == '\0') {
            return new TreeNode(value, OPERAND);
        } else {
            cerr << "Error: Invalid number format\n";
            return nullptr;
        }
    } else {
        cerr << "Error: Expected a number\n";
        return nullptr;
    }
}

void printTree(TreeNode* root, int indent = 0) {
    if (root == nullptr) {
        return;
    }

    for (int i = 0; i < indent; ++i) {
        cout << " ";
    }

    if (root->type == OPERAND) {
        cout << root->value << endl;
    } else {
        cout << root->value << endl;
        printTree(root->left, indent + 4);
        printTree(root->right, indent + 4);
    }
}

int main() {
    cout << "Enter a mathematical expression: ";
    string input;
    getline(cin, input);
    size_t pos = 0;
    TreeNode* root = expression(input, pos);

    if (root) {
        cout << "Parse Tree:\n";
        printTree(root);

        delete root;
    }

    return 0;
}
