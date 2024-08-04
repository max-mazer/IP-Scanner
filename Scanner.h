#ifndef Scanner_H
#pragma once
#include <iostream>
#include <winsock.h>
#include <vector>
#include <string>

using namespace std;


class Scanner {
public:
	
	vector<string> getIp();
	void scan(string, int);
	bool timeout();
private:
	fd_set fr, fw, fe;

};
#endif