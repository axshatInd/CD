#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

typedef map<char, vector<string>> AugmentedGrammar;

struct AugmentedProduction {
    char lhs;
    string rhs;
    AugmentedProduction(char _lhs, string _rhs) : lhs(_lhs), rhs(_rhs) {}
};

class LR0Item {
public:
    vector<AugmentedProduction*> productions;
    map<char, int> gotos;

    void Push(AugmentedProduction* p) { productions.push_back(p); }
    bool Contains(string prod) {
        for (auto& p : productions) {
            if (string(1, p->lhs) + "->" + p->rhs == prod) return true;
        }
        return false;
    }
};

void add_closure(char lookahead, LR0Item& item, AugmentedGrammar& grammar) {
    if (!isupper(lookahead)) return;
    for (auto& rhs : grammar[lookahead]) {
        string prod = "@" + rhs;
        if (!item.Contains(string(1, lookahead) + "->" + prod)) {
            item.Push(new AugmentedProduction(lookahead, prod));
        }
    }
}

void get_LR0_items(vector<LR0Item>& lr0items, AugmentedGrammar& grammar, int itemid, map<string, int>& globalGoto) {
    for (int i = 0; i < lr0items[itemid].productions.size(); i++) {
        string rhs = lr0items[itemid].productions[i]->rhs;
        char lookahead = rhs[rhs.find('@') + 1];
        add_closure(lookahead, lr0items[itemid], grammar);
    }

    for (int i = 0; i < lr0items[itemid].productions.size(); i++) {
        char lhs = lr0items[itemid].productions[i]->lhs;
        string rhs = lr0items[itemid].productions[i]->rhs;
        string production = string(1, lhs) + "->" + rhs;
        char lookahead = rhs[rhs.find('@') + 1];

        if (lookahead == '\0') {
            cout << "\t" << production << endl;
            continue;
        }

        if (lr0items[itemid].gotos.find(lookahead) == lr0items[itemid].gotos.end()) {
            if (globalGoto.find(production) == globalGoto.end()) {
                lr0items.push_back(LR0Item());
                string newRhs = rhs;
                swap(newRhs[rhs.find('@')], newRhs[rhs.find('@') + 1]);
                lr0items.back().Push(new AugmentedProduction(lhs, newRhs));
                lr0items[itemid].gotos[lookahead] = lr0items.size() - 1;
                globalGoto[production] = lr0items.size() - 1;
                cout << "\t" << production << " goto(" << lookahead << ") = I" << globalGoto[production] << endl;
            } else {
                lr0items[itemid].gotos[lookahead] = globalGoto[production];
            }
        } else {
            int nextItem = lr0items[itemid].gotos[lookahead];
            string newRhs = rhs;
            swap(newRhs[rhs.find('@')], newRhs[rhs.find('@') + 1]);
            if (!lr0items[nextItem].Contains(string(1, lhs) + "->" + newRhs)) {
                lr0items[nextItem].Push(new AugmentedProduction(lhs, newRhs));
            }
        }
    }
}

void load_grammar(AugmentedGrammar& grammar, vector<LR0Item>& lr0items) {
    string lhs, rhs, production;
    getline(cin, lhs);
    grammar['\''].push_back(lhs);
    lr0items[0].Push(new AugmentedProduction('\'', "@" + lhs));
    while (getline(cin, production)) {
        if (production.empty()) break;
        auto pos = production.find("->");
        lhs = production.substr(0, pos);
        rhs = production.substr(pos + 2);
        grammar[lhs[0]].push_back(rhs);
        lr0items[0].Push(new AugmentedProduction(lhs[0], "@" + rhs));
    }
}

int main() {
    int itemid = 0;
    AugmentedGrammar grammar;
    vector<LR0Item> lr0items(1);
    map<string, int> globalGoto;

    cout << "Augmented Grammar\n-----------------\n";
    load_grammar(grammar, lr0items);

    cout << "\nSets of LR(0) Items\n-------------------\n";
    while (itemid < lr0items.size()) {
        cout << "I" << itemid << ":\n";
        get_LR0_items(lr0items, grammar, itemid, globalGoto);
        itemid++;
    }
    return 0;
}