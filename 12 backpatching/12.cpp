#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <memory>

using namespace std;

// Class representing a three-address code (TAC) instruction
class Instruction {
public:
    string op; // Operation (e.g., "JUMP", "IF")
    int target; // Target address for jump instructions (initially -1, means placeholder)
    string label; // Label (if applicable for control flow instructions)

    Instruction(const string& op, int target = -1, const string& label = "")
        : op(op), target(target), label(label) {}
};

// Class representing the backpatching mechanism
class Backpatcher {
private:
    vector<Instruction> instructions; // List of generated instructions
    unordered_map<string, int> label_addresses; // Maps label names to instruction indices
    vector<pair<int, int>> backpatch_list; // List of backpatch operations (index of instruction and target label)

public:
    // Emit a jump instruction with a placeholder target (used for labels that aren't defined yet)
    void emit_jump(const string& label) {
        instructions.push_back(Instruction("JUMP", -1, label)); // -1 means unknown target
        int instruction_index = instructions.size() - 1;
        // Record the backpatch point for this instruction
        backpatch_list.push_back({instruction_index, label_addresses.size()});
    }

    // Define a label at a specific address (instruction index)
    void define_label(const string& label) {
        // The label is defined at the current instruction index
        label_addresses[label] = instructions.size() - 1;
        // Backpatch any jump instruction that targets this label
        backpatch(label);
    }

    // Perform backpatching for a given label
    void backpatch(const string& label) {
        // Find the label address
        if (label_addresses.find(label) == label_addresses.end()) {
            cout << "Error: Label '" << label << "' not defined." << endl;
            return;
        }

        int label_address = label_addresses[label];

        // Go through the list of backpatch points
        for (auto& patch : backpatch_list) {
            int instruction_index = patch.first;
            const string& target_label = instructions[instruction_index].label;

            if (target_label == label) {
                instructions[instruction_index].target = label_address;
            }
        }
    }

    // Print the instructions with backpatched targets
    void print_instructions() const {
        for (int i = 0; i < instructions.size(); i++) {
            cout << i << ": " << instructions[i].op;
            if (instructions[i].target != -1) {
                cout << " -> Target: " << instructions[i].target;
            }
            if (!instructions[i].label.empty()) {
                cout << " (Label: " << instructions[i].label << ")";
            }
            cout << endl;
        }
    }
};

// Example usage
int main() {
    Backpatcher bp;

    // Create jump instructions with unknown targets
    cout << "Generating code with placeholders..." << endl;
    bp.emit_jump("L1"); // Jump to label L1 (placeholder target)
    bp.emit_jump("L2"); // Jump to label L2 (placeholder target)

    // Define the labels and backpatch the jump targets
    cout << "\nDefining labels and backpatching..." << endl;
    bp.define_label("L1"); // Label L1 defined at current instruction index
    bp.define_label("L2"); // Label L2 defined at current instruction index

    // Print the final instructions after backpatching
    cout << "\nFinal instructions after backpatching:" << endl;
    bp.print_instructions();

    return 0;
}