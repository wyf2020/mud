#include <iostream>
#include <ctime>

#include"function.h"

using namespace std;

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

int exp_needed[max_level] = { 10, 20, 30, 50, 100, 150, 200, 300, 500, 1000 };

bool isnum(string s) {
    int l = s.length();
    for (int i = 0; i < l; i++) {
        if (s[i] < '0' || s[i]>'9') return false;
    }
    return true;
}

void Initial_map_1() {
    string name = "化圣雪原";
    string dis = "这是一片苍茫的雪原，漫天的风雪几乎掩盖了旅者的视线，在这风雪中隐隐夹杂着阵阵类似龙吟的叫啸，传说这里曾是四大古龙之一冰霜巨龙的栖息地....";
    vector<int>* ob = new vector<int>;
    vector<int>* poke = new vector<int>;
    maps* p = new maps(name, dis, *ob, *poke);
    return;
}


void Initial_map_2() {
    string name = "天空岛";
    string d = "这是一座浮空的岛屿, 你需要具有飞行能力的龙裔才能前往";
    vector<int>* ob = new vector<int>;
    vector<int>* po = new vector<int>;
    new maps(name, d, *ob, *po);
    return;
}


void initial_user_1() {
    string name = "wyf";
    string pass = "123456";
    user* p = new user(name, pass);
    p->pos = 1;
}

void initial_user_2() {
    string name = "wjk";
    string pass = "12345";
    user* p = new user(name, pass);
    p->pos = 1;
}

void initial_user() {
    initial_user_1();
    initial_user_2();
}

void initial_skill_1() {
    new damage("寒冰箭", "发射一支冰霜箭矢", 10, 0.2, 0);
}

void initial_skill_2() {
    new buff("霜铠", "凝结一层护盾, 提升本局战斗的防御力", 1, 10, 0);
}

void initial_skill() {
    initial_skill_1();
    initial_skill_2();
}

void initial_poke_1(int pos,int uid) {
    string name = "冰原地龙幼崽";
    string d = "这是一只生长在冰雪地区的龙裔，由于身体流淌的原始古龙的血脉过于稀薄，已经失去了飞行能力";
    pokemon* p = new pokemon(name, d, 1, pos);
    p->insert_skill(1);
    p->insert_skill(2);
    if (pos) {
        maps::MP[pos]->insert_po(p->get_id());
    }
    else {
        user* u = user::umap[uid];
        u->insert_poke(p->get_id());
    }
    p->ability["FLY"] = 0;
    return;
}

void initial_poke() {
    initial_skill();
    initial_poke_1(1,0);
    initial_poke_1(0,1);
    initial_poke_1(0,2);
}

void Initial_key() {
    key* p = new key();
    p->setpos(1);
    maps::MP[1]->insert_ob(p->get_id());
}
void Initial_box() {
    bean* pb = new bean(10);
    pb->setpos(-1);
    box* p = new box(3);
    maps::MP[1]->insert_ob(p->get_id());
}

void Initial_bean() {
    bean* p = new bean(10);
    p->setpos(1);
    maps::MP[1]->insert_ob(p->get_id());
}

void Initial_npc() {
    string s1 = "远方的旅客啊...真是稀奇..", s2 = "你是最后一脉驯龙者吧...", s3 = "我吗？我只是在这冰原漫无目的地游荡的可怜游魂罢了..";
    vector<string>s;
    s.push_back(s1); s.push_back(s2); s.push_back(s3);
    bean* p = new bean(10);
    p->setpos(-1);
    string na = "残缺的老妪游魂", di = "这是一个可怜的游魂，已经快消逝在这冰原中了";
    npc* p2 = new npc(s, 5, na, di);
    p2->setpos(1);
    maps::MP[1]->insert_ob(p2->get_id());
}

void Initial() {
    initial_user();
    Initial_map_1();
    Initial_map_2();
    link_map(1, 2, 'e');
    initial_poke();
    Initial_key();
    Initial_bean();
    Initial_box();
    Initial_npc();
    srand((unsigned int)time(NULL));
}

int fight_begin(int u1, SOCKET SID) {
    user* p = user::umap[u1];
    int tarp = 0;
    while (1) {
        out(SID,  string("请选择出战的训化龙裔:\n"));
        int cnt = (int)p->poke.size();
        p->show_poke(SID);
        string tid = "-1";
        tid = get(SID);
        if (tid == "-1" || !isnum(tid) || atoi(tid.c_str()) > cnt) { out(SID, string("请输入") + "1" + "~" + to_string(cnt) + "之间的整数\n"); }
        else {
            cnt = 0;
            for (auto t : p->poke) {
                cnt++;
                if (atoi(tid.c_str()) == cnt) {
                    return t;
                }
            }
        }
    }
}

void fight(int u1, int pid2, SOCKET SID) {
    pokemon* p1, * p2 = pokemon::POKE[pid2];
    out(SID,  p2->get_name()+ " 出现了!\n" );
    int pid1 = fight_begin(u1, SID);
    p1 = pokemon::POKE[pid1];
    p1->init_fight();
    p2->init_fight();
    int round = 0;
    while (1) {
        round++;
        out(SID, string( "-------------------第" ) +  to_string(round) + "回合---------------------\n") ;
        p1->show_status(SID);
        out(SID, string( "      VS      "));
        p2->show_status(SID);
        out(SID, string("\n"));
        int sk_id = 0;
        while (1) {
            out(SID, string( "请选择技能:\n" ));
            int total = (int)p1->skill.size();
            p1->show_skill(SID);
            string tid = "-1";
            tid = get(SID);
            if (tid == "-1" || !isnum(tid) || atoi(tid.c_str()) > total) { 
                out(SID, string("请输入") + "1" + "~" + to_string(total) + "之间的整数\n"); 
            }
            else {
                total = 0;
                for (auto t : p1->skill) {
                    total++;
                    if (atoi(tid.c_str()) == total) {
                        sk_id = t;
                        break;
                    }
                }
                break;
            }
        }
        out(SID, string( "你") + Skill::SK[sk_id]->use_skill(pid1, pid2, SID) + "             ");
        if (p2->HP == 0) {
            out(SID, string( "你成功击败了")+ p2->get_name());
            p1->exp_up((int)ceil(exp_needed[p2->level - 1] * 0.5), SID);
            break;
        }
        else {
            int total2 = (int)p2->skill.size();
            int tid2 = (int)ceil((double)rand() / RAND_MAX * total2);
            total2 = 0;
            for (auto t : p2->skill) {
                total2++;
                if (tid2 == total2) {
                    out(SID, string( "对方") + Skill::SK[t]->use_skill(pid2, pid1, SID) + "\n");
                }
            }
            if (p1->HP == 0) {
                out(SID, string( "你被") + p2->get_name() + "击败了\n");
                break;
            }
        }
    }
    p1->init_fight();
    p2->init_fight();
}

void show_help(SOCKET SID) {
    out(SID, string("1. move [e/w/s/n] 向东/西/南/北方向移动\n"));
    out(SID, string("2. see [road/stuff]查看周遭\n"));
    out(SID, string("3. act [number] 与发现的物品或人类互动\n"));
    out(SID, string("4. help 查看帮助手册\n"));
    out(SID, string("5. check [other/dragon/package/domed] [number] 观察场景物品或人类/野生生物/背包内物品/已驯服的龙裔\n"));
    out(SID, string("6. fight [number] 与目标生物战斗\n"));
    out(SID, string("7. view [package/domed] 查看背包/被驯服的龙裔\n"));
    out(SID, string("8. use [number] 使用背包内物品\n"));
    return;
}

void see(user* u, SOCKET SID) {
    string op2;
    op2 = get(SID);
    if (op2 == "road") maps::MP[u->pos]->show_link(SID);
    else  if (op2 == "stuff") maps::MP[u->pos]->show_ob_po(u,SID);
    else  out(SID, string( "\n--指令无法识别，黑龙米狄尔遗留的瘴气似乎侵蚀了你的理智..--\n"));
    return;
}

void act_with(user* u, SOCKET SID) {
    string id;
    id = get(SID);
    if (!isnum(id)) {
        out(SID, string( "\n--指令无法识别，黑龙米狄尔遗留的瘴气似乎侵蚀了你的理智..--\n"));
        return;
    }
    int cnter = 0, bj = 0;
    maps& t = *maps::MP[u->pos];
    for (auto it = t.ob.begin(); it != t.ob.end(); it++) {
        cnter++;
        if (cnter == atoi(id.c_str())) {
            object::OB[*it]->act(u, SID);
            bj = 1;
            break;
        }
    }
    if (!bj) out(SID, string( "\n你似乎出现了对不存在物的幻觉..\n"));
    return;
}

void check_ob(user* u, SOCKET SID) {
    string type;
    string id;
    type = get(SID);
    id = get(SID);
    if (!isnum(id)) {
        out(SID, string( "\n--指令无法识别，黑龙米狄尔遗留的瘴气似乎侵蚀了你的理智..--\n"));
        return;
    }
    if (type == "other") {
        int cnter = 0, bj = 0;
        maps& t = *maps::MP[u->pos];
        for (auto it = t.ob.begin(); it != t.ob.end(); it++) {
            cnter++;
            if (cnter == atoi(id.c_str())) {
                object::OB[*it]->show(SID);
                bj = 1;
                break;
            }
        }
        if (!bj) out(SID, string( "\n你似乎出现了对不存在物的幻觉..\n"));
    }
    else if (type == "dragon") {
        int cnter = 0, bj = 0;
        maps& t = *maps::MP[u->pos];
        for (auto it = t.poke.begin(); it != t.poke.end(); it++) {
            cnter++;
            if (cnter == atoi(id.c_str())) {
                pokemon::POKE[*it]->show_dis(SID);
                bj = 1;
                break;
            }
        }
        if (!bj) out(SID, string( "\n你似乎出现了对不存在物的幻觉..\n"));
    }
    else if (type == "package") {
        u->check_package(atoi(id.c_str()), SID);

    }
    else if (type == "domed") {
        u->check_domed(atoi(id.c_str()), SID);
    }
    return;
}

bool move_position(user* u, SOCKET SID) {
    string a = get(SID);
    if (u->move(a[0], SID)) return true;
    return false;
}

void fight_start(user* u, SOCKET SID) {
    string id;
    id = get(SID);
    if (!isnum(id)) {
        out(SID, string( "\n--指令无法识别，黑龙米狄尔遗留的瘴气似乎侵蚀了你的理智..--\n"));
        return;
    }
    int cnter = 0, bj = 0;
    maps& t = *maps::MP[u->pos];
    for (auto it = t.poke.begin(); it != t.poke.end(); it++) {
        cnter++;
        if (cnter == atoi(id.c_str())) {
            int i = pokemon::POKE[*it]->get_id();
            fight(u->get_id(), i, SID);
            bj = 1;
            break;
        }
    }
    if (!bj) out(SID, string( "\n你似乎出现了对不存在的龙裔的幻觉..\n"));
    return;
}

void view_me(user* u, SOCKET SID) {
    string type;
    type = get(SID);
    if (type == "package") {
        u->show_pack(SID);
        return;
    }
    else if (type == "domed") {
        out(SID, string("你吹响龙骨哨，唤来了:\n"));
        u->show_poke(SID);
        return;
    }
    out(SID, string( "\n--指令无法识别，黑龙米狄尔遗留的瘴气似乎侵蚀了你的理智..--\n"));
    return;
}

void user_use(user* u, SOCKET SID) {
    string id;
    id = get(SID);
    if (!isnum(id)) {
        out(SID, string("\n--指令无法识别，黑龙米狄尔遗留的瘴气似乎侵蚀了你的理智..--\n"));
        return;
    }
    u->use(atoi(id.c_str()), SID);
}

bool operate(user* u, string op, SOCKET SID) {
    if (op == "help") { show_help(SID); return false; }
    if (op == "see") { see(u, SID); return false; }
    if (op == "act") { act_with(u, SID); return false; }
    if (op == "fight") { fight_start(u,SID); return false; }
    if (op == "check") { check_ob(u,SID); return false; }
    if (op == "move") { if (move_position(u, SID)) return true; else return false; }
    if (op == "view") { view_me(u,SID); return false; }
    if (op == "use") { user_use(u,SID); return false; }
    out(SID, string( "\n--指令无法识别，黑龙米狄尔遗留的瘴气似乎侵蚀了你的理智..--\n"));

    return false;
}

void Welcome(SOCKET SID) {
    out(SID, string("\n---欢迎来到龙之谷---\n"));
    out(SID, string("这里是龙裔与驯龙师共存的世外桃源...\n"));
}

bool name_in(int& id, SOCKET SID) {
    out(SID, string( "\n请输入用户名: "));
    string na;
    na = get(SID);
    for (auto it = user::umap.begin(); it != user::umap.end(); it++) {
        if (it->second->get_name() == na) id = it->first;
    }
    if (id == -1) {
        out(SID, string( ">>该用户不存在,请重新输入\n"));
        return false;
    }
    return true;
}

int pass_in(int id, SOCKET SID) {
    out(SID, string( "请输入密码: "));
    string pa;
    pa = get(SID);
    if (pa != user::umap[id]->get_password()) {
        out(SID, string( ">>密码错误，请重新输入\n"));
        return 0;
    }
    return 1;
}


int Begin(SOCKET SID) {
    int id = -1;
    while (1) {
        if(name_in(id, SID)) break;
        
    }
    while (1)
    {
        if (pass_in(id, SID)) break;

    }
    out(SID, string( "\n>>登录成功<<\n"));
    return id;
}


//int main()
//{
//    Initial();
//    Welcome();
//    /*while (1) {
//        if (Begin()) break;
//    }*/
//    //开始!!!
//
//    while (1) {
//        user* u = user::umap[1];
//        int pos = u->get_pos();
//        maps::MP[pos]->show();
//        while (1)
//        {
//            out(SID, << "\n ..输入help以查看可选操作..\n";
//            string op;
//            cin >> op;
//            if (operate(u, op)) break;
//        }
//    }
//    return 0;
//}