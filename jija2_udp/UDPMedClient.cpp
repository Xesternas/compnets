#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <string>
#include <windows.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)
using namespace std;
#define PORT 999
#define SERVERADDR "127.0.0.1" // IP-адрес сервера


struct Person {
    double height;
    double weight;
    char second_name[25];
}P;


int main()
{
    cout << "UDP Demo Client\nType your data to get your Body Mass Index\n";

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
   
    cout << "Input Second Name; Height; Weight: ";
    cin >> P.second_name >> P.height >> P.weight;
    sendto(my_sock, (char*)&P, sizeof(P), 0, (sockaddr*)&Daddr, sizeof(Daddr));
    sockaddr_in SRaddr;
    int SRaddr_size = sizeof(SRaddr);
    double BMI = 0;
    int n = recvfrom(my_sock, (char*)&BMI, sizeof(BMI), 0, (sockaddr*)&SRaddr, &SRaddr_size);
    if (n == SOCKET_ERROR) {
        cout << "RECVFROM() ERROR:" << WSAGetLastError() << "\n";
        closesocket(my_sock); 
        WSACleanup();  
        return -1;
    }

    cout << "S=>C(BMI):" << BMI;
    if (BMI >= 18.5 && BMI < 24.9) cout << "(Normal)\n";
    if (BMI < 18.5) cout << "(Underweight)\n";
    if (BMI > 24.9) cout << "(Overweight)\n";
    Sleep(5000);
    
    closesocket(my_sock);
    WSACleanup();     
    return 0;
}