#pragma once
#ifndef _POKEMON_HEAD_
#define _POKEMON_HEAD_

#include<map>
#include<set>
#include<vector>
#include<string>

#include"socketio.h"
#include"maps.h"
#include"object.h"
#include"user.h"
using namespace std;

#define max_level 20

class pokemon {
protected:

    int id;
    string name;
    string discribe;
    int HP;
    int MAXHP;
    int DEF;
    int MAXDEF;
    double ATKx;
    int EXP;
    int level;
    set<int> skill;
    int pos;
public:
    map<string, int>ability;
    static map<int, pokemon*> POKE;
    static int pokemon_cnt;
    static map<int, pokemon*> createPOKE();
    
    pokemon(string d, string n, int level,int p);
    ~pokemon();
    // get fun
    string get_name();
    int get_id();
    int get_level();
    // cout fun
    void show_skill(SOCKET SID);
    void show_dis(SOCKET SID);
    // modify fun
    void die(); // hp->0
    void cure(); // hp->maxhp
    void exp_up(int exp, SOCKET SID);
    void level_up(SOCKET SID);
    void insert_skill(int a);
    void delete_skill(int a);
    void init_fight();
    // show fun
    void show_status(SOCKET SID);

    // action fun
    

    /* friend class */
    friend class Skill;
    friend class damage;
    friend class buff;
    friend void fight(int u1, int pid2, SOCKET SID);
};

class Skill {
protected:
    static map<int, Skill*> SK;
    static int Skill_cnt;
    int id;
    string name;
    string describe;
public:
    static map<int, Skill*> createSK();
    string get_name();
    int get_id();
    Skill(string name, string describe);
    ~Skill();
    
    //action
    virtual string use_skill(int p1, int p2, SOCKET SID) = 0;
    virtual void begin_fight(); // call at the beginning of fight
    //friend
    friend class pokemon;
    friend void fight(int u1, int pid2, SOCKET SID);
};

class damage:public Skill {
protected:
    int ATK;
    double CRI;
    int used_time; // record the times of skill used. For some special skills like 'combo'
public:
    damage(string name, string describe, int ATK, double CRI = 0, int used_time = 0);
    ~damage();
    //action
    virtual string use_skill(int p1, int p2, SOCKET SID);
    virtual void begin_fight();
};

class buff :public Skill {
protected:
    double ATKx;
    int DEF;
    int used_time; // record the times of skill used. For some special skills like 'combo'
public:
    buff(string name, string describe,double ATKx = 1, int DEF = 0, int used_time = 0);
    ~buff();
    //action
    virtual string use_skill(int p1, int p2, SOCKET SID);
    virtual void begin_fight();
};

#endif