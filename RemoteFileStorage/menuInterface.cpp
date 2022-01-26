#include "menuInterface.h"
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

/*
	FUNCTION TO CLEAN THE SCREEN
	DEPENDING on the OS, we either use system("cls") or system("clean");
*/
void clear_screen() {
	{
#ifdef _WIN32
		std::system("cls");
#else
		std::system("clear");
#endif
	}
}

void showInterface() {
	string title = " Remote File Storage";
	int a = 0;
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < 60; i++) {
			if (j != 1) {
				cout << "*";
			}
			else if (j == 1 && (i == 0 || i == 59)) {
				cout << "*";
			}
			else {
				if (a < title.size()) {
					cout << title[a];
					a++;
				}
				else {
					cout << " ";
				}
			}
		}
		cout << endl;
	}
};

void interfaceOptions(string serverAddress,int portAddr) {
	cout << endl;
	showInterface();
	cout << "Currently connected to: " << serverAddress;
	cout << "  Port: " << portAddr<<endl;
	for (int i = 0; i < 60; i++) {
		cout << "*";
	}
	cout << endl;
	cout << "This client offers the several functions( EXIT to exit):"<<endl;
	cout << "-Upload" << endl;
	cout << "-Download" << endl;
	cout << "-Retrieve" << endl;
	for (int i = 0; i < 60; i++) {
		cout << "*";
	}
	cout << endl << ">>";
}

void showServerData(std::string serverAddress, int portAddr) {
	clear_screen();
	cout << endl<<"Currently connected to: " << serverAddress;
	cout << " and Port: " << portAddr << endl<<endl;
}
