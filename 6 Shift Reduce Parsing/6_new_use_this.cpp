#include <iostream>
#include <vector>
#include <stack>
#include <map>
using namespace std;

// Grammar rules: LHS -> RHS
map<string, vector<string>> grammar = {
    {"E", {"E+E", "E*E", "(E)", "i"}}
};

// Function to check if a given string can be reduced
bool can_reduce(const string& str, string& lhs) {
    for (auto& rule : grammar) {
        for (auto& rhs : rule.second) {
            if (str == rhs) {
                lhs = rule.first;
                return true;
            }
        }
    }
    return false;
}

// Function to get stack content as string
string stack_to_string(const vector<string>& st, int start) {
    string s = "";
    for (int i = start; i < st.size(); i++) {
        s += st[i];
    }
    return s;
}

// Shift-reduce parser
bool shift_reduce_parser(vector<string> input) {
    vector<string> stack; // Using vector as a stack for easier access
    input.push_back("$"); // End marker

    while (true) {
        // Try to reduce
        bool reduced = false;
        for (int len = 1; len <= stack.size(); ++len) {
            int start = stack.size() - len;
            string suffix = stack_to_string(stack, start);
            string lhs;
            if (can_reduce(suffix, lhs)) {
                // Apply reduction
                cout << "Reduce: " << suffix << " -> " << lhs << endl;
                for (int i = 0; i < len; ++i) stack.pop_back();
                stack.push_back(lhs);
                reduced = true;
                break; // Restart reduction from top
            }
        }

        if (!reduced) {
            // Shift if not reducible
            if (input[0] != "$") {
                cout << "Shift: " << input[0] << endl;
                stack.push_back(input[0]);
                input.erase(input.begin());
            } else {
                // Input exhausted, check final stack
                if (stack.size() == 1 && stack[0] == "E") {
                    cout << "Accepted" << endl;
                    return true;
                } else {
                    cout << "Rejected" << endl;
                    return false;
                }
            }
        }
    }
}

int main() {
    // Sample input: i*i+i
    vector<string> input = {"i", "*", "i", "+", "i"};

    cout << "Parsing steps:" << endl;
    bool result = shift_reduce_parser(input);
    cout << (result ? "Success" : "Fail") << endl;

    return 0;
}
