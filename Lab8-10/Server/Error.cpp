#include "stdafx.h"
#include <string>
#include "Winsock2.h" //заголовок WS2_32.dll
#pragma comment(lib, "WS2_32.lib") //экспорт WS2_32.dll
using namespace std;

string GetErrorMsgText(int code)
{
	string msgText;
	switch (code)
	{
	case WSAEINTR:
		msgText = "Function error";
		break;
	case WSAEACCES:
		msgText = "Acces error";
		break;
	case WSAEFAULT:
		msgText = "Wrong address";
		break;
	case WSAEINVAL:
		msgText = "Argument error";
		break;
	case WSAEMFILE:
		msgText = "Too much files";
		break;
	case WSAEWOULDBLOCK:
		msgText = "Resourse is blocked";
		break;
	case WSAEINPROGRESS:
		msgText = "Operation in progress";
		break;
	case WSAEALREADY:
		msgText = "Operation already in progress";
		break;
	case WSAENOTSOCK:
		msgText = "Wrong socket";
		break;
	case WSAEDESTADDRREQ:
		msgText = "Location address required";
		break;
	case WSAEMSGSIZE:
		msgText = "Too long message";
		break;
	case WSAEPROTOTYPE:
		msgText = "Wrong type of protocol";
		break;
	case WSAENOPROTOOPT:
		msgText = "Protocol option error";
		break;
	case WSAEPROTONOSUPPORT:
		msgText = "Protocol is unsupported";
		break;
	case WSAESOCKTNOSUPPORT:
		msgText = "Socket type is unsupported";
		break;
	case WSAEOPNOTSUPP:
		msgText = "Operation is unsupported";
		break;
	case WSAEPFNOSUPPORT:
		msgText = "Protocol type is unsupported";
		break;
	case WSAEAFNOSUPPORT:
		msgText = "Address type is unsupported by protocol";
		break;
	case WSAEADDRINUSE:
		msgText = "Adress is already in used";
		break;
	case WSAEADDRNOTAVAIL:
		msgText = "Adress is maybe in used";
		break;
	case WSAENETDOWN:
		msgText = "Network disconnected";
		break;
	case WSAENETUNREACH:
		msgText = "Network is not reachable";
		break;
	case WSAENETRESET:
		msgText = "Network reset";
		break;
	case WSAECONNABORTED:
		msgText = "Program network error";
		break;
	case WSAECONNRESET:
		msgText = "Network connection reset";
		break;
	case WSAENOBUFS:
		msgText = "Too small buffer";
		break;
	case WSAEISCONN:
		msgText = "Socket is already connected";
		break;
	case WSAENOTCONN:
		msgText = "Socket is unconnected";
		break;
	case WSAESHUTDOWN:
		msgText = "Cannot execute send: socket has completed operation";
		break;
	case WSAETIMEDOUT:
		msgText = "The allotted time period has expired";
		break;
	case WSAECONNREFUSED:
		msgText = "Connection rejected";
		break;
	case WSAEHOSTDOWN:
		msgText = "The host is inoperative";
		break;
	case WSAEHOSTUNREACH:
		msgText = "There is no route for the host";
		break;
	case WSAEPROCLIM:
		msgText = "Too many processes";
		break;
	case WSASYSNOTREADY:
		msgText = "Network is not available";
		break;
	case WSAVERNOTSUPPORTED:
		msgText = "This version is not available";
		break;
	case WSANOTINITIALISED:
		msgText = "WS2_32.dll initialization failed";
		break;
	case WSAEDISCON:
		msgText = "Disconnecting in progress";
		break;
	case WSATYPE_NOT_FOUND:
		msgText = "Class not found";
		break;
	case WSAHOST_NOT_FOUND:
		msgText = "Host not found";
		break;
	case WSATRY_AGAIN:
		msgText = "Unauthorized host not found";
		break;
	case WSANO_RECOVERY:
		msgText = "Undefined error";
		break;
	case WSANO_DATA:
		msgText = "There is no record of the requested type";
		break;
	case WSA_INVALID_HANDLE:
		msgText = "The specified event handle is an error";
		break;
	case WSA_INVALID_PARAMETER:
		msgText = "One or more parameters with an error";
		break;
	case WSA_IO_INCOMPLETE:
		msgText = "The I/O object is not in a signal state";
		break;
	case WSA_IO_PENDING:
		msgText = "Operation will complete later";
		break;
	case WSA_NOT_ENOUGH_MEMORY:
		msgText = "Not enough memory";
		break;
	case WSA_OPERATION_ABORTED:
		msgText = "Operation rejected";
		break;
	case WSASYSCALLFAILURE:
		msgText = "System call abort";
		break;
	default:
		break;
	}
	return msgText;
}

string SetErrorMsgText(string msgText, int code)
{
	return msgText + GetErrorMsgText(code);
}
