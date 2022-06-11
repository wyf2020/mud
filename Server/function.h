#ifndef _FUNCTION_HEAD_
#define _FUNCTION_HEAD_


#include"socketio.h"
#include"maps.h"
#include"object.h"
#include"user.h"
#include"pokemon.h"
using namespace std;

bool isnum(string s);
void Initial_map_1();


void Initial_map_2();

void initial_user_1();

void initial_user();

void initial_skill_1();
void initial_skill_2();
void initial_skill();

void initial_poke_1(int pos, int uid);

void initial_poke();

void Initial_key();
void Initial_box();

void Initial_bean();
void Initial_npc();

void Initial();

int fight_begin(int u1, SOCKET SID);
int find_nth_skill(pokemon* p, int n);
void fight(int u1, int pid2, SOCKET SID);

//void operate(user* u, string op, string op2, SOCKET SID);

void show_help(SOCKET SID);

void see(user* u, SOCKET SID);

void act_with(user* u, SOCKET SID);

void check_ob(user* u, SOCKET SID);
bool move_position(user* u, SOCKET SID);

void fight_start(user* u, SOCKET SID);

void view_me(user* u, SOCKET SID);


bool operate(user* u, string op, SOCKET SID);
void Welcome(SOCKET SID);
bool name_in(int& id, SOCKET SID);
int pass_in(int id, SOCKET SID);
int Begin(SOCKET SID);

#endif