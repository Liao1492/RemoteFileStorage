#include "Commands.h"
#include <string>
#include <iostream>
#include <WS2tcpip.h>
#include <fstream>

using namespace std;

/*
	UPLOAD FUNCTION
	string choice and Socket s as input
	CONNECT TO THE SERVER AND upload line by line.
*/

void uploadFile(std::string choice, SOCKET s) {
	char buffer[4096]; // Buffer to receive data from server
	int receivedBytes;
	int sendResult;
	string fileName;
	ifstream inputFile;
	string line;
	sendResult = send(s, choice.c_str(), choice.size(), 0);
	ZeroMemory(buffer, 4096);
	receivedBytes = recv(s, buffer, 4096, 0);
	string status;
	if (sendResult == SOCKET_ERROR) {
		throw invalid_argument("Impossible to send to the file to server");
	}
	if (receivedBytes > 0) {
		status = string(buffer, 0, receivedBytes);
	}
	else {
		cout << "No message from server" << endl;
	}
	if (status.compare("SUCCESS") == 0) {
		cout << "Send status:" << status << endl;
		int pos = choice.find(" ");
		fileName = choice.substr(pos+1, choice.size());
		inputFile.open(fileName);
		if (!inputFile) {
			throw invalid_argument("Impossible to open the file");
		}
		else {
			cout << "File opened successfully!" << endl;
		}
		while (getline(inputFile, line)) {
			line += '\n';
			sendResult = send(s, line.c_str(), line.size(), 0);
			if (sendResult == SOCKET_ERROR) {
				throw invalid_argument("Impossible to send line to the server");
			}
			ZeroMemory(buffer, 4096);
			receivedBytes = recv(s, buffer, 4096, 0);
			if (receivedBytes > 0) {
				if (line.compare("#\n") != 0) {
					cout << string(buffer, 0, receivedBytes) << " for " << line;
				}
				else {
					cout << string(buffer, 0, receivedBytes) << " for EOF" << endl;
				}
			}
			else {
				throw invalid_argument("No message from the server");
			}
		}
		inputFile.close(); //CLOSING FILE
		if (line.compare("#\n") != 0) {
			line = "#\n";
			sendResult = send(s, line.c_str(), line.size(), 0);
			if (sendResult == SOCKET_ERROR) {
				throw invalid_argument("Impossible to send line to the server");
			}
			ZeroMemory(buffer, 4096);
			receivedBytes = recv(s, buffer, 4096, 0);
			if (receivedBytes > 0) {
				cout << string(buffer, 0, receivedBytes) << " for EOF" << endl;
			}
			else {
				throw invalid_argument("No message from the server");
			}
		}
		cout << "File uploaded correcly!" << endl;
		
	}
	else {
		cout << "SEND STATUS: FAIL" << endl;
		cout << status<<endl;
	}
}

/*
	DOWNLOAD FUNCTION
	string choice and Socket s as input
	CONNECT TO THE SERVER AND save line by line in local file.
*/

void downloadFile(std::string choice, SOCKET s) {
	char buffer[4096]; // Buffer to receive data from server
	int receivedBytes;
	int sendResult;
	string fileName;
	ofstream outputFile;
	string line;
	sendResult = send(s, choice.c_str(), choice.size(), 0);
	ZeroMemory(buffer, 4096);
	receivedBytes = recv(s, buffer, 4096, 0);
	string status;
	if (sendResult == SOCKET_ERROR) {
		throw invalid_argument("Impossible to send to the file to server");
	}
	if (receivedBytes > 0) {
		status = string(buffer, 0, receivedBytes);
	}
	else {
		cout << "No message from server" << endl;
	}
	if (status.compare("SUCCESS") == 0) {
		cout << "Status:" << status << endl;
		int pos = choice.find(" ");
		fileName = choice.substr(pos + 1, choice.size());
		pos = fileName.find(".");
		fileName.insert(pos, "_downloaded_");
		outputFile.open(fileName);
		if (!outputFile) {
			throw invalid_argument("Impossible to open the file");
		}
		else {
			cout << "File opened successfully!" << endl;
		}
		while (true) {
			ZeroMemory(buffer, 4096);
			receivedBytes = recv(s, buffer, 4096, 0);
		
			if (receivedBytes > 0) {
				line = string(buffer, 0, receivedBytes);
				sendResult = send(s, line.c_str(), line.size(), 0);
				if (line.compare("#") != 0) {
					cout << "Line received: " << line;
					outputFile << line;
					if (sendResult == SOCKET_ERROR) {
						throw invalid_argument("Impossible to send to the file to server");
					}
				}
				else {
					outputFile << line;
					break; // AFTER RECEIVED EOF,CLOSE WHILE LOOP
				}
			}
			else {
				throw invalid_argument("No message from the server");
			}
		}
		cout << "EOF received: " << line << endl;
		outputFile.close();	//CLOSING FILE
		cout << "File saved correctly!" << endl;
	}
	else {
		cout << "Status: FAIL" << endl;
	}
}

/*
	RETRIEVE-EXIT-DEFAULT has the same concept
	string choice and socket as parameters.
	Send to the server and receive an answer
*/
void sendingMess(std::string choice, SOCKET s) { 
	char buffer[4096]; // Buffer to receive data from server
	int receivedBytes;
	int sendResult;
	sendResult = send(s, choice.c_str(), choice.size(), 0);
	ZeroMemory(buffer, 4096);
	receivedBytes = recv(s, buffer, 4096, 0);
	string status;
	if (sendResult == SOCKET_ERROR) {
		throw invalid_argument("Impossible to send to the file to server");
	}
	if (receivedBytes > 0) {
		status = string(buffer, 0, receivedBytes);
		cout << status << endl;
	}
	else {
		cout << "No message from server" << endl;
	}
}
