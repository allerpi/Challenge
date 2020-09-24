#include <iostream>

#include "Register.hpp"
#include "Register.cpp"

using namespace std;

int main(){
    Register<string> a;
    
    a.sort(&Register<string>::compare_port_dest);
    
    return 0;
}
