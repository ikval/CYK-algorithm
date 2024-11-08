#include "CFG.h"
#include "src/json.hpp"
#include <fstream>
using json = nlohmann::json;

CFG::CFG(const string& filename) {
    ifstream file(filename);

    json j;
    file >> j;

    file.close();

    V = j["Variables"].get<vector<string>>();
    sort(V.begin(), V.end());

    T = j["Terminals"].get<vector<string>>();
    sort(T.begin(), T.end());

    for (const auto& prod : j["Productions"]) {
        string head = prod["head"];
        auto body = prod["body"].get<vector<string>>();
        P.emplace_back(head, body);
    }

    sort(P.begin(), P.end(), [](const Production& a, const Production& b) {
        if (a.getHead() == b.getHead()) {
            return a.getBody().empty() && !b.getBody().empty();
        }
        if (a.getHead() == "BINDIGIT" && b.getHead() == "S") {
            return true;
        }
        return a.getHead() < b.getHead();
    });

    S = j["Start"];
}

void CFG::print() const {
    cout << "V = {";
    for (auto it = V.begin(); it != V.end(); ++it) {
        if (it != V.begin()) cout << ", ";
        cout << *it;
    }
    cout << "}" << endl;

    cout << "T = {";
    for (auto it = T.begin(); it != T.end(); ++it) {
        if (it != T.begin()) cout << ", ";
        cout << *it;
    }
    cout << "}" << endl;

    cout << "P = {" << endl;
    for (const auto& production : P) {
        const string& head = production.getHead();
        const vector<string>& body = production.getBody();

        cout << "    " << head << " -> `";

        if (body.empty()) {
            cout << "`" << endl;
        } else {
            for (auto it = body.begin(); it != body.end(); ++it) {
                if (it != body.begin()) cout << " ";
                cout << *it;
            }
            cout << "`" << endl;
        }
    }
    cout << "}" << endl;

    cout << "S = " << S << endl;
}


