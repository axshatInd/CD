#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>

using namespace std;

// Structure to represent a quadruple
struct Quadruple {
    string op;    // Operation (e.g., +, -, *, /)
    string arg1;  // First operand
    string arg2;  // Second operand
    string result; // Result of the operation

    Quadruple(string o, string a1, string a2, string res)
        : op(o), arg1(a1), arg2(a2), result(res) {}
};

// Structure to represent a triple
struct Triple {
    string op;    // Operation (e.g., +, -, *, /)
    int arg1;     // Index of first operand in symbol table
    int arg2;     // Index of second operand in symbol table

    Triple(string o, int a1, int a2) : op(o), arg1(a1), arg2(a2) {}
};

// Structure to represent an indirect triple
struct IndirectTriple {
    int index; // Index of the operation in the triples list
    string result; // Result name

    IndirectTriple(int idx, string res) : index(idx), result(res) {}
};

class IntermediateCodeGenerator {
private:
    vector<Quadruple> quadruples;
    vector<Triple> triples;
    vector<IndirectTriple> indirectTriples;
    unordered_map<string, int> symbolTable;
    int tempCount = 0;

    string generateTemp() {
        return "t" + to_string(tempCount++);
    }

public:
    void generateQuadruples(string op, string arg1, string arg2) {
        string result = generateTemp();
        quadruples.push_back(Quadruple(op, arg1, arg2, result));
    }

    void generateTriples(string op, int arg1, int arg2) {
        triples.push_back(Triple(op, arg1, arg2));
    }

    void generateIndirectTriples(int index, string result) {
        indirectTriples.push_back(IndirectTriple(index, result));
    }

    void printQuadruples() {
        cout << "Quadruples: " << endl;
        for (auto& quad : quadruples) {
            cout << "(" << quad.op << ", " << quad.arg1 << ", " << quad.arg2 << ", " << quad.result << ")" << endl;
        }
    }

    void printTriples() {
        cout << "Triples: " << endl;
        for (auto& trip : triples) {
            cout << "(" << trip.op << ", " << trip.arg1 << ", " << trip.arg2 << ")" << endl;
        }
    }

    void printIndirectTriples() {
        cout << "Indirect Triples: " << endl;
        for (auto& indirect : indirectTriples) {
            cout << "(" << indirect.index << ", " << indirect.result << ")" << endl;
        }
    }

    void processExpression(string expression) {
        istringstream expr(expression);
        string operand1, operand2, op;

        while (expr >> operand1 >> op >> operand2) {
            // Generate symbol table entry for operands
            if (symbolTable.find(operand1) == symbolTable.end()) {
                symbolTable[operand1] = symbolTable.size();
            }
            if (symbolTable.find(operand2) == symbolTable.end()) {
                symbolTable[operand2] = symbolTable.size();
            }

            // Generate intermediate code in all three forms
            generateQuadruples(op, operand1, operand2);

            int arg1 = symbolTable[operand1];
            int arg2 = symbolTable[operand2];
            generateTriples(op, arg1, arg2);

            string tempResult = generateTemp();
            generateIndirectTriples(triples.size() - 1, tempResult); // Use the index of the last triple
        }
    }
};

int main() {
    IntermediateCodeGenerator generator;
    string expression;

    // Prompt user for input expression
    cout << "Enter an arithmetic expression (e.g., a + b * c): ";
    getline(cin, expression); // Get the full line as input

    generator.processExpression(expression);

    // Printing intermediate code forms
    generator.printQuadruples();
    generator.printTriples();
    generator.printIndirectTriples();

    return 0;
}
