#pragma once
#include <winsock2.h>
#include <string>

using namespace std;

#define maxc 2048 // max chars in one communication

string get(SOCKET socketid);
void out(SOCKET socketid, string s);