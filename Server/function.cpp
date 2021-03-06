#include <iostream>
#include <ctime>
#include <map>
#include <thread>

#include"function.h"

using namespace std;

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

int exp_needed[max_level] = { 10, 20, 30, 50, 100, 150, 200, 300, 500, 1000, 1500, 2000, 3000, 5000, 10000 };
extern map<int, SOCKET> UID2SID;
extern map<SOCKET, int> SID2UID;
extern map<int, communicator> comap;
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
    string d = "这是一座浮空的岛屿, 抬头望去只能看到山一样巨大的巨岩,需要具有飞行能力的龙裔才能前往";
    vector<int>* ob = new vector<int>;
    vector<int>* po = new vector<int>;
    maps* p = new maps(name, d, *ob, *po);
    return;
}

void Initial_map_3() {
    string name = "圣巢废墟";
    string d = "这里曾是古龙首领的神圣巢穴，现在只留下了断裂的石柱和布满灰尘的黄金基座，由于更接近恩泽，这里龙裔较多的保留着古龙的血脉...";
    vector<int>* ob = new vector<int>;
    vector<int>* po = new vector<int>;
    maps* p = new maps(name, d, *ob, *po);
    return;
}

void Initial_map_4() {
    string name = "初始火炉";
    string d = "这里是古龙时代时火龙一族授予幼龙初始之火仪式的地方，如今只剩下万亿年的火炉还在微弱地燃烧...";
    vector<int>* ob = new vector<int>;
    vector<int>* po = new vector<int>;
    maps* p = new maps(name, d, *ob, *po);
    return;
}

void Initial_map_5() {
    string name = "岩石要塞";
    string d = "这是曾经虚空侵袭时遭遇的第一座要塞，岩石巨龙曾在这里驻守，如今的后裔都是它的血脉...";
    vector<int>* ob = new vector<int>;
    vector<int>* po = new vector<int>;
    maps* p = new maps(name, d, *ob, *po);
    return;
}

void Initial_map_6() {
    string name = "空洞荒原";
    string d = "这里什么都没有...或许古龙的时代这里也曾繁荣昌盛，可如今已经被虚空腐蚀，就连空间和时间也消失了....";
    vector<int>* ob = new vector<int>;
    vector<int>* po = new vector<int>;
    maps* p = new maps(name, d, *ob, *po);
    return;
}

void initial_user_1() {
    string name = "wyf";
    string pass = "1";
    user* p = new user(name, pass);
    p->pos = 1;
}

void initial_user_2() {
    string name = "wjk";
    string pass = "2";
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
    new buff("霜铠", "凝结一层护盾, 提升本局战斗的防御力", 1, 15, 0);
}
void initial_skill_3() {
    new buff("凝冰", "吸收空气中的冰元素, 提升本局战斗的攻击力", 1.5, 0, 0);
}
void initial_skill_4() {
    new damage("龙之吐息", "释放带有上古力量的龙息", 20, 0.5, 0);
}
void initial_skill_5() {
    new damage("绝对零度", "吞噬空气中的热量(连续使用该技能, 伤害越来越高)", 5, 0, 0);
}
void initial_skill_6() {
    new damage("霜之哀伤", "利用空气中的冰元素, 让自己非常哀伤(必定暴击)", 1, 1.0, 0);
}
void initial_skill_7() {
    new damage("急速风刃", "连续释放大量风刃切割敌人", 25, 0.2, 0);
}
void initial_skill_8() {
    new buff("休眠", "进入休眠状态, 提升少量防御力", 1, 10, 0);
}
void initial_skill_9() {
    new buff("龙血禁咒", "使用上古巨龙血脉中的力量, 以自身防御力为代价, 提升大量攻击力", 2, -20, 0);
}
void initial_skill_10() {
    new damage("龙骨突刺", "使用骨刺对敌方进行攻击", 20, 0, 0);
}
void initial_skill_11() {
    new damage("火龙球", "喷出火球攻击地方", 25, 0, 0);
}

void initial_skill() {
    initial_skill_1();
    initial_skill_2();
    initial_skill_3();
    initial_skill_4();
    initial_skill_5();
    initial_skill_6();
    initial_skill_7();
    initial_skill_8();
    initial_skill_9();
    initial_skill_10();
    initial_skill_11();
}

void initial_poke_1(int pos, int uid) {
    string name = "冰原地龙幼崽";
    string d = "这是一只生长在冰雪地区的龙裔，由于身体流淌的原始古龙的血脉过于稀薄，已经失去了飞行能力";
    pokemon* p = new pokemon(name, d, 1, pos);
    p->insert_skill(1);
    p->insert_skill(2);
    p->insert_skill(3);
    p->insert_skill(6);
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

void initial_poke_2(int pos, int uid) {
    string name = "成年冰原地龙";
    string d = "这是一只生长在冰雪地区的龙裔，由于身体流淌的原始古龙的血脉过于稀薄，已经失去了飞行能力";
    pokemon* p = new pokemon(name, d, 2, pos);
    p->insert_skill(1);
    p->insert_skill(2);
    p->insert_skill(3);
    p->insert_skill(5);
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

void initial_poke_3(int pos, int uid) {
    string name = "天空龙";
    string d = "上古天空的霸主, 星空之下最强的一族";
    pokemon* p = new pokemon(name, d, 1, pos);
    p->insert_skill(4);
    p->insert_skill(7);
    p->insert_skill(8);
    p->insert_skill(9);
    if (pos) {
        maps::MP[pos]->insert_po(p->get_id());
    }
    else {
        user* u = user::umap[uid];
        u->insert_poke(p->get_id());
    }
    p->ability["FLY"] = 1;
    return;
}

void initial_poke_4(int pos, int uid) {
    string name = "骨龙";
    string d = "上古战场残存的尸骸, 如今又被神秘力量复苏";
    pokemon* p = new pokemon(name, d, 4, pos);
    p->insert_skill(10);
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

void initial_poke_5(int pos, int uid) {
    string name = "熔岩巨龙";
    string d = "熔岩中诞生的巨龙";
    pokemon* p = new pokemon(name, d, 5, pos);
    p->insert_skill(11);
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
    initial_poke_2(1,0);
    initial_poke_4(5,0);
    initial_poke_5(4,0);
    initial_poke_3(3,0);
}

int Initial_key(int pos) {
    key* p = new key();
    p->setpos(pos);
    if(pos!=-1) maps::MP[pos]->insert_ob(p->get_id());
    return p->get_id();
}

int  Initial_box(int id,int pos) {
    box* p = new box(0);
    p->insert(id);
    p->setpos(pos);
    if(pos!=-1) maps::MP[pos]->insert_ob(p->get_id());
    return p->get_id();
}

int Initial_bean(int pos) {
    bean* p = new bean(10);
    p->setpos(pos);
    if (pos != -1) maps::MP[pos]->insert_ob(p->get_id());
    return p->get_id();
}

int Initial_npc(int id,int pos) {
    string s1 = "远方的旅客啊...真是稀奇..", s2 = "你是最后一脉驯龙者吧...", s3 = "我吗？我只是在这冰原漫无目的地游荡的可怜游魂罢了..";
    vector<string>s;
    s.push_back(s1); s.push_back(s2); s.push_back(s3);
    string na = "残缺的老妪游魂", di = "这是一个可怜的游魂，已经快消逝在这冰原中了";
    npc* p2 = new npc(s, id, na, di);
    p2->setpos(pos);
    if (pos != -1) maps::MP[pos]->insert_ob(p2->get_id());
    return p2->get_id();
}

int Initial_npc2(int id, int pos) {
    string s1 = "劈里啪啦...(你是..火龙大人吗...)", s2 = "劈里啪啦劈里啪啦...(我好孤独啊...)", s3 = "啾啾劈里啪啦(快跑吧..离开吧....虚空终将吞噬我们...龙的时代已经消逝了..)";
    vector<string>s;
    s.push_back(s1); s.push_back(s2); s.push_back(s3);
    string na = "孤独的火苗", di = "衰老的初始之火火苗，见证了火龙的衰亡和虚空的侵蚀..";
    npc* p2 = new npc(s, id, na, di);
    p2->setpos(pos);
    if (pos != -1) maps::MP[pos]->insert_ob(p2->get_id());
    return p2->get_id();
}

void Initialmaps()
{
    Initial_map_1();
    Initial_map_2();
    Initial_map_3();
    Initial_map_4();
    Initial_map_5();
    Initial_map_6();
    link_map(1, 2, 'e');
    link_map(1, 3, 'w');
    link_map(1, 4, 's');
    link_map(1, 5, 'n');
    link_map(5, 6,'e');
}

void Initialobject() {
    Initial_key(1);
    Initial_bean(1);
    int id_bean= Initial_bean(-1);
    Initial_box(id_bean,1);
    id_bean = Initial_bean(-1);
    Initial_npc(id_bean,1);
    Initial_bean(2);
    Initial_bean(2);
    Initial_bean(3);
    Initial_bean(4);
    Initial_bean(5);
    id_bean = Initial_bean(-1);
    Initial_box(id_bean,3);
    int id_key = Initial_key(-1);
    Initial_box(id_key, 3);
    Initial_key(5);
    id_bean = Initial_bean(-1);
    Initial_box(id_bean,4);
    id_key = Initial_key(-1);
    Initial_npc2(id_key, 4);
}

void Initial() {
    initial_user();
    Initialmaps();
    Initialobject();
    initial_poke();
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

int find_nth_skill(pokemon *p, int n) {
    int total = 0, sk_id = 0;
    for (auto t : p->skill) {
        total++;
        if (n == total) {
            sk_id = t;
            break;
        }
    }
    return sk_id;
}

void fight_pvp(int u1, int u2, SOCKET SID1, SOCKET SID2) {
    user* up1 = user::umap[u1], * up2 = user::umap[u2];
    comap[u2].set_asked(u1);
    out(SID1, string("正在等待")+up2->get_name()+"接受战斗!\n@");
    get(SID1);// 立即输出s
    int cntms = 50;
    int gofight = 0;
    while (1) {
        this_thread::sleep_for(chrono::milliseconds(100));
        cntms++;
        if (comap[u1].get_reply()) {
            if (comap[u1].get_reply() == 1) {
                out(SID1, up2->get_name() + "接受了你的战斗邀请\n");
                gofight = 1;
            }
            else if (comap[u1].get_reply() == 2) {
                out(SID1, up2->get_name() + "拒绝了你的战斗邀请\n");
            }
            break;
        }
        if (cntms % 100 == 0) {
            out(SID1, string("正在等待") + up2->get_name() + "接受战斗!\n继续等待请按1, 放弃等待请按2\n");
            comap[u2].cancel_asked();
            string wait = get(SID1);
            if (wait[0] == '1') {
                comap[u2].set_asked(u1);
                continue;
            }
            else if (wait[0] ==  '2') {
                break;
            }
        }
    }
    if (gofight == 0) return;

    int pid1 = fight_begin(u1, SID1);
    int pid2 = fight_begin(u2, SID2);

    pokemon* p1 = pokemon::POKE[pid1], * p2 = pokemon::POKE[pid2];

    out(SID1,  string("对方派出了")+ p2->get_name() +"!\n");
    out(SID2,  string("对方派出了")+ p1->get_name() +"!\n");
    p1->init_fight();
    p2->init_fight();
    int round = 0;
    while (1) {
        round++;
        out(SID1, string("------------------------第") + to_string(round) + "回合---------------------------(你的回合)\n");
        p1->show_status(SID1);
        out(SID1, string("      VS      "));
        p2->show_status(SID1);
        out(SID1, string("\n"));

        out(SID2, string("------------------------第") + to_string(round) + "回合---------------------------(对方回合)\n");
        p2->show_status(SID2);
        out(SID2, string("      VS      "));
        p1->show_status(SID2);
        out(SID2, string("\n@"));
        get(SID2);

        int sk_id1 = 0, sk_id2 = 0;
        while (1) {
            if (sk_id1 == 0) {
                out(SID1, string("请选择技能:\n"));
                int total = p1->skill.size();
                p1->show_skill(SID1);
                string tid = "-1";
                tid = get(SID1);
                if (tid == "-1" || !isnum(tid) || atoi(tid.c_str()) > total) {
                    out(SID1, string("请输入") + "1" + "~" + to_string(total) + "之间的整数\n");
                }
                else {
                    sk_id1 = find_nth_skill(p1, atoi(tid.c_str()));
                    break;
                }
            }
        }
        string num1 = Skill::SK[sk_id1]->use_skill(pid1, pid2);

        out(SID1, string("你") + num1 + "\n");
        out(SID2, string("对方") + num1 + "\n");



        if (p2->HP == 0) {
            out(SID1, string("你成功击败了") + up2->get_name());
            p1->exp_up((int)ceil(exp_needed[p2->level] * 0.5), SID1);
            out(SID2, string("你被") + up1->get_name() + "击败了");
            break;
        }
        else {
            round++;

            out(SID1, string("------------------------第") + to_string(round) + "回合---------------------------(对方回合)\n");
            p1->show_status(SID1);
            out(SID1, string("      VS      "));
            p2->show_status(SID1);
            out(SID1, string("\n@"));
            get(SID1);

            out(SID2, string("------------------------第") + to_string(round) + "回合---------------------------(你的回合)\n");
            p2->show_status(SID2);
            out(SID2, string("      VS      "));
            p1->show_status(SID2);
            out(SID2, string("\n"));

            while (1) {
                if (sk_id2 == 0) {
                    out(SID2, string("请选择技能:\n"));
                    int total = p2->skill.size();
                    p2->show_skill(SID2);
                    string tid = "-1";
                    tid = get(SID2);
                    if (tid == "-1" || !isnum(tid) || atoi(tid.c_str()) > total) {
                        out(SID2, string("请输入") + "1" + "~" + to_string(total) + "之间的整数\n");
                    }
                    else {
                        sk_id2 = find_nth_skill(p2, atoi(tid.c_str()));
                        break;
                    }
                }
            }
            string num2 = Skill::SK[sk_id2]->use_skill(pid2, pid1);
            out(SID2, string("你") + num2 + "\n");
            out(SID1, string("对方") + num2 + "\n");
            if (p1->HP == 0) {
                out(SID2, string("你成功击败了") + up1->get_name());
                p2->exp_up((int)ceil(exp_needed[p1->level - 1] * 0.5), SID2);
                out(SID1, string("你被") + up2->get_name() + "击败了");
                break;
            }
        }
    }
    p1->init_fight();
    p2->init_fight();
    comap[u2].set_finish();
    comap[u1].init();
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
                /*total = 0;
                for (auto t : p1->skill) {
                    total++;
                    if (atoi(tid.c_str()) == total) {
                        sk_id = t;
                        break;
                    }
                }*/
                sk_id = find_nth_skill(p1, atoi(tid.c_str()));
                break;
            }
        }
        out(SID, string( "你") + Skill::SK[sk_id]->use_skill(pid1, pid2) + "             ");
        if (p2->HP == 0) {
            out(SID, string( "你成功击败了")+ p2->get_name());
            p1->exp_up((int)ceil(exp_needed[p2->level - 1] * 0.5), SID);
            out(SID, string("是否捕捉击败的龙裔(y/n)?"));
            while (1) {
                string yn = get(SID);
                if (yn[0] == 'y' || yn[0] == 'Y') {
                    out(SID, string("捕捉成功!你获得了") + p2->get_name());
                    user::umap[u1]->insert_poke(p2->get_id());
                    break;
                }
                else if (yn[0] == 'n' || yn[0] == 'N') {
                    out(SID, string("你放弃了捕捉"));
                    break;
                }
                else {
                    out(SID, string("请输入'y'捕捉或输入'n'放弃捕捉\n"));
                    continue;
                }
            }
            break;
        }
        else {
            int total2 = (int)p2->skill.size();
            int tid2 = (int)ceil((double)rand() / RAND_MAX * total2);

            sk_id = find_nth_skill(p2, tid2);
            out(SID, string("对方") + Skill::SK[sk_id]->use_skill(pid2, pid1) + "\n");
            /*total2 = 0;
            for (auto t : p2->skill) {
                total2++;
                if (tid2 == total2) {
                    out(SID, string( "对方") + Skill::SK[t]->use_skill(pid2, pid1, SID) + "\n");
                }
            }*/
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
    out(SID, string("6. fight [player/dragon][number] 与目标玩家或生物战斗\n"));
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
    string object;
    object = get(SID);
    if (object != "player" && object != "dragon") {
        out(SID, string("\n--指令无法识别，黑龙米狄尔遗留的瘴气似乎侵蚀了你的理智..--\n"));
        return;
    }
    string sid;
    sid = get(SID);
    if (!isnum(sid)) {
        out(SID, string( "\n--指令无法识别，黑龙米狄尔遗留的瘴气似乎侵蚀了你的理智..--\n"));
        return;
    }
    int id = atoi(sid.c_str());
    int cnter = 0, bj = 0;
    maps& t = *maps::MP[u->pos];
    if (object == "dragon") {
        for (auto it = t.poke.begin(); it != t.poke.end(); it++) {
            cnter++;
            if (cnter == id) {
                int i = pokemon::POKE[*it]->get_id();
                fight(u->get_id(), i, SID);
                bj = 1;
                break;
            }
        }
    }
    else if (object == "player") {
        for (auto t : user::umap) {
            if (t.second->get_pos() != u->get_pos() || t.second->get_id() == u->get_id()) continue; // 如果不在同一地点
            cnter++;
            if (cnter == id) {
                int u2 = t.second->get_id();
                fight_pvp(u->get_id(), u2, SID, UID2SID[u2]);
                bj = 1;
                break;
            }
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