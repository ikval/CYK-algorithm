#ifndef CYK_ALGORITHM_CYK_H
#define CYK_ALGORITHM_CYK_H

#include <utility>
#include <vector>
#include <string>

using namespace std;

class CYK {
private:
    vector<char> terminals;
    int str_len;

public:
    vector<vector<TableCell*>> table;
    explicit CYK(const string& s);
    vector<char> getTerminals() const;
    int getStringLength() const;
};


#endif //CYK_ALGORITHM_CYK_H
