#include <iostream>
#include <vector>
#include <queue>
#include "psi.h"
using namespace std;
using namespace psi;

State eval(const string& gates, const string& state){
    State s = State(state);
    for (char g: gates){
        s = Gate(string({g})) * s;
    }
    return s;
}

int main(){
    vector<vector<string>> inputs {{"+", "i", "0"}, {"+", "i", "0"}, {"+", "i", "0"}, {"+", "i", "0"}, {"+", "i", "0"}};
    vector<vector<string>> outputs {{"0", "+", "i"}, {"+", "-i", "1"}, {"0", "i", "+"}, {"1", "i", "+"}, {"1", "-", "i"}};
    for (int i = 0; i < inputs.size(); ++i){
        cout << "mapping: ";
        for (int j = 0; j < inputs[i].size(); ++j){
            cout << '|' << inputs[i][j] << "> -> |" << outputs[i][j] << ">, ";
        }
        cout << endl << "Start searching..." << endl;
        queue<string> nodes;
        nodes.push("");
        string gates;
        int depth = -1, count = 0;
        while (!nodes.empty()){
            gates = nodes.front();
            nodes.pop();
            if ((int)gates.size() > depth){
                depth = gates.size();
            }
            if (count % 1000 == 0){
                for (int j = 0; j < 256; ++j) cout << '\b';
                cout << "# Gates searched: " << count << "| Depth: " << depth << unitbuf;
            }
            bool match = true;
            for (int j = 0; j < inputs[i].size(); ++j){
                if (eval(gates, inputs[i][j]) != outputs[i][j]){
                    match = false;
                    break;
                }
            }
            if (match){
                for (int j = 0; j < 256; ++j) cout << '\b';
                cout << "# Gates searched: " << count << "| Depth: " << depth;
                cout << endl << "Gate found: ";
                for (int j = 0; j < gates.size(); ++j){
                    cout << gates[j];
                    if (j != gates.size() - 1){
                        cout << '-';
                    }
                }
                cout << endl;
                break;
            }
            if (depth >= 18){
                cout << endl << "Max depth reached. Gate not found. " << endl;
                break;
            }
            string add_s = gates, add_h = gates;
            ++count;
            add_s.append("s"), add_h.append("h");
            nodes.push(add_s), nodes.push(add_h);
        }
        cout << endl;
    }
}