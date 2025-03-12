#include <iostream>
#include <vector>
using namespace std;

int main() {
    char c;
    int n;
    cout << "Enter the parent Non Terminal: ";
    cin >> c;

    string a = string(1, c) + "->";
    vector<string> productions;

    cout << "Enter total number of productions: ";
    cin >> n;

    // Taking input for productions
    for (int i = 0; i < n; i++) {
        string prod;
        cout << "Enter the production " << i + 1 << ": ";
        cin >> prod;
        productions.push_back(prod);
    }

    // Finding the common prefix
    string prefix = productions[0];
    for (int i = 1; i < n; i++) {
        int j = 0;
        while (j < prefix.size() && j < productions[i].size() && prefix[j] == productions[i][j]) {
            j++;
        }
        prefix = prefix.substr(0, j); // Update prefix to common part
    }

    // If there is a common prefix
    if (!prefix.empty() && prefix != productions[0]) {
        string newNonTerminal = string(1, c) + "'";
        a += prefix + newNonTerminal;
        string newProduction = newNonTerminal + "->";

        // Extracting the remaining parts after the prefix
        for (int i = 0; i < n; i++) {
            string suffix = productions[i].substr(prefix.size());
            if (suffix.empty()) suffix = "#"; // Empty part means epsilon (#)
            newProduction += suffix;
            if (i != n - 1) newProduction += "|";
        }

        // Printing the left-factored productions
        cout << "\nAfter left Factoring:\n";
        cout << a << endl;
        cout << newProduction << endl;
    } else {
        // If no left factoring is needed
        cout << "No left factoring required." << endl;
        cout << "Production Rule is: " << a;
        for (int i = 0; i < n; i++) {
            cout << productions[i];
            if (i != n - 1) cout << "|";
        }
        cout << endl;
    }

    return 0;
}
