#include <string>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <iostream>
#pragma comment (lib, "Ws2_32.lib")
#pragma warning(disable: 4996)
using namespace std;
#define request "GET/ HTTP/1.1\r\n Host: localhost \r\n\r\n"

#define max_packet_size 65535

int main() {
	WSADATA ws;
	SOCKET s;
	sockaddr_in adr;
	HOSTENT* hn;

	char buff[max_packet_size];

	if (WSAStartup(0x0202, &ws) != 0) { return -1; }

	if (INVALID_SOCKET == (s = socket(AF_INET, SOCK_STREAM, 0))) {
		return -1;
	}

	if (NULL == (hn = gethostbyname("localhost")))
	{
		return -1;
	}

	adr.sin_family = AF_INET;
	((unsigned long*)&adr.sin_addr)[0] =
		((unsigned long**)hn->h_addr_list)[0][0];
	adr.sin_port = htons(8000);

	if (SOCKET_ERROR == connect(s, (sockaddr*)&adr, sizeof(adr)))
	{
		int res = WSAGetLastError();
		return -1;
	}

	if (SOCKET_ERROR == send(s, (char*)&request, sizeof(request), 0)) {
		int res = WSAGetLastError();
		return -1;
	}

	int len = 0;

	do {
		if (SOCKET_ERROR == (len = recv(s, (char*)&buff, max_packet_size, 0))) {
			int res = WSAGetLastError();
			return -1;
		}
		buff[len] = 0;
		cout << buff;
	} while (len != 0);

	Sleep(5000);

	if (SOCKET_ERROR == closesocket(s)) {
		return -1;}

	return 0;
}
