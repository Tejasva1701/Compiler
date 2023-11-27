#include <iostream>
#include <stack>
using namespace std;

int getPrecedence(char op){
    if (op == '+' || op == '-'){
        return 1;
    }     
    else if (op == '*' || op == '/'){
        return 2;
    }
    else{
        return 0;
    }
}

string infixToPostfix(const string &infix){
    string postfix = "";
    stack<char> operatorStack;
    for (char ch : infix){
        if (isalnum(ch)){
            postfix += ch;
        }
        else if (ch == '('){
            operatorStack.push(ch);
        }
        else if (ch == ')'){
            while (!operatorStack.empty() && operatorStack.top() != '('){
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            if (!operatorStack.empty() && operatorStack.top() == '(')
            {
            operatorStack.pop();
            }
        }
        else{
            while (!operatorStack.empty() && getPrecedence(ch) <= getPrecedence(operatorStack.top())){
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.push(ch);
        }
    }
    while (!operatorStack.empty()){
        postfix += operatorStack.top();
        operatorStack.pop();
    }
    return postfix;
}

string infixToPrefix(const string &infix){
    string reverseInfix = "";
    for (int i = infix.length() - 1; i >= 0; i--){
        if (infix[i] == '('){
            reverseInfix += ')';
        }
        else if (infix[i] == ')'){
            reverseInfix += '(';
        }
        else{
            reverseInfix += infix[i];
        }   
    }
    string reversedPostfix = infixToPostfix(reverseInfix);
    string prefix = "";
    for (int i = reversedPostfix.length() - 1; i >= 0; i--){
        prefix += reversedPostfix[i];
    }
    return prefix;
}


int main(){
    string infixExpression;
    char choice;
    cout << "Enter an infix expression: ";
    cin >> infixExpression;
    string postfix = infixToPostfix(infixExpression);
    cout << "Postfix Expression: " << postfix << endl;
    string prefix = infixToPrefix(infixExpression);
    cout << "Prefix Expression: " << prefix << endl;
    return 0;
}


//(A+B)*C-(D+E)/F
