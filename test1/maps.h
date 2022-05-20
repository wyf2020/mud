#pragma once
#ifndef _MAPS_HEAD_
#define _MAPS_HEAD_

#include<map>
#include<vector>
#include<string>

#include"object.h"
#include"pokemon.h"
#include"user.h"
using namespace std;

class maps {
private:
    int id;
    int e, w, s, n;
    string discribe;
    string name;
    vector<int>ob;
    vector<int>poke;
    static string find_link_map(int id);
        
public:
    static int map_cnt;
    static map<int, maps*>MP;
    void insert_ob(int id);
    void insert_po(int id);
    void initial();
    static map<int,maps*> createMP();
    void delete_ob(int id);
    void delete_po(int id);
    void show();
    void show_link();
    void show_ob_po();
    friend void link_map(int a, int b, char p);
    friend bool Check(int pos, char a);

    friend class user;
    friend void act_with(user* u);
    friend void fight_start(user* u);
    friend void check_ob(user *u);
    maps(string na, string dis, vector<int>& ob, vector<int>& po);
    ~maps();
};
void link_map(int a, int b, char p);
bool Check(user *u,int pos, char a);
#endif

