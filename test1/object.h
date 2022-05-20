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
    box(int in,string n = "���ױ���", string di = "\n����һ��������ϸ�������ز��ʵ����ӣ��ƺ����ű����Ҫ��Կ�״�...\n");
    ~box();
    void act(user *u);
};

class bean :public object {
private:
    int delta_ex;
public:
    void act(user * u);
    void use(user * u);
    bean(int ex, string n = "��צ��", string di = "\n���ֲ�������������������³�������צ����״����ѱ��������ú���Ի�ù��ϵ�����...\n");
    ~bean();
};


class key:public object {
public:
    void act(user * u);
    key(string n = "����Կ��", string di = "\n����һ��ɢ���Ź�Ե�Կ�ף��ƺ���ħ�������������κ�����...\n");
    ~key();
};

class npc :public object {
private:
    vector<string>sentences;
    int have;
    int cnt_sen=0;
public:
    npc(vector<string>& s,int ha=0, string na="·��", string di="\n����һ����ɫ�Ҵҵĸ�·�ˣ��ƾɵĶ����ڸ�ס��������...\n");
    ~npc();
    void act(user *u);
};

#endif
