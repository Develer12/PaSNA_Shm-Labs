#define _WINSOCK_DEPRECATED_NO_WARNINGS


#include "stdafx.h"
#include <string>
#include <iostream>
#include "Winsock2.h" //заголовок WS2_32.dll
#pragma comment(lib, "WS2_32.lib") //экспорт WS2_32.dll
#include "Error.h"
#include <ctime>

using namespace std;

int main()
{
	WSADATA wsaData;

	SOCKET cC; //серверный сокет

	SOCKADDR_IN serv; //параметры сокета сервера
	serv.sin_family = AF_INET; //используется IP-адресация
	serv.sin_port = htons(8800); //TCP-порт 2000
	serv.sin_addr.s_addr = inet_addr("192.168.43.192"); //адрес сервера

	SOCKADDR_IN clnt; //параметры сокета клиента
	memset(&clnt, 0, sizeof(clnt)); //обнулить память
	int lclnt = sizeof(clnt); //размер SOCKADDR_IN

	char ibuf[50] = "client: I here "; //буфер вывода
	int lobuf = 0; //количество отправленных байт
	int libuf = 0; //количество принятых байт
	clock_t start, stop;
	try
	{
		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			throw SetErrorMsgText("Startup: ", WSAGetLastError());
		while (true)
		{

			if ((cC = socket(AF_INET, SOCK_DGRAM, NULL)) == INVALID_SOCKET)
				throw SetErrorMsgText("socket: ", WSAGetLastError());

			int count;
			cout << "Number of messages: ";
			cin >> count;

			start = clock();
			for (int i = 1; i <= count; i++)
			{
				string obuf = "hhhhhhhhhdajsfrjvsejvshHello from Client " + to_string(i);
				if ((lobuf = sendto(cC, obuf.c_str(), strlen(obuf.c_str()) + 1, NULL, (sockaddr*)&serv, sizeof(serv))) == SOCKET_ERROR)
					throw SetErrorMsgText("sendto: ", WSAGetLastError());
				cout << obuf << endl;
			}
			string obuf = "";
			if ((lobuf = sendto(cC, obuf.c_str(), strlen(obuf.c_str()) + 1, NULL, (sockaddr*)&serv, sizeof(serv))) == SOCKET_ERROR)
				throw SetErrorMsgText("sendto: ", WSAGetLastError());

			stop = clock();
			cout << "Time for sendto and recvfrom: " << (double)((stop - start) / CLK_TCK) << endl;

		}
		if (closesocket(cC) == SOCKET_ERROR)
			throw SetErrorMsgText("closesocket: ", WSAGetLastError());

		if (WSACleanup() == SOCKET_ERROR)
			throw SetErrorMsgText("Cleanup: ", WSAGetLastError());
	}
	catch (string errorMsgText)
	{
		cout << endl << errorMsgText << endl;
	}
	system("pause");
	return 0;
}