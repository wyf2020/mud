#pragma once
#include <winsock2.h>
#include <string>

using namespace std;

#define maxc 2048 // max chars in one communication

string get(SOCKET socketid);
void out(SOCKET socketid, string s);

class communicator {
private:
	int uid;
	int been_asked;
	int askeruid;
	int been_reply; // 1 yes; 2 no
	int finish;
public:
	communicator() {
		uid = 0;
		been_asked = 0;
		askeruid = 0;
		been_reply = 0;
		finish = 0;
	}
	communicator(const communicator& b) {
		uid = b.uid;
		been_asked = 0;
		askeruid = 0;
		been_reply = 0;
		finish = 0;
	}
	communicator(int uid) : uid(uid) {
		been_asked = 0;
		askeruid = 0;
		been_reply = 0;
		finish = 0;
	}
	int get_asked() { return been_asked; }
	void set_asked(int a) {
		been_asked = 1;
		askeruid = a;
	}
	void cancel_asked() {
		been_asked = 0;
		askeruid = 0;
	}
	int get_reply() {
		return been_reply;
	}
	void set_reply(int yn) {
		been_reply = yn;
	}
	int get_askeruid() { return askeruid; }
	int get_finish() { return finish; }
	void set_finish() { finish = 1; }
	void init() {
		been_asked = 0;
		been_reply = 0;
		askeruid = 0;
		finish = 0;
	}
};