#pragma once
#ifndef _OBJECT_HEAD_
#define _OBJECT_HEAD_

#include<map>
#include<vector>
#include<string>
#include<set>

#include"maps.h"
#include"pokemon.h"
#include"user.h"
using namespace std;

extern class user;

class object {
protected:
    int id;
    string discribe;
    string name;
    int type;
    int pos=-1;
    bool acted = false;
public:
    friend class maps;
    friend class user;
    static map<int, object*>OB;
    static int object_cnt;
    static map<int, object*>createOB();
    string get_name();
    int get_id();
    int get_type();
    int get_pos();
    void set_name(string n);
    void set_acted();
    virtual void act(user *u);
    void show();
    void setpos(int p);
    virtual void use(user *u);
    object(string d, string n);
    ~object();
};
    
class box :public object {
private:
    int inside;
public:
    box(int in,string n = "龙首宝箱", string di = "\n这是一个被精雕细琢的神秘材质的箱子，似乎藏着宝物，需要用钥匙打开...\n");
    ~box();
    void act(user *u);
};

class bean :public object {
private:
    int delta_ex;
public:
    void act(user * u);
    void use(user * u);
    bean(int ex, string n = "龙爪草", string di = "\n这个植物在神秘力量的作用下长成了龙爪的形状，给驯化龙裔服用后可以获得古老的力量...\n");
    ~bean();
};


class key:public object {
public:
    void act(user * u);
    key(string n = "龙纹钥匙", string di = "\n这是一个散发着光辉的钥匙，似乎有魔法的力量来打开任何箱子...\n");
    ~key();
};

class npc :public object {
private:
    vector<string>sentences;
    int have;
    int cnt_sen=0;
public:
    npc(vector<string>& s,int ha=0, string na="路人", string di="\n这是一个行色匆匆的赶路人，破旧的斗篷掩盖住了他的脸...\n");
    ~npc();
    void act(user *u);
};

#endif
