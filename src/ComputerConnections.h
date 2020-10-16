// Created by Valeria Pineda and Martha del Rio on 13/10/20.
// Class that saves outgoing IP addresses given a specific IP address.

#ifndef ComputerConnections_h
#define ComputerConnections_h

#include <stack>
#include <queue>
#include <ctime>
#include <stdio.h>
#include "Register.h"

using namespace std;

class ComputerConnections {
private:
    string ip;
    string name;
    stack<string> incoming;
    queue<string> outgoing;

    // generate a random ip given the home network address
    void generate_ip(string home);

public:
    ComputerConnections() = default;
    // give all attributes a value based on Register
    ComputerConnections(Register &r);
    ~ComputerConnections();

    // return computer ip
    string get_ip() { return ip; };

    // get amount of incoming connections (stack)
    int get_incoming_size();

    // get amount of outgoing connections (queue)
    int get_outgoing_size();

    // retrieve last outgoing connection made
    string get_last_ip();

    // check if dest_ip is internal or external
    string check_dest(string dest_ip);

    // prints incoming and outgoing IP addresses
    void print_all();
    
    // checks if computer has n amount of consecutive outgoing connections
    bool check_consecutive(int n);
};

#endif
