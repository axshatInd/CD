#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool reduce(stack<string>& st) {
    // Apply reduction rules as long as possible
    if (st.size() >= 1 && st.top() == "id") {
        st.pop();
        st.push("E");
        return true;
    }

    if (st.size() >= 3) {
        string top1 = st.top(); st.pop();
        string top2 = st.top(); st.pop();
        string top3 = st.top(); st.pop();

        // Rule: E + E or E * E
        if (top1 == "E" && (top2 == "+" || top2 == "*") && top3 == "E") {
            st.push("E");
            return true;
        }

        // Rule: ( E )
        if (top1 == ")" && top2 == "E" && top3 == "(") {
            st.push("E");
            return true;
        }

        // If no rule matched, push back in order
        st.push(top3);
        st.push(top2);
        st.push(top1);
    }

    return false;
}

int main() {
    string input;
    cout << "Enter input string with tokens (e.g. id+id*id): ";
    cin >> input;

    stack<string> parseStack;
    string token = "";
    int i = 0;

    cout << "\nShift-Reduce Parsing Steps:\n";
    while (i < input.length()) {
        if (input[i] == 'i' && i + 1 < input.length() && input[i + 1] == 'd') {
            token = "id";
            i += 2;
        } else {
            token = input[i];
            i++;
        }

        parseStack.push(token);
        cout << "Shift: " << token << "\n";

        while (reduce(parseStack)) {
            cout << "Reduce\n";
        }
    }

    // Final reduction check
    while (reduce(parseStack)) {
        cout << "Reduce\n";
    }

    if (parseStack.size() == 1 && parseStack.top() == "E") {
        cout << "\nInput is successfully parsed.\n";
    } else {
        cout << "\nInput string is not valid.\n";
    }

    return 0;
}
