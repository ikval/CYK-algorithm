#include "CYK.h"

CYK::CYK(const string &s) {
    str_len = s.size();

    for (auto & ch : s) {
        terminals.push_back(ch);
    }

    for (int i = str_len; i > 0; i--) {
        vector<TableCell*> table_row;
        for (int j = 0; j < i; j++) {
            auto* cell = new TableCell("");
            table_row.push_back(cell);
        }
        table.push_back(table_row);
    }

    for (int i = 0; i < str_len; i++) {
        for (int j = 0; j != str_len - i; j++) {

            string produced_str;
            for (int k = j; k < i + j + 1; k++) {
                produced_str += terminals[k];
            }
            table[i][j]->setProdStr(produced_str);
        }
    }
}

CYK::~CYK() {
    for (auto& row : table) {
        for (auto& cell : row) {
            delete cell;
        }
    }
}

vector<char> CYK::getTerminals() const {
    return terminals;
}

int CYK::getStringLength() const {
    return str_len;
}

