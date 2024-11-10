#include "CFG.h"
#include "src/json.hpp"
#include "cyk/CYK.h"
#include <set>
#include <fstream>
#include <iomanip>

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

vector<string> CFG::addInstantCandidates(const string& produced_str) {
    vector<string> var_candidates;

    for (const auto& production : P) {
        const vector<string>& body = production.getBody();

        string body_str = "";
        for (size_t i = 0; i < body.size(); ++i) {
            body_str += body[i];
            if (i < body.size() - 1) {
                body_str += " ";
            }
        }

        if (produced_str == body_str) {
            var_candidates.push_back(production.getHead());
        }
    }

    return var_candidates;
}

void CFG::printCYKTable(CYK* cyk) const {
    int str_len = cyk->getStringLength();
    vector<vector<string>> table_strs(str_len);

    vector<int> col_widths(str_len, 0);

    for (int i = str_len - 1; i >= 0; i--) {
        for (int j = 0; j < str_len - i; j++) {
            vector<string> items = cyk->table[i][j]->getItems();

            string cell_str = items.empty() || items[0] == "-" ? "{}" : "{";

            for (size_t k = 0; k < items.size(); ++k) {
                cell_str += items[k];
                if (k < items.size() - 1) {
                    cell_str += ", ";
                }
            }
            if (!items.empty() && items[0] != "-") {
                cell_str += "}";
            }

            table_strs[i].push_back(cell_str);
            col_widths[j] = max(col_widths[j], static_cast<int>(cell_str.size()));
        }
    }

    for (int i = str_len - 1; i >= 0; i--) {
        cout << "| ";
        for (int j = 0; j < str_len - i; j++) {
            cout << setw(col_widths[j]) << left << table_strs[i][j] << " | ";
        }
        cout << endl;
    }
}


bool CFG::accepts(const string& s) {
    CYK* cyk = new CYK(s);
    int str_len = cyk->getStringLength();

    // Base Case: Length 1 substrings
    for (int j = 0; j < str_len; j++) {
        string prod_str = cyk->table[0][j]->getProdStr();
        vector<string> candidates = addInstantCandidates(prod_str);
        cyk->table[0][j]->setItems(candidates);
    }

    // Recursive Case: Length > 1 substrings
    for (int len = 2; len <= str_len; len++) {
        for (int i = 0; i <= str_len - len; i++) {
            vector<string> candidates;

            for (int k = 1; k < len; k++) {
                vector<string> leftVars = cyk->table[k-1][i]->getItems();
                vector<string> rightVars = cyk->table[len-k-1][i+k]->getItems();

                for (const string& A : leftVars) {
                    for (const string& B : rightVars) {
                        string combined = A + " " + B;

                        vector<string> new_candidates = addInstantCandidates(combined);
                        candidates.insert(candidates.end(), new_candidates.begin(), new_candidates.end());
                    }
                }
            }

            sort(candidates.begin(), candidates.end());
            candidates.erase(unique(candidates.begin(), candidates.end()), candidates.end());
            if (!candidates.empty()) {
                cyk->table[len-1][i]->setItems(candidates);
            }
        }
    }

    printCYKTable(cyk);

    vector<string> topCandidates = cyk->table[str_len-1][0]->getItems();
    bool isAccepted = find(topCandidates.begin(), topCandidates.end(), S) != topCandidates.end();
    cout << (isAccepted ? "true" : "false") << endl;

    delete cyk;
    return isAccepted;
}




