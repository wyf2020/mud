#pragma once
#ifndef _USER_HEAD_
#define _USER_HEAD_

#include<map>
#include<vector>
#include<set>
#include<string>

#include"socketio.h"
#include"maps.h"
#include"object.h"
#include"pokemon.h"
using namespace std;

class user {
protected:
    int id;
    string username;
    string password;
    map<int,int>my_ob;
    int defeat_poke;
    bool is_online = false;
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
    bool move(char a, SOCKET SID);
    void delete_ob(int id,SOCKET SID);
    void get_ob(int id);
    void insert_poke(int a);
    void delete_poke(int a);
    void use(int id, SOCKET SID);
    void online();
    void offline();
    //show fun
    bool Is_Online();
    void show_poke(SOCKET SID);
    void show_pack(SOCKET SID);
    void check_package(int id, SOCKET SID);
    void check_domed(int id, SOCKET SID);
    //
    user(string d, string n);
    ~user();
    friend bool Check(user* u, int pos, char a, SOCKET SID);
    friend class maps;
    friend class object;
    friend class box;
};


#endif