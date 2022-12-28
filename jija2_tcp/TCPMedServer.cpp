#include <iostream> 
#include <winsock2.h>
#include <windows.h>
#include <string>
#pragma comment (lib, "Ws2_32.lib") 
using namespace std;
#define SRV_PORT 1234 

struct Person {
	int weight;
	int height;
	char secondName[25];
}P;

double getBMI(int height, int weight) {
	return double(weight * 10000) / (height * height);
}

int main() {
	char buff[1024];
	if (WSAStartup(0x0202, (WSADATA*)&buff[0]))
	{
		cout << "Error WSAStartup \n" << WSAGetLastError();   // Ошибка!
		return 1;
	}

	SOCKET s, s_new;
	int from_len;
	//int* IMBData = new int[2];
	sockaddr_in sin, from_sin;
	s = socket(AF_INET, SOCK_STREAM, 0);
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = 0;
	sin.sin_port = htons(SRV_PORT);
	bind(s, (sockaddr*)&sin, sizeof(sin));
	listen(s, 3);
	while (1) {
		from_len = sizeof(from_sin);
		s_new = accept(s, (sockaddr*)&from_sin, &from_len);

		if (s_new == 0) cout << "Client connection error!\n";
		else {
			cout << "New Client was connected!" << endl;
			from_len = recv(s_new, (char*)&P, sizeof(P), 0);
			double BMI = getBMI(P.height, P.weight);
			cout << "Received Data" << endl;
			cout << "Second Name:" << P.secondName << "; Height:" << P.height << "; Weight:" << P.weight << endl;
			cout << BMI << endl;
			send(s_new, (char*)&BMI, sizeof(BMI), 0);
			cout << "Client was disconnected" << endl;
			closesocket(s_new);
		}
	}
	return 0;
}