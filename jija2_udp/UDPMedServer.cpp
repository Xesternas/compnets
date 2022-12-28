#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <windows.h>
#include <string>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
using namespace std;
#define PORT 999    
#define sHELLO "Hello, STUDENT\n"

struct Person {
    double height;
    double weight;
    char second_name[25];
}P;

double getBMI(double height, double weight) {
    return (weight * 10000) / (height * height);
}

int main() {
    double BMI;
    cout << "UDP DEMO ECHO-SERVER\n";
    
    int err = WSAStartup(MAKEWORD(2, 2), (WSADATA*)&BMI);
    if (err != 0) {
        cout << "WSASTARTUP ERROR: " << WSAGetLastError() << "\n";
        return 1;
    }
    
    SOCKET Lsock;
    Lsock = socket(AF_INET, SOCK_DGRAM, 0);
    if (Lsock == INVALID_SOCKET) {
        cout << "SOCKET() ERROR: " << WSAGetLastError();
        WSACleanup();
        return 1;
    }
   
    sockaddr_in Laddr;
    Laddr.sin_family = AF_INET;
    Laddr.sin_addr.s_addr = INADDR_ANY;
   
    Laddr.sin_port = htons(PORT);
    if (bind(Lsock, (sockaddr*)&Laddr, sizeof(Laddr)))
    {
        cout << "BIND ERROR:" << WSAGetLastError();
        closesocket(Lsock);
        WSACleanup();
        return 1;
    }
    
    while (1) {
        sockaddr_in Caddr;
        int Caddr_size = sizeof(Caddr);
        int bsize = recvfrom(Lsock, (char*)&P, sizeof(P), 0, (sockaddr*)&Caddr, &Caddr_size);
        if (bsize == SOCKET_ERROR)
            cout << "RECVFROM() ERROR:" << WSAGetLastError();
        HOSTENT* hst;
        hst = gethostbyaddr((char*)&Caddr.sin_addr, 4, AF_INET);
        cout << "NEW DATAGRAM!\n" << ((hst) ? hst->h_name : "Unknown host") << "/" << inet_ntoa(Caddr.sin_addr) <<
            "/" << ntohs(Caddr.sin_port) << "/" << P.second_name << " Height:" << P.height << " Weight:" << P.weight << '\n';
        BMI = getBMI(P.height, P.weight);
        
        sendto(Lsock, (char*)&BMI, sizeof(BMI), 0, (sockaddr*)&Caddr, sizeof(Caddr));
    }

    return 0;
}