#include "socketio.h"
#include <map>
#include <string>
#include <iostream>
#include <cstdio>

using namespace std;

map<SOCKET, string> m;

string get(SOCKET socketid) {

    string s = m[socketid];
    m[socketid] = " ";
    int count = s.length(), sendCount = 0, currentPosition = 0;
    char sendBuf[maxc] = {};
    strcpy(sendBuf, s.c_str());
    while (count > 0 && (sendCount = send(socketid, sendBuf + currentPosition, count, 0)) != SOCKET_ERROR)
    {
        count -= sendCount;
        currentPosition += sendCount;
    }
    if (sendCount == SOCKET_ERROR) throw - 1;

    char recvBuf[maxc] = {};
    count = recv(socketid, recvBuf, maxc, 0);
    if (count == 0) throw 0;
    if (count < 0) throw - 1;
    if (recvBuf[count - 1] == '\n') {
        recvBuf[count - 1] = 0;
        count--;
    }
    string ret(recvBuf);
    //cout << "ret = " << ret << endl;
    return ret;
}

void out(SOCKET socketid, string s) {
    if (m.count(socketid) && m[socketid] != " ") {
        m[socketid] += s;
    }
    else {
        m[socketid] = s;
    }
}