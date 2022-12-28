#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <string>
#include <windows.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
using namespace std;
#define PORT 999
#define SERVERADDR "192.168.1.45" // IP-адрес сервера

string* predmet = new string[4];

struct Student
{
    string Name;
    int val[4];
}P;

int answer;


int main()
{
    predmet[0] = "OOP";
    predmet[1] = "Physic";
    predmet[2] = "Math";
    predmet[3] = "DIf";

    cout << "Type your data:" << endl;

    int err = WSAStartup(MAKEWORD(2, 2), (WSADATA*)&P);
    if (err != 0) {
        cout << "WSASTARTUP ERROR: " << WSAGetLastError() << "\n";
        return 1;
    }


    SOCKET my_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (my_sock == INVALID_SOCKET) {
        cout << "SOCKET() ERROR: " << WSAGetLastError() << "\n";
        WSACleanup();
        return -1;
    }

    HOSTENT* hst;
    sockaddr_in Daddr;
    Daddr.sin_family = AF_INET;
    Daddr.sin_port = htons(PORT);

    if (inet_addr(SERVERADDR))
        Daddr.sin_addr.s_addr = inet_addr(SERVERADDR);
    else
        if (hst = gethostbyname(SERVERADDR))
            Daddr.sin_addr.s_addr =
            ((unsigned long**)hst->h_addr_list)[0][0];
        else {
            cout << "Unknown Host: " << WSAGetLastError() << "\n";
            closesocket(my_sock); WSACleanup(); return -1;
        }

    cout << "Enter Name: " << endl;
    cin >> P.Name;
    for (int i = 0; i < 4; i++) {
        cout << predmet[i] << " grade: " << endl;
        cin >> P.val[i];
    }

    sendto(my_sock, (char*)&P, sizeof(P), 0, (sockaddr*)&Daddr, sizeof(Daddr));
    sockaddr_in SRaddr;
    int SRaddr_size = sizeof(SRaddr);


    int n = recvfrom(my_sock, (char*)&answer, sizeof(answer), 0, (sockaddr*)&SRaddr, &SRaddr_size);
    if (n == SOCKET_ERROR) {
        cout << "RECVFROM() ERROR:" << WSAGetLastError() << "\n";
        closesocket(my_sock);
        WSACleanup();
        return -1;
    }

    cout << answer << endl;
    switch (answer)
    {
    case 30000: cout << "No scholarship" << endl;
        break;
    case 40000: cout << "Scholarship = 1800" << endl;
        break;
    case 50000: cout << "Scholarship = 2500" << endl;
        break;
    default: cout << "No scholarship" << endl;
        if (answer % 10 == 1) cout << "OOP" << endl;
        if (answer % 100 / 10 == 1) cout << "Physic" << endl;
        if (answer % 1000 / 100 == 1) cout << "Math" << endl;
        if (answer % 10000 / 1000 == 1) cout << "Dif" << endl;
        break;
    }
    Sleep(5000);

    closesocket(my_sock);
    WSACleanup();
    return 0;
}
