// test1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <ctime>
#include"maps.h"
#include"object.h"
#include"user.h"
#include"pokemon.h"
using namespace std;

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
    vector<int>*ob=new vector<int>;
    vector<int>*poke=new vector<int>;
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
    string name = "name";
    string pass = "123456";
    user *p = new user(name, pass);
    p->pos = 1;
}

void initial_user() {
    initial_user_1();
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

void initial_poke_1(int pos) {
    string name = "冰原地龙幼崽";
    string d = "这是一只生长在冰雪地区的龙裔，由于身体流淌的原始古龙的血脉过于稀薄，已经失去了飞行能力";
    pokemon * p = new pokemon(name, d,1,pos);
    p->insert_skill(1);
    p->insert_skill(2);
    if (pos) {
        maps::MP[pos]->insert_po(p->get_id());
    }
    else {
        user* u = user::umap[1];
        u->insert_poke(p->get_id());
    }
    p->ability["FLY"] = 0;
    return;
}

void initial_poke() {
    initial_skill();
    initial_poke_1(1);
    initial_poke_1(0);
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
    string na = "残缺的老妪游魂",di = "这是一个可怜的游魂，已经快消逝在这冰原中了";
    npc* p2 = new npc(s, 5, na, di);
    p2->setpos(1);
    maps::MP[1]->insert_ob(p2->get_id());
}

void Initial() {
    initial_user_1();
    Initial_map_1();
    Initial_map_2();
    link_map(1,2,'e');
    initial_poke();
    Initial_key();
    Initial_bean();
    Initial_box();
    Initial_npc();
    srand((unsigned int)time(NULL));
}

int fight_begin(int u1) {
    user* p = user::umap[u1];
    int tarp = 0;
    while (1) {
        cout << "请选择出战的训化龙裔:" << endl;
        int cnt = (int)p->poke.size();
        p->show_poke();
        string tid = "-1";
        cin >> tid;
        if (tid == "-1" ||!isnum(tid)|| atoi(tid.c_str()) > cnt) { cout << "请输入" << 1 << "~" << cnt << "之间的整数" << endl; }
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

void fight(int u1, int pid2) {
    pokemon* p1, * p2 = pokemon::POKE[pid2];
    cout << p2->get_name() << " 出现了!" << endl;
    int pid1 = fight_begin(u1);
    p1 = pokemon::POKE[pid1];
    p1->init_fight();
    p2->init_fight();
    int round = 0;
    while (1) {
        round++;
        cout << "-------------------第"<< round << "回合---------------------" << endl;
        p1->show_status();
        cout << "      VS      ";
        p2->show_status();
        cout << endl;
        int sk_id = 0;
        while (1) {
            cout << "请选择技能:" << endl;
            int total = (int)p1->skill.size();
            p1->show_skill();
            string tid = "-1";
            cin >> tid;
            if (tid == "-1" ||!isnum(tid)|| atoi(tid.c_str()) > total) { cout << "请输入" << 1 << "~" << total << "之间的整数" << endl; }
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
        cout << "你" << Skill::SK[sk_id]->use_skill(pid1, pid2) << "             ";
        if (p2->HP == 0) {
            cout << "你成功击败了" << p2->get_name() << endl;
            p1->exp_up((int)ceil(exp_needed[p2->level-1] * 0.5));
            break;
        }
        else {
            int total2 = (int)p2->skill.size();
            int tid2 = (int)ceil((double)rand() / RAND_MAX * total2);
            total2 = 0;
            for (auto t : p2->skill) {
                total2++;
                if (tid2 == total2) {
                    cout << "对方" << Skill::SK[t]->use_skill(pid2, pid1) << endl;
                }
            }
            if (p2->HP == 0) {
                cout << "你被" << p2->get_name() << "击败了" << endl;
                break;
            }
        }
    }
    p1->init_fight();
    p2->init_fight();
}

void show_help() {
    cout << "1. move [e/w/s/n] 向东/西/南/北方向移动\n";
    cout << "2. see [road/stuff]查看周遭\n";
    cout << "3. act [number] 与发现的物品或人类互动\n";
    cout << "4. help 查看帮助手册\n";
    cout << "5. check [other/dragon/package/domed] [number] 观察场景物品或人类/野生生物/背包内物品/已驯服的龙裔\n";
    cout << "6. fight [number] 与目标生物战斗\n";
    cout << "7. view [package/domed] 查看背包/被驯服的龙裔\n";
    return;
}

void see(user *u) {
    string op2;
    cin >> op2;
    if (op2 == "road") maps::MP[u->pos]->show_link();
    else  if (op2 == "stuff") maps::MP[u->pos]->show_ob_po();
    else  cout << "\n--指令无法识别，黑龙米狄尔遗留的瘴气似乎侵蚀了你的理智..--\n";
    return;
}

void act_with(user *u) {
    string id;
    cin >> id;
    if (!isnum(id)) {
        cout << "\n--指令无法识别，黑龙米狄尔遗留的瘴气似乎侵蚀了你的理智..--\n";
        return;
    }
    int cnter = 0,bj=0;
    maps& t = *maps::MP[u->pos];
    for (auto it = t.ob.begin(); it != t.ob.end(); it++) {
        cnter++;
        if (cnter == atoi(id.c_str())) {
            object::OB[*it]->act(u);
            bj = 1;
            break;
        }
    }
    if (!bj) cout << "\n你似乎出现了对不存在物的幻觉..\n";
    return;
}

void check_ob(user *u) {
    string type;
    string id;
    cin >> type>>id;
    if (!isnum(id)) {
        cout << "\n--指令无法识别，黑龙米狄尔遗留的瘴气似乎侵蚀了你的理智..--\n";
        return;
    }
    if (type == "other"){
        int cnter = 0, bj = 0;
        maps& t = *maps::MP[u->pos];
        for (auto it = t.ob.begin(); it != t.ob.end(); it++) {
            cnter++;
            if (cnter == atoi(id.c_str())) {
                object::OB[*it]->show();
                bj = 1;
                break;
            }
        }
        if (!bj) cout << "\n你似乎出现了对不存在物的幻觉..\n";
    }
    else if(type=="dragon") {
        int cnter = 0, bj = 0;
        maps& t = *maps::MP[u->pos];
        for (auto it = t.poke.begin(); it != t.poke.end(); it++) {
            cnter++;
            if (cnter == atoi(id.c_str())) {
                pokemon::POKE[*it]->show_dis();
                bj = 1;
                break;
            }
        }
        if (!bj) cout << "\n你似乎出现了对不存在物的幻觉..\n";
    }
    else if (type == "package") {
        u->check_package(atoi(id.c_str()));

    }
    else if (type == "domed") {
        u->check_domed(atoi(id.c_str()));
    }
    return;
}

bool move_position(user *u) {
    char a;
    cin >> a;
    if(u->move(a)) return true;
    return false;
}

void fight_start(user *u) {
    string id;
    cin >> id;
    if (!isnum(id)) {
        cout << "\n--指令无法识别，黑龙米狄尔遗留的瘴气似乎侵蚀了你的理智..--\n";
        return;
    }
    int cnter = 0, bj = 0;
    maps& t = *maps::MP[u->pos];
    for (auto it = t.poke.begin(); it != t.poke.end(); it++) {
        cnter++;
        if (cnter == atoi(id.c_str())) {
            int i = pokemon::POKE[*it]->get_id();
            fight(u->get_id(), i);
            bj = 1;
            break;
        }
    }
    if(!bj) cout << "\n你似乎出现了对不存在的龙裔的幻觉..\n";
    return;
}

void view_me(user* u) {
    string type;
    cin >> type;
    if (type == "package") {
        u->show_pack();
        return;
    }
    else if (type == "domed") {
        return;
    }
    cout << "\n--指令无法识别，黑龙米狄尔遗留的瘴气似乎侵蚀了你的理智..--\n";
    return;
}


bool operate(user* u,string op) {
    if (op == "help") {show_help();return false;}
    if (op == "see") {see(u);return false;}
    if (op == "act") { act_with(u); return false; }
    if (op == "fight") { fight_start(u); return false; }
    if (op == "check") { check_ob(u); return false; }
    if (op == "move") { if (move_position(u)) return true; else return false; }
    if (op == "view") { view_me(u); return false; }
    cout << "\n--指令无法识别，黑龙米狄尔遗留的瘴气似乎侵蚀了你的理智..--\n";

    return false;
}

void Welcome() {
    cout << "\n---欢迎来到龙之谷---\n";
    cout << "这里是龙裔与驯龙师共存的世外桃源...\n";
}

int name_in(int &id){
    cout << "\n请输入用户名: ";
    string na;
    cin >> na;
    for (auto it = user::umap.begin(); it != user::umap.end(); it++) {
        if (it->second->get_name() == na) id = it->first;
    }
    if (id == '-1') {
        cout << ">>该用户不存在,请重新输入\n";
        return 0;
    }
    return 1;
}

int pass_in(int id) {
    cout << "请输入密码: ";
    string pa;
    cin >> pa;
    if (pa != user::umap[id]->get_password()) {
        cout << ">>密码错误，请重新输入\n";
        return 0;
    }
    return 1;
}
bool Begin() {
    int id=-1;
    while (1) {
        if (name_in(id)) break;
    }
    while (1)
    {
        if (pass_in(id)) break;
    }
    cout << "\n>>登录成功<<\n";
    return true;
}


int main()
{
    Initial();
    Welcome();
    /*while (1) {
        if (Begin()) break;
    }*/
    //开始!!!
    
    while (1) {
        user* u = user::umap[1];
        int pos = u->get_pos();
        maps::MP[pos]->show();
        while (1)
        {
            cout << "\n ..输入help以查看可选操作..\n";
            string op;
            cin >> op;
            if (operate(u, op)) break;
        }
    }
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
