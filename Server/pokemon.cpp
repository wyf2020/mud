#include "pokemon.h"
#include<iostream>
#include<ctime>

using namespace std;

/* pokemon class */

int pokemon::pokemon_cnt = 0;
map<int, pokemon*>pokemon::POKE = pokemon::createPOKE();

map<int, pokemon*> pokemon::createPOKE() {
    map<int, pokemon*>tmp;
    return tmp;
}

pokemon::pokemon(string name, string discribe, int level,int p) :name(name), discribe(discribe),level(level),pos(p) {
    pokemon::pokemon_cnt++;
    id = pokemon::pokemon_cnt;
    pokemon::POKE[pokemon::pokemon_cnt] = this;
    HP = MAXHP = 50;
    DEF = MAXDEF = 10;
    ATKx = 1.0;
    EXP = 0;
    ability.clear();
    skill.clear();
}

pokemon::~pokemon() {}

string pokemon::get_name() {
    return name;
}

int pokemon::get_id() {
    return id;
}

void pokemon::die() {
    HP = 0;
}

void pokemon::cure() {
    HP = MAXHP;
}

void pokemon::exp_up(int exp, SOCKET SID) {
    int exp_needed[max_level] = { 10, 20, 30, 50, 100, 150, 200, 300, 500, 1000 };
    EXP += exp;
    out(SID, name + "获得了" + to_string(exp) + "点经验值");
    if (exp_needed[level - 1] <= EXP) {
        EXP -= exp_needed[level - 1];
        level_up(SID);
        out(SID, name + ",升级到了LV." + to_string(level) + "!" + "\n");
    }
    else {
        out(SID, string(", 距升级还有") + to_string(exp_needed[level - 1] - EXP) + "点经验" + "\n");
    }
}

int pokemon::get_level() {
    return level;
}

void pokemon::show_skill(SOCKET SID) {
    int cnt = 0;
    for (auto t : skill) {
        cnt++;
        out(SID, to_string(cnt) + "." + Skill::SK[t]->get_name() + " ");
    }
    out(SID, string("\n"));
}

void pokemon::show_dis(SOCKET SID)
{
    out(SID, discribe + "\n");
}

void pokemon::level_up(SOCKET SID) {
    level++;
    MAXHP *= 1.1;
    DEF *= 1.1;
}

void pokemon::insert_skill(int a) {
    skill.insert(a);
}
void pokemon::delete_skill(int a) {
    skill.erase(a);
}

void pokemon::init_fight() {
    HP = MAXHP;
    DEF = MAXDEF;
    ATKx = 1.0;
}

void pokemon::show_status(SOCKET SID) {
    out(SID, "LV." + to_string(level) + " " + name + " HP:" + to_string(HP) + "/" + to_string(MAXHP));
}


/* skill class */

int Skill::Skill_cnt = 0;
map<int, Skill*>Skill::SK = Skill::createSK();

map<int, Skill*> Skill::createSK() {
    map<int, Skill*>tmp;
    return tmp;
}

Skill::Skill(string name, string describe) :name(name), describe(describe) {
    Skill::Skill_cnt++;
    id = Skill::Skill_cnt;
    Skill::SK[Skill::Skill_cnt] = this;
}

Skill::~Skill() {}

string Skill::get_name() {
    return name;
}

int Skill::get_id() {
    return id;
}

void Skill::begin_fight() {} // do nothing

// damage class

damage::damage(string name, string describe, int ATK, double CRI, int used_time)
    :Skill(name, describe), ATK(ATK), CRI(CRI), used_time(used_time) {}

damage::~damage() {}

string damage::use_skill(int p1, int p2, SOCKET SID) {
    string CRIm, resm;
    int ATK_res = ATK;
    if ((double)rand() / RAND_MAX < CRI) {
        ATK_res *= 2;
        CRIm = "暴击! ";
    }
    ATK_res = (int)ceil(ATK_res * exp(-0.01 * pokemon::POKE[p2]->DEF));
    pokemon::POKE[p2]->HP -= ATK_res;
    resm = "造成了" + to_string(ATK_res) + "点伤害";
    if (pokemon::POKE[p2]->HP < 0) pokemon::POKE[p2]->HP = 0;
    ++used_time;
    out(SID, CRIm);
    return resm;
}

void damage::begin_fight() {
    used_time = 0;
}

buff::buff(string name, string describe, double ATKx, int DEF, int used_time) 
    :Skill(name, describe), ATKx(ATKx), DEF(DEF), used_time(used_time) {}

buff::~buff(){}

bool notdebuff(int id) {
    if (id == 2) return true; // 正面buff技能列表
    else return false;
}

string buff::use_skill(int p1, int p2, SOCKET SID) {
    if (notdebuff(this->id)) {
        int temp = p1;
        p1 = p2;
        p2 = temp;
    }
    string m;
    pokemon::POKE[p2]->ATKx *= ATKx;
    pokemon::POKE[p2]->DEF += DEF;
    if (ATKx != 1) m += "伤害提升了 ";
    if (DEF != 1) m += "防御力提升了 ";
    ++used_time;
    return m;
}

void buff::begin_fight() {
    used_time = 0;
}
