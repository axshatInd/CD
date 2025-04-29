#include <iostream>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

// Check if character is an operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Function to determine operator precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Convert infix to postfix (suffix)
string infixToPostfix(const string& infix) {
    stack<char> operators;
    string postfix = "";

    for (char c : infix) {
        if (isalnum(c)) {  // Operand
            postfix += c;
        } else if (isOperator(c)) {  // Operator
            while (!operators.empty() && precedence(operators.top()) >= precedence(c)) {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(c);
        }
    }

    while (!operators.empty()) {  // Pop remaining operators
        postfix += operators.top();
        operators.pop();
    }

    return postfix;
}

// Convert infix to prefix
string infixToPrefix(const string& infix) {
    stack<char> operators;
    string prefix = "";
    string reversedInfix = infix;
   
    reverse(reversedInfix.begin(), reversedInfix.end());
   
    for (char& c : reversedInfix) {
        if (isalnum(c)) {  // Operand
            prefix += c;
        } else if (isOperator(c)) {  // Operator
            while (!operators.empty() && precedence(operators.top()) > precedence(c)) {
                prefix += operators.top();
                operators.pop();
            }
            operators.push(c);
        }
    }

    while (!operators.empty()) {  // Pop remaining operators
        prefix += operators.top();
        operators.pop();
    }

    reverse(prefix.begin(), prefix.end());
    return prefix;
}

int main() {
    string expression;
    cout << "Enter an infix expression (single-letter operands, no parentheses): ";
    cin >> expression;

    string prefix = infixToPrefix(expression);
    string postfix = infixToPostfix(expression);

    cout << "Prefix: " << prefix << endl;
    cout << "Suffix (Postfix): " << postfix << endl;

    return 0;
}