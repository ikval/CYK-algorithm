#include "CFG.h"

using namespace std;

int main() {
    CFG cfg("./src/input-cyk1.json");
    cfg.print();
    bool a = cfg.accepts("baaba"); //moet true geven
    cout << a;
    bool b = cfg.accepts("abba"); //moet false geven
    cout << b;
    return 0;
}