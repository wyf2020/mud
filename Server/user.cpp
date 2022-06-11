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

void user::delete_ob(int id,SOCKET SID)
{
    int type = object::OB[id]->get_type();
    string name = object::OB[id]->get_name();
    if (this->my_ob.count(type)) {
        out(SID,name+string("�Ѿ�û����,") + string("ȥ���µĴ�½Ѱ�Ұ�...\n"));
    }
    else my_ob[type]--;
    return;
}

void user::get_ob(int id)
{
    int type = object::OB[id]->get_type();
    if (this->my_ob.count(type)) my_ob.insert(make_pair(type, 1));
    else my_ob[type]++;
    //(this->my_ob).insert(id);
}

void user::insert_poke(int a) {
    poke.insert(a);
}

void user::delete_poke(int a) {
    poke.erase(a);
}

void user::use(int id, SOCKET SID)
{
    string name = object::typetoname(id);
    if (!my_ob.count(id)) {
        out(SID, string("\n�㻹δӵ��" + name + ",ȥ̽����Զ�Ĵ�½��..\n"));
    }
    object* a = object::OB[id];
    //out(SID, string("?????????\n "));
    a->use(this,SID);
}

void user::show_poke(SOCKET SID) {
    int cnt = 0;
    for (auto t : poke) {
        cnt++;
        out(SID, string(" ")+to_string(cnt) + "." + pokemon::POKE[t]->get_name() + "  lv." + to_string(pokemon::POKE[t]->get_level()));
    }
    out(SID, string("\n"));
}

void user::show_pack(SOCKET SID)
{
    out(SID, string("������һ�±�����������:\n"));
    for (int i = 1; i <= 2; i++) {
        if(!my_ob.count(i)) out(SID, string("  ")+ to_string(i)+ ". " + object::typetoname(i) + " x" + to_string(0) + "\n");
        else out(SID, string("  ")+ to_string(i)  + ". " + object::typetoname(i) + " x" + to_string(my_ob[i]) + "\n");
    }
    return;
}

void user::check_package(int id, SOCKET SID)
{
    string name = object::typetoname(id);
    if (!this->my_ob.count(id))
    {
        out(SID,string("\n�㻹δӵ��"+name+",ȥ̽����Զ�Ĵ�½��..\n"));
        return;
    }
    if (id == 1) {
        bean *a=new bean(0);
        a->show(SID);
        delete a;
    }
    else {
        key* a = new key();
        a->show(SID);
        delete a;
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