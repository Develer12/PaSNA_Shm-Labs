#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "stdafx.h"
#include <string>
#include <iostream>
#include "Winsock2.h" //заголовок WS2_32.dll
#pragma comment(lib, "WS2_32.lib") //экспорт WS2_32.dll
#include "Error.h"
#include <ctime>


HANDLE hAcceptServer,    // дескриптор потока AcceptServer
hConsolePipe,     // дескриптор потока ConsolePipe 
hGarbageCleaner;   // дескриптор потока GarbageCleaner

DWORD WINAPI AcceptServer(LPVOID pPrm);  // прототипы функций 
DWORD WINAPI ConsolePipe(LPVOID pPrm);
DWORD WINAPI GarbageCleaner(LPVOID pPrm);

using namespace std;

int main()
{
	setlocale(LC_CTYPE, "Russian");

	volatile TalkersCommand  cmd = START;      // команды сервера 
	hAcceptServer = CreateThread(NULL, NULL, AcceptServer,
		(LPVOID)&cmd, NULL, NULL),
		hConsolePipe = CreateThread(NULL, NULL, ConsolePipe,
		(LPVOID)&cmd, NULL, NULL),
		hGarbageCleaner = CreateThread(NULL, NULL, GarbageCleaner,
		(LPVOID)NULL, NULL, NULL);


	WORD wVersionRequested;
	WSADATA wsaData; //информация о реализации Windows Sockets 
	WSAStartup(MAKEWORD(2, 2), &wsaData); //инициализация библиотеки, проверка номера версии; return 0 
	SOCKET sS; // дескриптор сокет
	SOCKADDR_IN sockaddr_in;//структура для хранения сокетов. 
	sockaddr_in.sin_family = AF_INET;
	sockaddr_in.sin_port = htons(2000);
	sockaddr_in.sin_addr.s_addr = INADDR_ANY;
	try
	{

		if (WSAStartup(MAKEWORD(2, 0), &wsaData) != 0)
			throw SetErrorMsgText("Startup: ", WSAGetLastError());
		while (true) {
			if ((sS = socket(AF_INET, SOCK_STREAM, NULL)) == INVALID_SOCKET)
				throw SetErrorMsgText("Socket: ", WSAGetLastError());
			//------
			if (bind(sS, reinterpret_cast<LPSOCKADDR>(&sockaddr_in), sizeof(sockaddr_in)) == SOCKET_ERROR) //связывает сокет с параметрами
				throw SetErrorMsgText("Bind:", WSAGetLastError());
			if (listen(sS, SOMAXCONN) == SOCKET_ERROR)//функция делает сокет доступным для подключений и устанавливает максимальную длину очереди подключений 
				throw SetErrorMsgText("Listen:", WSAGetLastError());
			//--------
			SOCKET cS; //сокет обмена данными с клиентом
			SOCKADDR_IN clnt;
			memset(&clnt, 0, sizeof(clnt));
			int lclnt = sizeof(clnt);
			cout << "The server waits for clients." << endl;
			if ((cS = accept(sS, (sockaddr*)&clnt, &lclnt)) == INVALID_SOCKET)
				throw SetErrorMsgText("accept:", WSAGetLastError());
			//=--------
			char ibuf[30];
			int libuf = 0,
				lobuf = 0;
			cout << "Client " << inet_ntoa(clnt.sin_addr)//IP-адрес в строчный вид
				<< ":" << clnt.sin_port << " conneced." << endl;
			clock_t start = clock();
			while (true) {
				memset(&ibuf, 0, sizeof ibuf);
				if ((libuf = recv(cS, ibuf, sizeof(ibuf), NULL)) == SOCKET_ERROR)
					throw SetErrorMsgText("recv:", WSAGetLastError());
				cout << ibuf << endl;
				if (strlen(ibuf) != 0) {
					if ((libuf = send(cS, ibuf, sizeof(ibuf), NULL)) == SOCKET_ERROR)
						throw SetErrorMsgText("send:", WSAGetLastError());
					if ((libuf = recv(cS, ibuf, sizeof(ibuf), NULL)) == SOCKET_ERROR)
						throw SetErrorMsgText("recv:", WSAGetLastError());
					cout << ibuf << endl;
				}
				else break;
			}
			clock_t end = clock();
			cout << "Time is : " << end - start << "ms" << endl;
			//--------
			if (closesocket(sS) == SOCKET_ERROR)
				throw  SetErrorMsgText("Closesocket:", WSAGetLastError());
		}
		if (WSACleanup() == SOCKET_ERROR)
			throw  SetErrorMsgText("Cleanup:", WSAGetLastError());
	}
	catch (string errorMsgText)
	{
		cout << endl << "WSAGetLastError: " << errorMsgText;
	}
	system("pause");
	return 0;
}
