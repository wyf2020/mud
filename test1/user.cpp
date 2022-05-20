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

bool user::move(char a){
    maps* p = maps::MP[pos];
    int tar = 0;
    if (a == 'e') {
        if (p->e == -1) {
            cout << "\n--东边似乎已难有收获..--\n";
            return false;
        } else tar = p->e;
    }else if (a == 'w') {
        if (p->w == -1) {
            cout << "\n--通往西边的路已是尽头..--\n";
            return false;
        } else tar = p->w;
    }else if (a == 's') {
        if (p->s == -1) {
            cout << "\n--南边只是一片虚无，没有探索价值...--\n";
            return false;
        } else tar = p->s;
    }else if (a == 'n') {
        if (p->n == -1) {
            cout << "\n--北侧绝壁入天，难以越过..--\n";
            return false;
        } else tar = p->n;
    }else {
        cout << "\n黑龙米狄尔的蛊惑竟让你失去了辨别方向的理智...\n" << endl;
    }
    if (!Check(this,pos,a)) return false;
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

void user::show_poke() {
    int cnt = 0;
    for (auto t : poke) {
        cnt++;
        cout << cnt << "." << pokemon::POKE[t]->get_name() << " ";
    }
    cout << endl;
}

void user::show_pack()
{
    int cnt = 0;
    map<string, int>cnter;
    cnter.clear();
    set<int>& t = this->my_ob;
    set<int>::iterator it;
    cout << "你检查了一下背包，里面有:\n";
    for (it = t.begin(); it != t.end(); it++) {
        int id = *it;
        object* a = object::OB[id];
        cnter[a->get_name()]++;
    }
    map<string, int>::iterator i;
    for (i = cnter.begin(); i != cnter.end(); i++)
    {
        cnt++;
        cout << "  " << cnt << ". " << i->first << " x" << i->second << endl;
    }

    return;
}

void user::check_package(int id)
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
            a->show();
            break;
        }
    }
    return;
}

void user::check_domed(int id)
{
    int cnt = 0;
    for (auto t : poke) {
        cnt++;
        if (cnt == id) {
            pokemon* temp = pokemon::POKE[t];
            cout<<"名称: " << temp->get_name() << "\n描述: ";
            temp->show_dis();
            cout << "\n技能:\n";
            temp->show_skill();
        }
    }
    cout << endl;
}

int user::get_pos() {
    return pos;
}