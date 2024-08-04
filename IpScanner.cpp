

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
    //Init variables
    
    int ports[12] = { 20,21,25,53,80,123,179,443,500,587,3389 }; //most common ports found on a cloudfare page

    for (int i = 1; i < 255; i++) { //main loop
        addr = result.at(0) + '.' + result.at(1) + '.' + result.at(2) + '.' + to_string(i);
        cout << "Testing IP address: " << addr << ". Ports Open are: ";
        for (int nI = 0; nI < sizeof(ports) / sizeof(ports[0]); nI++) {
            time(&start);
            IpScan.scan(addr, ports[nI]);
            time(&finish);
            
            if (difftime(finish, start) > 3) { //easy way to get around long wait times by making them slightly shorter
                cout << "Not reachable";
                break;
            }
        }
        cout << endl;
        
    }


}


