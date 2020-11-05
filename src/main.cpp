#include "ComputerConnections.h"
#include "SiteAccesses.h"

using namespace std;

int main() {
    cout << endl;
    
    Register r("new_data.csv");
    cout << r.top(3, "18-8-2020");

    cout << endl;
}
