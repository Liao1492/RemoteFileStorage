#pragma once
#include <string>
#include <iostream>
#include <WS2tcpip.h>

void uploadFile(std::string choice,SOCKET s);
void downloadFile(std::string choice,SOCKET s);
void sendingMess(std::string choice,SOCKET s);

