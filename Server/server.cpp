#include <winsock2.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <map>
#include <windows.h>
#include <thread>
#include"function.h"

using namespace std;

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

int cnt = 0;
map<int, SOCKET> UID2SID;
map<SOCKET, int> SID2UID;

map<int, communicator> comap;


DWORD WINAPI ThreadProc(
	__in  LPVOID lpParameter
	)
{
	SOCKET AcceptSocket=(SOCKET) lpParameter;
	int uid = 0;
	while (1) {
		if (uid = Begin(AcceptSocket)) {
			if (!UID2SID.count(uid)) UID2SID[uid] = AcceptSocket;
			if (!SID2UID.count(AcceptSocket)) SID2UID[AcceptSocket] = uid;
			if (!comap.count(uid)) comap[uid] = communicator(uid);
			break;
		}
    }
	Welcome(AcceptSocket);
	user* u;
	u = user::umap[uid];
	if (u->Is_Online()) {
		out(AcceptSocket, string("\n ..�����ظ���½,������������..\n"));
		Sleep(3000);
		closesocket(AcceptSocket);
		return 0;
	}
	u->online();
	while(1) try {
	
		int pos = u->get_pos();
		maps::MP[pos]->show(AcceptSocket);
		while (1)
		{	
			cout << uid << " " << comap[uid].get_asked() << endl;
			if (comap[uid].get_asked()) {// been invited to fight
				int askeruid = comap[uid].get_askeruid();
				out(AcceptSocket, user::umap[askeruid]->get_name() + "���㷢���ս, �Ƿ����(y/n)?\n");
				while (1) {
					string yn = get(AcceptSocket);
					if (yn[0] == 'y' || yn[0] == 'Y') {
						comap[askeruid].set_reply(1);
						while (1) {
							this_thread::sleep_for(chrono::milliseconds(100));
							if (comap[uid].get_finish()) {
								comap[uid].init();
								break;
							}
						}
						break;
					}
					else if (yn[0] == 'n' || yn[0] == 'N') {
						comap[askeruid].set_reply(2);
						break;
					}
					else {
						out(AcceptSocket, string("������'y'���ܶ�ս������'n'�ܾ���ս\n"));
						continue;
					}
				}

			}
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
	//cout << "????????????????????/\n";
	u->offline();
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

