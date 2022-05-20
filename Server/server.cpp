#include <winsock2.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <map>
#include <windows.h>
#include"function.h"

using namespace std;

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

int cnt = 0;



DWORD WINAPI ThreadProc(
	__in  LPVOID lpParameter
	)
{
	SOCKET AcceptSocket=(SOCKET) lpParameter;
	int uid = 0;
	while (1) {
        if ( uid = Begin(AcceptSocket)) break;
    }
	Welcome(AcceptSocket);

	while (1) {
		if(Begin(AcceptSocket)) break;
	}

	while(1) try {
		user* u = user::umap[uid];
		int pos = u->get_pos();
		maps::MP[pos]->show(AcceptSocket);
		while (1)
		{
			out(AcceptSocket ,string("\n ..����help�Բ鿴��ѡ����..\n"));
			string op = get(AcceptSocket);
			//cout << op.length() << endl;
			if (operate(u, op, AcceptSocket)) break;
		}
	}
	catch (...) {
			break;
	}

	//string s = get(AcceptSocket);
	//cout << s;
	//string prefix = to_string(++cnt);
	//out(AcceptSocket, prefix + ":" +s);

	//��������
	closesocket(AcceptSocket);
	return 0;
}

int main(int argc, char* argv[])
{
	//----------------------
	// Initialize game server.
	Initial();
	//----------------------
	// Initialize Winsock.
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
		wprintf(L"WSAStartup failed with error: %ld\n", iResult);
		return 1;
	}
	//----------------------
	// Create a SOCKET for listening for
	// incoming connection requests.
	SOCKET ListenSocket;
	ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ListenSocket == INVALID_SOCKET) {
		wprintf(L"socket failed with error: %ld\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}
	//----------------------
	// The sockaddr_in structure specifies the address family,
	// IP address, and port for the socket that is being bound.
	sockaddr_in addrServer;
	addrServer.sin_family = AF_INET;
	addrServer.sin_addr.s_addr = htonl(INADDR_ANY); //ʵ������0
	addrServer.sin_port = htons(20131);


	//���׽��ֵ�һ��IP��ַ��һ���˿���
	if (bind(ListenSocket,(SOCKADDR *) & addrServer, sizeof (addrServer)) == SOCKET_ERROR) {
		wprintf(L"bind failed with error: %ld\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	//���׽�������Ϊ����ģʽ�ȴ���������
	//----------------------
	// Listen for incoming connection requests.
	// on the created socket
	if (listen(ListenSocket, 5) == SOCKET_ERROR) {
		wprintf(L"listen failed with error: %ld\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	SOCKADDR_IN addrClient;
	int len=sizeof(SOCKADDR);
	//��һ������ѭ���ķ�ʽ����ͣ�ؽ��տͻ���socket����
	while(1)
	{
		//�������󣬽����������󣬷���һ���µĶ�Ӧ�ڴ˴����ӵ��׽���
		SOCKET AcceptSocket=accept(ListenSocket,(SOCKADDR*)&addrClient,&len);
		if (AcceptSocket == INVALID_SOCKET) {
			cout << "1\n";
			break; //����
		}

		//�����߳�
		DWORD dwThread;
		HANDLE hThread = CreateThread(NULL,0,ThreadProc,(LPVOID)AcceptSocket,0,&dwThread);
		if(hThread==NULL)
		{
			closesocket(AcceptSocket);
			wprintf(L"Thread Creat Failed!\n");
			break;
		}

		CloseHandle(hThread);
	}

	closesocket(ListenSocket);
	WSACleanup();
	return 0;
}

