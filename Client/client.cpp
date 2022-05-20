#include <winsock2.h>
#include <stdio.h>
#include <windows.h>
#include <io.h>
#include <iostream>
#include <string>
using namespace std;

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

bool isnum(string s);

int main(int argc, char* argv[])
{
    //----------------------
    // Initialize Winsock.
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        wprintf(L"WSAStartup failed with error: %ld\n", iResult);
        return 1;
    }

    //----------------------
    // Create a SOCKET for connecting to server
    SOCKET ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ConnectSocket == INVALID_SOCKET) {
        printf("Error at socket(): %ld\n", WSAGetLastError() );
        WSACleanup();
        return 1;
    }
    //----------------------
    // The sockaddr_in structure specifies the address family,
    // IP address, and port for the socket that is being bound.
    string type;
    string addr;
    while (1) {
        cout << "请选择您希望进行的游戏方式: 1. 本地游玩 2. 多人联机\n";
        cin >> type;
        if (!isnum(type)) {
            cout << "请输入 1 或 2\n";
        }
        else break;
    }
    if (type == "2") { 
        cout << "请输入服务器的IP地址: (例如 127.0.0.1）";
        cin >> addr;
    }
    else addr = "127.0.0.1";
    sockaddr_in addrServer;
    addrServer.sin_family = AF_INET;
    addrServer.sin_addr.s_addr = inet_addr(addr.c_str());
    addrServer.sin_port = htons(20131);

	//----------------------
    // Connect to server.
    iResult = connect( ConnectSocket, (SOCKADDR*) &addrServer, sizeof(addrServer) );
    if ( iResult == SOCKET_ERROR) {
        closesocket (ConnectSocket);
        printf("Unable to connect to server: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

	char buf[1024+1];
	char buf2[1024+1];
	//以一个无限循环的方式，不停地接收输入，发送到server
	while(1)
	{
        int count = recv(ConnectSocket, buf2, 1024, 0);
        if (count == 0)break;//被对方关闭
        if (count == SOCKET_ERROR)break;//错误count<0
        buf2[count] = '\0';
        string sbuf2(buf2);
        if(sbuf2.length() != 1 || sbuf2[0] != ' ')
            cout << sbuf2 << flush;
        
        string sbuf;
        cin >> sbuf;
        strcpy(buf, sbuf.c_str());
        count = sbuf.length();
        int sendCount = 0;
        int currentPosition = 0;
		while( count>0 && (sendCount=send(ConnectSocket ,buf+currentPosition,count,0))!=SOCKET_ERROR)
		{
			count-=sendCount;
			currentPosition+=sendCount;
		}
		if(sendCount==SOCKET_ERROR)break;
		
		
	}
	//结束连接
	closesocket(ConnectSocket);
	WSACleanup();
	return 0;
}

bool isnum(string s)
{
    int l = s.length();
    for (int i = 0; i < l; i++) {
        if (s[i] < '0' || s[i]>'9') return false;
    }
    return true;
}