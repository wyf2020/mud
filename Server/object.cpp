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
    out(SID,  string("\n名称: ") + name + "\n");
    out(SID, string( "\n描述: ") + discribe +"\n");
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
    if (type == 1) a = "龙爪草";
    if (type == 2) a = "龙纹钥匙";
    if (type == 10) a = "龙首宝箱";
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
        out(SID,  string("\n...你回过神来，发现它早已被你搜刮一空，你使劲拍了拍额头让自己清醒...\n"));
        return;
    }
    map<int,int>::iterator it;
    int bj = -1;
    if (u->my_ob.count(2)) bj = 2;
    /*for (it = u->my_ob.begin(); it != u->my_ob.end(); it++) {
        
        if (object::OB[it0>]->get_name() == "龙纹钥匙") { bj = *it; break; }
    }*/
    if (bj==-1) {
        out(SID,  string("\n你最终没能打开宝箱，但隐隐感受到宝箱对某种神秘钥匙的呼唤...\n"));
        return;
    }
    u->delete_ob(bj,SID);
    int in = this->inside;
    object& t = *object::OB[in];
    out(SID, string( "\n龙首宝箱缓缓打开，古老的灰尘随着一丝古龙残存的气息冲天而起，尘埃落定之后，你得到了....\n"));
    t.show(SID);
    this->set_name("已被打开的龙首宝箱");
    u->get_ob(in);
    set_acted();
    return;
}


void bean::act(user* u, SOCKET SID)
{
    if (acted == true) {
        out(SID, string( "\n...你回过神来，发现它早已收入囊中，只是留下了诱人的虚影，你使劲拍了拍额头让自己清醒...\n"));
        return;
    }
    out(SID, string( "这仿佛是古龙的恩赐,你获得了.."));
    u->get_ob(id);
    this->show(SID);
    set_acted();
    return;
}

void bean::use(user* u, SOCKET SID)
{
    int i;
    out(SID, string( "你希望把这珍贵的龙爪草喂给...\n"));
    u->show_poke(SID);
    string s;
    s = get(SID);
    if (isnum(s)) i = atoi(s.c_str());
    else {
        out(SID, string("\n你似乎出现了对不存在的龙裔的幻觉..\n"));
    }
    string name;
    int cnt = 0,bj=0;
    for (auto t : u->poke) {
        cnt++;
        if (cnt == i) { pokemon::POKE[t]->exp_up(this->delta_ex,SID); bj = 1; name = pokemon::POKE[t]->get_name(); break; }
    }
    if (bj) out(SID, string( "你和你的 ") + name + "情谊更加坚定了..\n");
    else out(SID, string( "\n你似乎出现了对不存在的龙裔的幻觉..\n"));
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
            out(SID, + "1.继续 2.返回\n");
            c= get(SID);
            if (c == "2") { out(SID,  name + ": \"" + "急着赶路吗，那么再见吧..." + "\"\n"); return; }
        }
    }
    if (acted == true) return;
    if (this->have) {
        out(SID,  name + ": \"你的名字是" + u->get_name() + "吗...请收下这个..祝你好运，最后一脉驯龙者..." + "\"\n");
        u->get_ob(this->have);
        out(SID,  name + "赠与你..\n");
        object::OB[this->have]->show(SID);
    }
    set_acted();
    return;
}

void key::act(user* u, SOCKET SID)
{
    if (acted == true) {
        out(SID, string( "\n...你回过神来，发现它早已收入囊中，只是留下了诱人的虚影，你使劲拍了拍额头让自己清醒...\n"));
        return;
    }
    out(SID, string( "似乎是与龙的朝夕相处提升了你的运气,你获得了.."));
    u->get_ob(id);
    this->show(SID);
    set_acted();
}

void key::use(user* u, SOCKET SID)
{
    out(SID, string("\n你会用到它的，但不是现在。所以去找宝箱吧...\n"));
    return;
}

key::key(string n, string di):object(di,n){
    type = 2;
}

key::~key(){
}
