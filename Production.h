#ifndef CFG_PRODUCTION_H
#define CFG_PRODUCTION_H

#include <string>
#include <utility>
#include <vector>

using namespace std;

class Production {
private:
    string head;
    vector<string> body;

public:
    Production(string h, vector<string> b) : head(std::move(h)), body(std::move(b)) {}

    [[nodiscard]] string getHead() const {
        return head;
    }

    [[nodiscard]] const vector<string>& getBody() const {
        return body;
    }
};


#endif //CFG_PRODUCTION_H
