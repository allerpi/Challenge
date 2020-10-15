#include <iostream>
#include <vector>
#include "Register.h"
#include "ComputerConnections.h"

using namespace std;

int main(){
    cout << endl;
    Register r("data.csv");
    ComputerConnections a(r);

    cout << endl;
}
