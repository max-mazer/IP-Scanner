// IpScanner.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Scanner.h"
#include <winsock.h>
#include <vector>
#include <ctime>


using namespace std;

int main()
{
    time_t start, finish;
    Scanner IpScan;
    vector<string> result = IpScan.getIp();
    string addr;
    int ports[12] = { 20,21,25,53,80,123,179,443,500,587,3389 };
    for (int i = 1; i < 255; i++) {
        
        addr = result.at(0) + '.' + result.at(1) + '.' + result.at(2) + '.' + to_string(i);
        cout << "Testing IP address: " << addr << ". Ports Open are: ";
        for (int nI = 0; nI < sizeof(ports) / sizeof(ports[0]); nI++) {
            time(&start);
            IpScan.scan(addr, ports[nI]);
            time(&finish);
            
            if (difftime(finish, start) > 3) {
                cout << "Not reachable";
                break;
            }
        }
        cout << endl;
        
    }


}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
