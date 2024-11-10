#include "CFG.h"

using namespace std;

int main() {
    CFG cfg("./src/input-cyk1.json");
    cfg.accepts("baaba");
    return 0;
}