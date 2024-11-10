#include "TableCell.h"

TableCell::TableCell(const string &def_item) {
    items.push_back(def_item);
}

void TableCell::setItems(const vector<string> &v_items) {
    items = v_items;
}

void TableCell::setProdStr(const string &s) {
    produced_str = s;
}

string TableCell::getProdStr() const {
    return produced_str;
}

vector<string> TableCell::getItems() const {
    return items;
}
