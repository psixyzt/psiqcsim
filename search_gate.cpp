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
    string inputs = "+i0";
    string outputs = "0i+";
    queue<string> nodes;
    nodes.push("");
    string gates;
    int depth = -1;
    while (!nodes.empty()){
        gates = nodes.front();
        nodes.pop();
        if ((int)gates.size() > depth){
            depth = gates.size();
            cout << "Depth: " << depth << endl;
        }
        bool match = true;
        for (int i = 0; i < inputs.size(); ++i){
            if (eval(gates, string({inputs[i]})) != string({outputs[i]})){
                match = false;
                break;
            }
        }
        if (match){
            cout << gates << endl;
            break;
        }
        string add_s = gates, add_h = gates;
        add_s.append("s"), add_h.append("h");
        nodes.push(add_s), nodes.push(add_h);
    }
}