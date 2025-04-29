#include <iostream>
#include <string>
using namespace std;

int main() {
    string statement;
    cout << "Enter a simple statement (e.g., a = b + c * d;): ";
    getline(cin, statement);

    if (statement.back() == ';')
        statement.pop_back();

    char resultVar = statement[0];
    char operand1 = statement[4];
    char op1 = statement[6];
    char operand2 = statement[8];
    char op2 = statement[9];
    char operand3 = statement[10];

    string t1 = "t1 = ";
    t1 += operand2;
    t1 += " ";
    t1 += op2;
    t1 += " ";
    t1 += operand3;

    string t2 = "t2 = ";
    t2 += operand1;
    t2 += " ";
    t2 += op1;
    t2 += " t1";

    string final = "";
    final += resultVar;
    final += " = t2";

    cout << "\nGenerated Intermediate Code:\n";
    cout << t1 << endl;
    cout << t2 << endl;
    cout << final << endl;

    cout << "\nGenerated Pseudo Machine Code:\n";
    cout << "LOAD " << operand2 << endl;
    cout << (op2 == '*' ? "MUL " : "DIV ") << operand3 << endl;
    cout << "STORE t1" << endl;
    cout << "LOAD " << operand1 << endl;
    cout << (op1 == '+' ? "ADD " : "SUB ") << "t1" << endl;
    cout << "STORE t2" << endl;
    cout << "LOAD t2" << endl;
    cout << "STORE " << resultVar << endl;

    return 0;
}