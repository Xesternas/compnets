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

struct Student
{
    string Name;
    int val[4];
}P;

int answer;


int main() {
    cout << "Server on:\n";

    int err = WSAStartup(MAKEWORD(2, 2), (WSADATA*)&answer);
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
        cout << "New info\n" << P.Name << '\n';

        answer = 60000;
        for (int i = 0; i < 4; i++)
        {
            switch (P.val[i])
            {
            case 5: if (answer >= 50000) answer = 50000;

                break;
            case 4: if (answer >= 40000) answer = 40000;

                break;
            case 3: if (answer >= 30000) answer = 30000;

                break;
            case 2: if (answer > 22000) answer = 20000;
                if (answer >= 20000)
                    answer = answer + pow(10, i);
                break;
            }
        }

        sendto(Lsock, (char*)&answer, sizeof(answer), 0, (sockaddr*)&Caddr, sizeof(Caddr));
    }

    return 0;
}
