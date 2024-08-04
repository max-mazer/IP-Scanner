#include "Scanner.h"
#include <iostream>
#include <winsock.h>
#include <vector>
#include <string>
using namespace std;

bool Scanner::timeout() {
	return false;
}

vector<string>  Scanner::getIp() {
	WSADATA ws;
	if (WSAStartup(MAKEWORD(2, 2), &ws)) {
		cout << " try again" << endl;
		WSACleanup();
		exit(EXIT_FAILURE);
	}

	char buff[80];
	string ipList[2];
	vector<string> result;
	if (gethostname(buff, sizeof(buff)) == SOCKET_ERROR) {
		cout << "Error" << WSAGetLastError << "when getting local host name" << endl;
		return result;
	}
	struct hostent* phe = gethostbyname(buff);
	if (phe == 0) {
		cout << "bad host look up" << endl;
		return result;
	}
	for (int nIndex = 0; phe->h_addr_list[nIndex] != 0; ++nIndex)
	{
		struct in_addr addr;
		memcpy(&addr, phe->h_addr_list[nIndex], sizeof(struct in_addr));
		ipList[nIndex] = inet_ntoa(addr);
	}
	size_t start = 0;
	size_t end = ipList[1].find('.');
	while (end != string::npos) {
		result.push_back(ipList[1].substr(start, end - start));
		start = end + 1;
		end = ipList[1].find('.', start);
	}
	result.push_back(ipList[1].substr(start));
	WSACleanup();
	return result;
}
void Scanner::scan(string addr, int port) {
	WSADATA ws;
	if (WSAStartup(MAKEWORD(2, 2), &ws)) {
		cout << " try again" << endl;
		WSACleanup();
		exit(EXIT_FAILURE);
	}

		SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (s == INVALID_SOCKET) {
			std::cerr << "Socket creation failed.\n";
			WSACleanup();
			exit(EXIT_FAILURE);
		}
		sockaddr_in server;
	
		server.sin_family = AF_INET;
		server.sin_addr.s_addr = inet_addr(addr.c_str());
		server.sin_port = htons(port);
		memset(&(server.sin_zero), 0, 8);
		
		int success = connect(s, (SOCKADDR*)&server, sizeof(server));
		
		if (success == SOCKET_ERROR) {
			closesocket(s);
			WSACleanup();
		}
		else {
			cout << port << " ";
		}
		closesocket(s);
		WSACleanup();
}
