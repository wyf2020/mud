#include"maps.h"
#include<iostream>

int maps::map_cnt = 0;
map<int, maps*>maps::MP = maps::createMP();

maps::maps(string na, string dis,vector<int>&ob,vector<int>&po):discribe(dis), name(na),poke(po),ob(ob) {
    n = s = w = e = -1;
    maps::map_cnt++;
    id = maps::map_cnt;
    maps::MP[maps::map_cnt] = this;
}

maps::~maps() {
}

map<int, maps*> maps::createMP() {
    map<int, maps*>temp;
    return temp;
}

void maps::initial() {
    maps::map_cnt++;
    int ct = 1;
    maps::MP[ct];
}

void maps::show(SOCKET SID) {
    out(SID, string("\n  ---") + this->name + "---\n");
    out(SID, string("\n") + this->discribe + "\n");
    return;
}

string maps::find_link_map(int id) {
    string tmp = "";
    if(maps::MP.find(id)==maps::MP.end()) tmp="无路可走";
    else tmp=(maps::MP[id])->name;
    return tmp;
}

void maps::show_link(SOCKET SID) {
    out(SID, string("\n"));
    string E, W, N, S;
    E = maps::find_link_map(this->e);
    W = maps::find_link_map(this->w);
    N = maps::find_link_map(this->n);
    S = maps::find_link_map(this->s);
    out(SID, string(" 东: ") + E + "\n");
    out(SID, string(" 南: ") + S + "\n");
    out(SID, string(" 西: ") + W + "\n");
    out(SID, string(" 北: ") + N + "\n");
    return;
}

void maps::insert_ob(int id) {
    (this->ob).push_back(id);
}

void maps::insert_po(int id) {
    (this->poke).push_back(id);
}

void maps::delete_ob(int id) {
    vector<int>& t = this->ob;
   t.erase(remove(t.begin(), t.end(), id),t.end());
    return;
}

void maps::delete_po(int id) {
    vector<int>& t = this->poke;
    t.erase(remove(t.begin(), t.end(), id), t.end());
    return;
}

void maps::show_ob_po(user *u,SOCKET SID) {
    int cnt_ob = 0;
    out(SID, string("\n你四下查看，发现了:\n( act [number] 与发现的物品或人类互动/fight [number] 与目标生物战斗) \n"));
    out(SID, string(" 同为终末驯龙者的:\n"));

    for (auto it = user::umap.begin(); it != user::umap.end(); it++) {
        user* p = it->second;
        if (p->Is_Online()&&p->get_pos() == u->get_pos() && p->get_id() != u->get_id()) {
            cnt_ob++;
            out(SID, string("  ") + to_string(cnt_ob) + ". ");
            out(SID, p->get_name());
            out(SID, string("\n"));
        }
    }
    out(SID, string("\n"));
    cnt_ob = 0;
    out(SID, string(" 物品和神秘人类:\n"));
    for (auto it = ob.begin(); it != ob.end(); it++) {
        cnt_ob++;
        out(SID,string("  ") + to_string(cnt_ob) + ". ");
        out(SID,object::OB[*it]->get_name());
        if (object::OB[*it]->acted == true) out(SID, string("(已取得)"));
        out(SID, string("\n"));
    }
    out(SID, " 其他生物:\n"); 
    cnt_ob = 0;
    for (auto it = poke.begin(); it != poke.end(); it++) {
        cnt_ob++;
        out(SID,string("  ") + to_string(cnt_ob) + ". ");
        out(SID,pokemon::POKE[*it]->get_name());
        out(SID, string("\n"));
    }
    return;
}

void link_map(int a, int b, char p) {
    if (p == 'e') maps::MP[a]->e = b,maps::MP[b]->w=a;
    if (p == 'n') maps::MP[a]->n = b,maps::MP[b]->s=a;
    if (p == 'w') maps::MP[a]->w = b,maps::MP[b]->e=a;
    if (p == 's') maps::MP[a]->s = b,maps::MP[b]->n=a;
    return;
}

bool Check(user * u,int pos, char a, SOCKET SID)
{
    if ((pos == 1 && a == 'e') || (pos == 2 && a == 'w')) {
        int bj = 0;
        for (auto it = u->poke.begin(); it != u->poke.end(); it++) {
            if (pokemon::POKE[*it]->ability["FLY"] == 1) { bj = 1; return true; }
        }
        out(SID, "\n可怜的最后一脉驯龙者，你并不具备到达那边的条件..\n");
        return false;
    }
    return true;
}