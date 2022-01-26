#include <iostream>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <WS2tcpip.h>
#include <map>
#include "menuInterface.h"
#include "Commands.h"
#pragma comment(lib,"ws2_32.lib")

using namespace std;

int connectToServer(SOCKET s,string serverAdd,int serverPort); // Function prototype
string deleteExtraSpaces(string s);


int main() {
	
	string serverAddress;
	string choice ;
	int serverPort; 
	showInterface(); // printing menu.
	cout << "Insert server ip address:";
	cin >> serverAddress;
	cout << "Insert server port number: ";
	cin >> serverPort;
	WSAData data; // structure that contains information about the socket
	WORD version = MAKEWORD(2, 2); // the version of the WSAData we are using, which is 2.2
	int winSockResult = WSAStartup(version, &data);
	if (winSockResult != 0) // 0 means the winsock was open sucessfully 
	{
		cerr << "Impossible to open the winsock. Err#" << winSockResult << endl;
		return -1;
	}
	// Socket creation
	SOCKET tcpSock;
	tcpSock = socket(AF_INET, SOCK_STREAM, 0);// AF_INET IPv4 and SOCK_STREAM is for TCP
	if (tcpSock == INVALID_SOCKET) {
		cerr << "Impossible to create a socket. Err#" << WSAGetLastError() << endl;
		return -1;
	}
	//Server connection
	int connResult;
	try {
		connResult = connectToServer(tcpSock, serverAddress, serverPort);
	}
	catch (invalid_argument& e) {
		cerr<<e.what();
		closesocket(tcpSock);
		WSACleanup();
		return -1;
	}
	cin.ignore();
	map<string, int> switchComm = { {"UPLOAD",1},{"DOWNLOAD",2},{"RETRIEVE",3},{"EXIT",4} }; // MAP client functions to integer for switch
	string comm; // command to be executed
	clear_screen(); // clean prompt command.
	do {
		interfaceOptions(serverAddress,serverPort);
		getline(cin, choice);
		choice = deleteExtraSpaces(choice);
		int pos = choice.find(" ");
		if (pos < 0) {
			pos = choice.size();
		}
		std::transform(choice.begin(), choice.begin()+pos, choice.begin(), ::toupper); // make the input uppercase so our program is not case sensitive
		comm = choice.substr(0, pos);
		switch (switchComm[comm])
		{
		case 1:
			showServerData(serverAddress, serverPort);
			try
			{
				uploadFile(choice, tcpSock);
			}
			catch (invalid_argument& e)
			{
				cerr << e.what();
			}	
			break;
		case 2:
			showServerData(serverAddress, serverPort);
			try
			{
				downloadFile(choice, tcpSock);
			}
			catch (invalid_argument& e)
			{
				cerr << e.what();
			}
			break;
		case 3:
			showServerData(serverAddress, serverPort);
			try
			{
				sendingMess(choice, tcpSock);
			}
			catch (invalid_argument& e)
			{
				cerr << e.what();
			}
			break;
		case 4:
			std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);
			showServerData(serverAddress, serverPort);
			try
			{
				sendingMess(choice, tcpSock);
			}
			catch (invalid_argument& e)
			{
				cerr << e.what();
			}
			closesocket(tcpSock);
			WSACleanup();
			break;
		default:
			showServerData(serverAddress, serverPort);
			try
			{
				sendingMess(choice, tcpSock);
			}
			catch (invalid_argument& e)
			{
				cerr << e.what();
			}
			break;
		}
	} while (choice.compare("exit") != 0);
	
	return 0;
	
}

int connectToServer(SOCKET s, string serverAdd, int serverPort)
{
	//Defining hint structure. "Helping" our system telling it some information(such as using Ipv4)
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(serverPort);
	inet_pton(AF_INET, serverAdd.c_str(), &hint.sin_addr);

	//Trying the connection

	int connResult = connect(s, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR) {
		throw invalid_argument("Can't connect to the server with IP address:" +serverAdd );
	}
	else {
		return connResult;
	}
}

string deleteExtraSpaces(string s) {
	for (int i = s.size() - 1; i >= 0; i--)
	{
		if (s[i] == ' ' && s[i] == s[i - 1]) //added equal sign
		{
			s.erase(s.begin() + i);
		}
	}
	return s;
}
