#ifndef CFG_H
#define CFG_H

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "Production.h"
#include "cyk/CYK.h"

using namespace std;

class CFG {
private:
    vector<string> V;
    vector<string> T;
    vector<Production> P;
    string S;

public:
    CFG(const string& filePath);

    void print() const;

    vector<string> addInstantCandidates(const string& produced_str);

    void printCYKTable(CYK* cyk) const;

    bool accepts(const string& s);
};

#endif // CFG_H
