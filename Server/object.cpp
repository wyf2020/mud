#include "object.h"
#include "function.h"
#include<iostream>
#include<set>
#include<string>
#include<string.h>
using namespace std;

int object::object_cnt = 0;
map<int,object*>object::OB = createOB();


map<int, object*> object::createOB() {
    map<int, object*>tmp;
    return tmp;
}

object::object(string d, string n) :discribe(d), name(n) {
    object::object_cnt++;
    id = object::object_cnt;
    object::OB[object::object_cnt] = this;
}

string object::get_name() {
    return name;
}

void object::show(SOCKET SID) {
    out(SID,  string("\n����: ") + name + "\n");
    out(SID, string( "\n����: ") + discribe +"\n");
    return;
}

void object::setpos(int p)
{
    this->pos = p;
}

object::~object() {
}

int object::get_id() {
    return id;
}

int object::get_type()
{
    return this->type;
}

int object::get_pos()
{
    return pos;
}

void object::set_name(string n)
{
    name = n;
}

void object::set_acted()
{
    acted = true;
}

string object::typetoname(int type)
{
    string a;
    if (type == 1) a = "��צ��";
    if (type == 2) a = "����Կ��";
    if (type == 10) a = "���ױ���";
    if (type == 11) a = "NPC";
    return a;
}

void object::use(user* u,SOCKET SID) {

}

void object::act(user* u, SOCKET SID)
{

}

box::box(int in, string n, string di ):inside(in),object(di,n) {
    type = 10;
}

box::~box() {
}

void box::act(user* u, SOCKET SID) {
    if (acted == true) {
        out(SID,  string("\n...��ع����������������ѱ����ѹ�һ�գ���ʹ�������Ķ�ͷ���Լ�����...\n"));
        return;
    }
    map<int,int>::iterator it;
    int bj = -1;
    if (u->my_ob.count(2)) bj = 2;
    /*for (it = u->my_ob.begin(); it != u->my_ob.end(); it++) {
        
        if (object::OB[it0>]->get_name() == "����Կ��") { bj = *it; break; }
    }*/
    if (bj==-1) {
        out(SID,  string("\n������û�ܴ򿪱��䣬���������ܵ������ĳ������Կ�׵ĺ���...\n"));
        return;
    }
    u->delete_ob(bj,SID);
    int in = this->inside;
    object& t = *object::OB[in];
    out(SID, string( "\n���ױ��仺���򿪣����ϵĻҳ�����һ˿�����д����Ϣ������𣬳����䶨֮����õ���....\n"));
    t.show(SID);
    this->set_name("�ѱ��򿪵����ױ���");
    u->get_ob(in);
    set_acted();
    return;
}


void bean::act(user* u, SOCKET SID)
{
    if (acted == true) {
        out(SID, string( "\n...��ع������������������������У�ֻ�����������˵���Ӱ����ʹ�������Ķ�ͷ���Լ�����...\n"));
        return;
    }
    out(SID, string( "��·��ǹ����Ķ���,������.."));
    u->get_ob(id);
    this->show(SID);
    set_acted();
    return;
}

void bean::use(user* u, SOCKET SID)
{
    int i;
    out(SID, string( "��ϣ������������צ��ι��...\n"));
    u->show_poke(SID);
    string s;
    s = get(SID);
    if (isnum(s)) i = atoi(s.c_str());
    else {
        out(SID, string("\n���ƺ������˶Բ����ڵ�����Ļþ�..\n"));
    }
    string name;
    int cnt = 0,bj=0;
    for (auto t : u->poke) {
        cnt++;
        if (cnt == i) { pokemon::POKE[t]->exp_up(this->delta_ex,SID); bj = 1; name = pokemon::POKE[t]->get_name(); break; }
    }
    if (bj) out(SID, string( "������ ") + name + "������Ӽᶨ��..\n");
    else out(SID, string( "\n���ƺ������˶Բ����ڵ�����Ļþ�..\n"));
    return;
}

bean::bean(int ex, string n, string di) :delta_ex(ex), object(di, n) {
    type = 1;
}

bean::~bean() {}

npc::npc(vector<string>& s, int ha, string na, string di) :have(ha), sentences(s), object(di, na) {
    type = 11;
}

npc::~npc() {}

void npc::act(user* u, SOCKET SID) {
    string c;
    vector<string>::iterator it;
    if (acted == true) {
        out(SID, name + ": \"" + sentences[cnt_sen-1] +"\"\n");
        return;
    }
    else {
        for (it = sentences.begin() + this->cnt_sen; it != sentences.end(); it++) {
            this->cnt_sen++;
            out(SID,  name + ": \"" + *it + "\"\n");
            out(SID, + "1.���� 2.����\n");
            c= get(SID);
            if (c == "2") { out(SID,  name + ": \"" + "���Ÿ�·����ô�ټ���..." + "\"\n"); return; }
        }
    }
    if (acted == true) return;
    if (this->have) {
        out(SID,  name + ": \"���������" + u->get_name() + "��...���������..ף����ˣ����һ��ѱ����..." + "\"\n");
        u->get_ob(this->have);
        out(SID,  name + "������..\n");
        object::OB[this->have]->show(SID);
    }
    set_acted();
    return;
}

void key::act(user* u, SOCKET SID)
{
    if (acted == true) {
        out(SID, string( "\n...��ع������������������������У�ֻ�����������˵���Ӱ����ʹ�������Ķ�ͷ���Լ�����...\n"));
        return;
    }
    out(SID, string( "�ƺ��������ĳ�Ϧ�ദ�������������,������.."));
    u->get_ob(id);
    this->show(SID);
    set_acted();
}

void key::use(user* u, SOCKET SID)
{
    out(SID, string("\n����õ����ģ����������ڡ�����ȥ�ұ����...\n"));
    return;
}

key::key(string n, string di):object(di,n){
    type = 2;
}

key::~key(){
}
