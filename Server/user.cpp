#include "user.h"
#include<iostream>
using namespace std;

int user::user_cnt = 0;
map<int, user*>user::umap = createumap();

map<int, user*> user::createumap() {
    map<int, user*>tmp;
    return tmp;
}

bool user::catch_poke(int id){
    this->poke.insert(id);
    return true;
}

user::user(string username, string password) :username(username), password(password) {
    pos = 1;
    poke.clear();
    defeat_poke = 0;
    user::user_cnt++;
    id = user::user_cnt;
    user::umap[user::user_cnt] = this;
}

user::~user() {}

string user::get_name() {
    return username;
}

int user::get_id() {
    return id;
}

string user::get_password() {
    return password;
}

bool user::move(char a, SOCKET SID){
    maps* p = maps::MP[pos];
    int tar = 0;
    if (a == 'e') {
        if (p->e == -1) {
            out(SID, string("\n--�����ƺ��������ջ�..--\n"));
            return false;
        } else tar = p->e;
    }else if (a == 'w') {
        if (p->w == -1) {
            out(SID, string("\n--ͨ�����ߵ�·���Ǿ�ͷ..--\n"));
            return false;
        } else tar = p->w;
    }else if (a == 's') {
        if (p->s == -1) {
            out(SID, string("\n--�ϱ�ֻ��һƬ���ޣ�û��̽����ֵ...--\n"));
            return false;
        } else tar = p->s;
    }else if (a == 'n') {
        if (p->n == -1) {
            out(SID, string("\n--����������죬����Խ��..--\n"));
            return false;
        } else tar = p->n;
    }else {
        out(SID, string("\n�����׵Ҷ��Ĺƻ�����ʧȥ�˱���������...\n"));
        return false;
    }
    if (!Check(this,pos,a, SID)) return false;
    else pos = tar;
    return true;
}

void user::delete_ob(int id)
{
    this->my_ob.erase(id);
    return;
}

void user::get_ob(int id)
{
    (this->my_ob).insert(id);
}

void user::insert_poke(int a) {
    poke.insert(a);
}

void user::delete_poke(int a) {
    poke.erase(a);
}

void user::show_poke(SOCKET SID) {
    int cnt = 0;
    for (auto t : poke) {
        cnt++;
        out(SID, to_string(cnt) + "." + pokemon::POKE[t]->get_name() + " ");
    }
    out(SID, string("\n"));
}

void user::show_pack(SOCKET SID)
{
    int cnt = 0;
    map<string, int>cnter;
    cnter.clear();
    set<int>& t = this->my_ob;
    set<int>::iterator it;
    out(SID, string("������һ�±�����������:\n"));
    for (it = t.begin(); it != t.end(); it++) {
        int id = *it;
        object* a = object::OB[id];
        cnter[a->get_name()]++;
    }
    map<string, int>::iterator i;
    for (i = cnter.begin(); i != cnter.end(); i++)
    {
        cnt++;
        out(SID, string("  ") + to_string(cnt) + ". " + i->first + " x" + to_string(i->second) + "\n");
    }

    return;
}

void user::check_package(int id, SOCKET SID)
{
    int cnt = 0;
    map<string, int>cnter;
    cnter.clear();
    set<int>& t = this->my_ob;
    set<int>::iterator it;
    for (it = t.begin(); it != t.end(); it++) {
        int tmp = *it;
        object* a = object::OB[tmp];
        cnter[a->get_name()]++;
    }
    string name_c;
    map<string, int>::iterator i;
    for (i = cnter.begin(); i != cnter.end(); i++)
    {
        cnt++;
        if (cnt == id) {
            name_c = i->first;
            break;
        }
    }
    for (it = t.begin(); it != t.end(); it++) {
        int temp = *it;
        object* a = object::OB[id];
        if (a->get_name() == name_c) {
            a->show(SID);
            break;
        }
    }
    return;
}

void user::check_domed(int id, SOCKET SID)
{
    int cnt = 0;
    for (auto t : poke) {
        cnt++;
        if (cnt == id) {
            pokemon* temp = pokemon::POKE[t];
            out(SID,string("����: ") + temp->get_name() + "\n����: ");
            temp->show_dis(SID);
            out(SID, string("\n����:\n"));
            temp->show_skill(SID);
        }
    }
    out(SID, string("\n"));
}

int user::get_pos() {
    return pos;
}