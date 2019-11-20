#define _WINSOCK_DEPRECATED_NO_WARNINGS


#include "stdafx.h"
#include <string>
#include <iostream>
#include "Winsock2.h" //заголовок WS2_32.dll
#pragma comment(lib, "WS2_32.lib") //экспорт WS2_32.dll
#include "Error.h"
#include <ctime>

using namespace std;

SOCKET cC;

bool GetServerByName(char* call, char* hostname, sockaddr* from, int* flen)
{
	hostent* server;
	int optval = 1;
	if ((cC = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
		throw SetErrorMsgText("socket: ", WSAGetLastError());

	if (setsockopt(cC, SOL_SOCKET, SO_BROADCAST, (char*)&optval, sizeof(int)) == SOCKET_ERROR)
		throw SetErrorMsgText("opt: ", WSAGetLastError());
	if ((server = gethostbyname(hostname)) == NULL)
		throw SetErrorMsgText("ERROR: SERVER NOT EXISTS.", 0);

	SOCKADDR_IN all;
	all.sin_family = AF_INET;
	all.sin_port = htons(2000);
	all.sin_addr.s_addr = INADDR_BROADCAST;
	all.sin_addr.s_addr = ((in_addr*)server->h_addr_list[0])->s_addr;

	char buf[] = "HI";
	if (sendto(cC, call, strlen(call) + 1, NULL, (sockaddr*)&all, sizeof(all)) == SOCKET_ERROR)
		throw SetErrorMsgText("sendto: ", WSAGetLastError());

	char ibuf[50];
	if (recvfrom(cC, ibuf, sizeof(ibuf), NULL, from, flen) == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAETIMEDOUT)
			return false;
		else
			throw SetErrorMsgText("recvfrom: ", WSAGetLastError());
	}

	cout << ibuf << endl;

	if (closesocket(cC) == SOCKET_ERROR)
		throw SetErrorMsgText("closesocket: ", WSAGetLastError());
	return true;
}

void main()
{
	setlocale(LC_CTYPE, "rus");

	WSADATA wsaData;

	char hostname[] = "HI";
	char call[] = "Oh, Spanch Bob";
	try
	{
		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			throw SetErrorMsgText("Startup: ", WSAGetLastError());

		SOCKADDR_IN from;
		memset(&from, 0, sizeof(from));
		int lfrom = sizeof(from);
		GetServerByName(call, hostname, (sockaddr*)&from, &lfrom);
		cout << "Server socket: " << inet_ntoa(from.sin_addr) << ":" << htons(from.sin_port) << endl;

		if (WSACleanup() == SOCKET_ERROR)
			throw SetErrorMsgText("Cleanup: ", WSAGetLastError());
	}
	catch (string errorMsgText)
	{
		cout << "WSAGetLastError: " << errorMsgText << endl;
	}
	system("pause");
}