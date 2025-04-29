#include <iostream>
#include <string>
#include <vector>

using namespace std;

int nt, t, top = 0;
vector<char> s(50), NT(10), T(10);
vector<vector<char>> l(10, vector<char>(10, 'f')), tr(10, vector<char>(10, 'f'));

int searchnt(char a) {
    for (int i = 0; i < nt; i++) {
        if (NT[i] == a)
            return i;
    }
    return -1;
}

int searchter(char a) {
    for (int i = 0; i < t; i++) {
        if (T[i] == a)
            return i;
    }
    return -1;
}

void push(char a) {
    s[top] = a;
    top++;
}

char pop() {
    top--;
    return s[top];
}

void installl(int a, int b) {
    if (l[a][b] == 'f') {
        l[a][b] = 't';
        push(T[b]);
        push(NT[a]);
    }
}

void installt(int a, int b) {
    if (tr[a][b] == 'f') {
        tr[a][b] = 't';
        push(T[b]);
        push(NT[a]);
    }
}

int main() {
    int n;
    cout << "Enter the number of productions: ";
    cin >> n;

    // Read productions
    vector<string> pr(n);
    cout << "Enter the productions one by one (e.g., A->BC):\n";
    for (int i = 0; i < n; i++) {
        cin >> pr[i];
    }

    nt = 0;
    t = 0;

    // Collect non-terminals (NT) and terminals (T)
    for (int i = 0; i < n; i++) {
        if (searchnt(pr[i][0]) == -1) {
            NT[nt++] = pr[i][0];
        }
    }

    for (int i = 0; i < n; i++) {
        for (size_t j = 3; j < pr[i].length(); j++) {
            if (searchnt(pr[i][j]) == -1) {
                if (searchter(pr[i][j]) == -1) {
                    T[t++] = pr[i][j];
                }
            }
        }
    }

    // Initialize leading and trailing arrays
    for (int i = 0; i < nt; i++) {
        for (int j = 0; j < t; j++) {
            l[i][j] = 'f';
            tr[i][j] = 'f';
        }
    }

    // Compute leading sets
    for (int i = 0; i < nt; i++) {
        for (int j = 0; j < n; j++) {
            if (NT[searchnt(pr[j][0])] == NT[i]) {
                if (searchter(pr[j][3]) != -1) {
                    installl(searchnt(pr[j][0]), searchter(pr[j][3]));
                } else {
                    for (size_t k = 3; k < pr[j].length(); k++) {
                        if (searchnt(pr[j][k]) == -1) {
                            installl(searchnt(pr[j][0]), searchter(pr[j][k]));
                            break;
                        }
                    }
                }
            }
        }
    }

    while (top != 0) {
        char b = pop();
        char c = pop();
        for (int s = 0; s < n; s++) {
            if (pr[s][3] == b) {
                installl(searchnt(pr[s][0]), searchter(c));
            }
        }
    }

    // Output leading sets
    for (int i = 0; i < nt; i++) {
        cout << "Leading[" << NT[i] << "]\t{";
        for (int j = 0; j < t; j++) {
            if (l[i][j] == 't') cout << T[j] << ",";
        }
        cout << "}\n";
    }

    // Compute trailing sets
    top = 0;
    for (int i = 0; i < nt; i++) {
        for (int j = 0; j < n; j++) {
            if (NT[searchnt(pr[j][0])] == NT[i]) {
                if (searchter(pr[j][pr[j].length() - 1]) != -1) {
                    installt(searchnt(pr[j][0]), searchter(pr[j][pr[j].length() - 1]));
                } else {
                    for (size_t k = pr[j].length() - 1; k >= 3; k--) {
                        if (searchnt(pr[j][k]) == -1) {
                            installt(searchnt(pr[j][0]), searchter(pr[j][k]));
                            break;
                        }
                    }
                }
            }
        }
    }

    while (top != 0) {
        char b = pop();
        char c = pop();
        for (int s = 0; s < n; s++) {
            if (pr[s][3] == b) {
                installt(searchnt(pr[s][0]), searchter(c));
            }
        }
    }

    // Output trailing sets
    for (int i = 0; i < nt; i++) {
        cout << "Trailing[" << NT[i] << "]\t{";
        for (int j = 0; j < t; j++) {
            if (tr[i][j] == 't') cout << T[j] << ",";
        }
        cout << "}\n";
    }

    return 0;
}