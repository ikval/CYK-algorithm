#ifndef CYK_ALGORITHM_TABLECELL_H
#define CYK_ALGORITHM_TABLECELL_H

#include <string>
#include <vector>
using namespace std;

class TableCell {
private:
    vector<string> items;
    string produced_str;

public:
    explicit TableCell(const string& def_item);

    void setItems(const vector<string>& v_items);

    void setProdStr(const string& s);

    string getProdStr() const;

    vector<string> getItems() const;
};


#endif //CYK_ALGORITHM_TABLECELL_H
