#include "object.h"
#include<iostream>
#include<set>
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

void object::show() {
    cout << "\n����: " << name << endl;
    cout << "\n����: " << discribe << endl;
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

void object::use(user* u) {

}

void object::act(user* u)
{

}

box::box(int in, string n, string di ):inside(in),object(di,n) {
    type = 1;
}

box::~box() {
}

void box::act(user* u) {
    if (acted == true) {
        cout << "\n...��ع����������������ѱ����ѹ�һ�գ���ʹ�������Ķ�ͷ���Լ�����...\n";
        return;
    }
    set<int>::iterator it;
    int bj = -1;
    for (it = u->my_ob.begin(); it != u->my_ob.end(); it++) {
        
        if (object::OB[*it]->get_name() == "����Կ��") { bj = *it; break; }
    }
    if (bj==-1) {
        cout << "\n������û�ܴ򿪱��䣬���������ܵ������ĳ������Կ�׵ĺ���...\n";
        return;
    }
    u->delete_ob(bj);
    int in = this->inside;
    object& t = *object::OB[in];
    cout << "\n���ױ��仺���򿪣����ϵĻҳ�����һ˿�����д����Ϣ������𣬳����䶨֮����õ���....\n";
    t.show();
    this->set_name("�ѱ��򿪵����ױ���");
    u->get_ob(in);
    set_acted();
    return;
}


void bean::act(user* u)
{
    if (acted == true) {
        cout << "\n...��ع������������������������У�ֻ�����������˵���Ӱ����ʹ�������Ķ�ͷ���Լ�����...\n";
        return;
    }
    cout << "��·��ǹ����Ķ���,������..";
    u->get_ob(id);
    this->show();
    set_acted();
    return;
}

void bean::use(user* u)
{
    int i;
    cout << "��ϣ������������צ��ι��...\n";
    u->show_poke();
    cin >> i;
    string name;
    int cnt = 0,bj=0;
    for (auto t : u->poke) {
        cnt++;
        if (cnt == i) { pokemon::POKE[t]->exp_up(this->delta_ex); bj = 1; name = pokemon::POKE[t]->get_name(); break; }
    }
    if (bj) cout << "������ " << name << "������Ӽᶨ��..\n";
    else cout << "\n���ƺ������˶Բ����ڵ�����Ļþ�..\n";
    return;
}

bean::bean(int ex, string n, string di) :delta_ex(ex), object(di, n) {
    type = 2;
}

bean::~bean() {}

npc::npc(vector<string>& s, int ha, string na, string di) :have(ha), sentences(s), object(di, na) {
    type = 1;
}

npc::~npc() {}

void npc::act(user* u) {
    int c;
    vector<string>::iterator it;
    if (acted == true) {
        cout << name << ": \"" << sentences[cnt_sen-1] << "\"\n";
        return;
    }
    else {
        for (it = sentences.begin() + this->cnt_sen; it != sentences.end(); it++) {
            this->cnt_sen++;
            cout << name << ": \"" << *it << "\"\n";
            cout << "1.���� 2.����\n";
            cin >> c;
            if (c == 2) { cout << name << ": \"" << "���Ÿ�·����ô�ټ���..." << "\"\n"; return; }
        }
    }
    if (acted == true) return;
    if (this->have) {
        cout << name << ": \"���������" << u->get_name() << "��...���������..ף����ˣ����һ��ѱ����..." << "\"\n";
        u->get_ob(this->have);
        cout << name << "������..\n";
        object::OB[this->have]->show();
    }
    set_acted();
    return;
}

void key::act(user* u)
{
    if (acted == true) {
        cout << "\n...��ع������������������������У�ֻ�����������˵���Ӱ����ʹ�������Ķ�ͷ���Լ�����...\n";
        return;
    }
    cout << "�ƺ��������ĳ�Ϧ�ദ�������������,������..";
    u->get_ob(id);
    this->show();
    set_acted();
}

key::key(string n, string di):object(di,n){
    type = 2;
}

key::~key(){
}
