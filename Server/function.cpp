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
    string name = "��ʥѩԭ";
    string dis = "����һƬ��ã��ѩԭ������ķ�ѩ�����ڸ������ߵ����ߣ������ѩ�������������������������Ľ�Х����˵���������Ĵ����֮һ��˪��������Ϣ��....";
    vector<int>* ob = new vector<int>;
    vector<int>* poke = new vector<int>;
    maps* p = new maps(name, dis, *ob, *poke);
    return;
}


void Initial_map_2() {
    string name = "��յ�";
    string d = "����һ�����յĵ���, ����Ҫ���з����������������ǰ��";
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
    new damage("������", "����һ֧��˪��ʸ", 10, 0.2, 0);
}

void initial_skill_2() {
    new buff("˪��", "����һ�㻤��, ��������ս���ķ�����", 1, 10, 0);
}

void initial_skill() {
    initial_skill_1();
    initial_skill_2();
}

void initial_poke_1(int pos,int uid) {
    string name = "��ԭ��������";
    string d = "����һֻ�����ڱ�ѩ���������ᣬ�����������ʵ�ԭʼ������Ѫ������ϡ�����Ѿ�ʧȥ�˷�������";
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
    string s1 = "Զ�����ÿͰ�...����ϡ��..", s2 = "�������һ��ѱ���߰�...", s3 = "������ֻ�������ԭ����Ŀ�ĵ��ε��Ŀ����λ����..";
    vector<string>s;
    s.push_back(s1); s.push_back(s2); s.push_back(s3);
    bean* p = new bean(10);
    p->setpos(-1);
    string na = "��ȱ�������λ�", di = "����һ���������λ꣬�Ѿ������������ԭ����";
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
        out(SID,  string("��ѡ���ս��ѵ������:\n"));
        int cnt = (int)p->poke.size();
        p->show_poke(SID);
        string tid = "-1";
        tid = get(SID);
        if (tid == "-1" || !isnum(tid) || atoi(tid.c_str()) > cnt) { out(SID, string("������") + "1" + "~" + to_string(cnt) + "֮�������\n"); }
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
    out(SID,  p2->get_name()+ " ������!\n" );
    int pid1 = fight_begin(u1, SID);
    p1 = pokemon::POKE[pid1];
    p1->init_fight();
    p2->init_fight();
    int round = 0;
    while (1) {
        round++;
        out(SID, string( "-------------------��" ) +  to_string(round) + "�غ�---------------------\n") ;
        p1->show_status(SID);
        out(SID, string( "      VS      "));
        p2->show_status(SID);
        out(SID, string("\n"));
        int sk_id = 0;
        while (1) {
            out(SID, string( "��ѡ����:\n" ));
            int total = (int)p1->skill.size();
            p1->show_skill(SID);
            string tid = "-1";
            tid = get(SID);
            if (tid == "-1" || !isnum(tid) || atoi(tid.c_str()) > total) { 
                out(SID, string("������") + "1" + "~" + to_string(total) + "֮�������\n"); 
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
        out(SID, string( "��") + Skill::SK[sk_id]->use_skill(pid1, pid2, SID) + "             ");
        if (p2->HP == 0) {
            out(SID, string( "��ɹ�������")+ p2->get_name());
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
                    out(SID, string( "�Է�") + Skill::SK[t]->use_skill(pid2, pid1, SID) + "\n");
                }
            }
            if (p1->HP == 0) {
                out(SID, string( "�㱻") + p2->get_name() + "������\n");
                break;
            }
        }
    }
    p1->init_fight();
    p2->init_fight();
}

void show_help(SOCKET SID) {
    out(SID, string("1. move [e/w/s/n] ��/��/��/�������ƶ�\n"));
    out(SID, string("2. see [road/stuff]�鿴����\n"));
    out(SID, string("3. act [number] �뷢�ֵ���Ʒ�����໥��\n"));
    out(SID, string("4. help �鿴�����ֲ�\n"));
    out(SID, string("5. check [other/dragon/package/domed] [number] �۲쳡����Ʒ������/Ұ������/��������Ʒ/��ѱ��������\n"));
    out(SID, string("6. fight [number] ��Ŀ������ս��\n"));
    out(SID, string("7. view [package/domed] �鿴����/��ѱ��������\n"));
    out(SID, string("8. use [number] ʹ�ñ�������Ʒ\n"));
    return;
}

void see(user* u, SOCKET SID) {
    string op2;
    op2 = get(SID);
    if (op2 == "road") maps::MP[u->pos]->show_link(SID);
    else  if (op2 == "stuff") maps::MP[u->pos]->show_ob_po(u,SID);
    else  out(SID, string( "\n--ָ���޷�ʶ�𣬺����׵Ҷ������������ƺ���ʴ���������..--\n"));
    return;
}

void act_with(user* u, SOCKET SID) {
    string id;
    id = get(SID);
    if (!isnum(id)) {
        out(SID, string( "\n--ָ���޷�ʶ�𣬺����׵Ҷ������������ƺ���ʴ���������..--\n"));
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
    if (!bj) out(SID, string( "\n���ƺ������˶Բ�������Ļþ�..\n"));
    return;
}

void check_ob(user* u, SOCKET SID) {
    string type;
    string id;
    type = get(SID);
    id = get(SID);
    if (!isnum(id)) {
        out(SID, string( "\n--ָ���޷�ʶ�𣬺����׵Ҷ������������ƺ���ʴ���������..--\n"));
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
        if (!bj) out(SID, string( "\n���ƺ������˶Բ�������Ļþ�..\n"));
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
        if (!bj) out(SID, string( "\n���ƺ������˶Բ�������Ļþ�..\n"));
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
        out(SID, string( "\n--ָ���޷�ʶ�𣬺����׵Ҷ������������ƺ���ʴ���������..--\n"));
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
    if (!bj) out(SID, string( "\n���ƺ������˶Բ����ڵ�����Ļþ�..\n"));
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
        out(SID, string("�㴵�������ڣ�������:\n"));
        u->show_poke(SID);
        return;
    }
    out(SID, string( "\n--ָ���޷�ʶ�𣬺����׵Ҷ������������ƺ���ʴ���������..--\n"));
    return;
}

void user_use(user* u, SOCKET SID) {
    string id;
    id = get(SID);
    if (!isnum(id)) {
        out(SID, string("\n--ָ���޷�ʶ�𣬺����׵Ҷ������������ƺ���ʴ���������..--\n"));
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
    out(SID, string( "\n--ָ���޷�ʶ�𣬺����׵Ҷ������������ƺ���ʴ���������..--\n"));

    return false;
}

void Welcome(SOCKET SID) {
    out(SID, string("\n---��ӭ������֮��---\n"));
    out(SID, string("������������ѱ��ʦ�����������Դ...\n"));
}

bool name_in(int& id, SOCKET SID) {
    out(SID, string( "\n�������û���: "));
    string na;
    na = get(SID);
    for (auto it = user::umap.begin(); it != user::umap.end(); it++) {
        if (it->second->get_name() == na) id = it->first;
    }
    if (id == -1) {
        out(SID, string( ">>���û�������,����������\n"));
        return false;
    }
    return true;
}

int pass_in(int id, SOCKET SID) {
    out(SID, string( "����������: "));
    string pa;
    pa = get(SID);
    if (pa != user::umap[id]->get_password()) {
        out(SID, string( ">>�����������������\n"));
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
    out(SID, string( "\n>>��¼�ɹ�<<\n"));
    return id;
}


//int main()
//{
//    Initial();
//    Welcome();
//    /*while (1) {
//        if (Begin()) break;
//    }*/
//    //��ʼ!!!
//
//    while (1) {
//        user* u = user::umap[1];
//        int pos = u->get_pos();
//        maps::MP[pos]->show();
//        while (1)
//        {
//            out(SID, << "\n ..����help�Բ鿴��ѡ����..\n";
//            string op;
//            cin >> op;
//            if (operate(u, op)) break;
//        }
//    }
//    return 0;
//}