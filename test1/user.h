#pragma once
#ifndef _USER_HEAD_
#define _USER_HEAD_

#include<map>
#include<vector>
#include<set>
#include<string>

#include"maps.h"
#include"object.h"
#include"pokemon.h"
using namespace std;

class user {
protected:
    int id;
    string username;
    string password;
    set<int>my_ob;
    int defeat_poke;
public:
    int pos;
    set<int> poke;
    static map<int, user*> umap;
    static int user_cnt;
    static map<int, user*> createumap();
    bool catch_poke(int id);
    string get_name();
//function
    //get fun
    int get_id();
    string get_password();
    int get_pos();
    //modify fun
    bool move(char a);
    void delete_ob(int id);
    void get_ob(int id);
    void insert_poke(int a);
    void delete_poke(int a);
    //show fun
    void show_poke();
    void show_pack();
    void check_package(int id);
    void check_domed(int id);
    //
    user(string d, string n);
    ~user();
    friend bool Check(user* u, int pos, char a);
    friend class maps;
    friend class object;
    friend class box;
};


#endif