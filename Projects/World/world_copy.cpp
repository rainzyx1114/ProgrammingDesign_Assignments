#include <iostream>
#include <cstdio>
#include <vector>
#include <array>
#include <cstring>
#include <algorithm>
#include <stdlib.h>
#include <stack>
#include <memory>

using namespace std;

class warrior;

enum class WeaponType {
    sword,
    bomb,
    arrow
};

enum class WarriorType {
    dragon,
    ninja,
    iceman,
    lion,
    wolf
};

class headquarter {
    WarriorType loop[5];
    int loopcount{0};
    public:
        vector<unique_ptr<warrior>> warriors;
        string name;
        int totallife{0};
        int location;
        headquarter(const char* n):name(n) {
            if (name == "red") {
                loop[0] = WarriorType::iceman;loop[1] = WarriorType::lion;loop[2] = WarriorType::wolf;loop[3] = WarriorType::ninja;loop[4] = WarriorType::dragon;
            }
            else if (name == "blue") {
                loop[0] = WarriorType::lion;loop[1] = WarriorType::dragon;loop[2] = WarriorType::ninja;loop[3] = WarriorType::iceman;loop[4] = WarriorType::wolf;
            }
        }
        void reset();
        int get_op_location();
        void warrior_create(WarriorType t);
        bool produce(int hour, int min);
};

class city {
        public:
            int flag{0}; // red->1, blue->-1
            int win_log{0}; // red->1, blue->-1
            int life{0};
            int location;
            warrior* red_warrior{nullptr};
            warrior* blue_warrior{nullptr};
            city(int l): location(l) {}
            string beg_war() {
                if (flag == 1) {return "red";}
                else if (flag == -1) {return "blue";}
                else {
                    return (location % 2 == 0? "blue" : "red");
                }
            }
};

vector<city> cities;
int N; // the number of cities
int R; // the damage of arrow
int K; // the decrease of lion's loyalty

struct WeaponConfig {
    string name;
    int use_times{0};
    int damage;
};

const char* WeaponNames[3] {"sword", "bomb", "arrow"};
struct weapon {
    WeaponConfig config;
    WeaponType type;
    weapon() = default;
    virtual void attack(warrior* attacker, warrior* opponent) {}
    virtual bool is_useful() {return true;}
    virtual ~weapon() = default;
};

struct WarriorConfig {
    string name;
    int life;
    int mark;
    int damage;
    int location;
    headquarter* belong;
    bool alive;
    bool win;
    int life_pre;
};

const char* WarriorNames[5] = {"dragon", "ninja", "iceman", "lion", "wolf"};

WarriorConfig configs[5];
class warrior {
    public:
        double courage{0};
        int loyalty{0};
        WarriorConfig config;
        WarriorType type;
        vector <unique_ptr<weapon>> weapons;
        warrior(WarriorType t, headquarter* b, int m) {
            int idx = static_cast<int>(t);
            type = t;
            config.life = configs[idx].life;
            config.name = WarriorNames[idx];
            config.damage = configs[idx].damage;
            config.mark = m;
            config.alive = true;
            config.belong = b;
            config.location = b->location;
            config.win = false;
        }
        virtual ~warrior(){
            weapons.clear();
        }
        virtual void win(warrior* opponent) {config.win = true;}
        virtual void lose() {config.win = false;}
        virtual void hurt(int d) {
            config.life -= d;
            if (config.life <= 0){
                config.alive = false;
                config.life = 0;
            }
        }
        virtual void fire(warrior* opponent, weapon* w) {
            if (w != nullptr) {
                w->attack(this, opponent);
            }
            opponent->hurt(config.damage);
        }
        virtual void feedback(warrior* opponent, weapon* w) {
            w->attack(this, opponent);
            opponent->hurt(config.damage / 2);
        }
        virtual bool move(int k) {
            if (config.belong->name == "red") {
                if (config.location == N && cities[config.location + 1].red_warrior != nullptr) {
                    cities[config.location].red_warrior = nullptr;
                    config.location ++;
                    cities[config.location].red_warrior = this;
                    return true;
                } 
                if (config.location == N + 1) return false;
                cities[config.location].red_warrior = nullptr;
                config.location ++;
                cities[config.location].red_warrior = this;
            }
            else if (config.belong->name == "blue") {
                if (config.location == 1 && cities[config.location - 1].blue_warrior != nullptr) {
                    cities[config.location].blue_warrior = nullptr;
                    config.location --;
                    cities[config.location].blue_warrior = this;
                    return true;
                }
                if (config.location == 0) return false;
                cities[config.location].blue_warrior = nullptr;
                config.location --;
                cities[config.location].blue_warrior = this;
            }
            return false;
        }
        void report(int hour, int min) {
            set_weapons();
            int arr{0},sw{0},bom{0};
            for (const auto& weapon: weapons) {
                if (weapon->type == WeaponType::arrow) {
                    arr = 3 - weapon->config.use_times;
                }
                else if (weapon->type == WeaponType::sword) {
                    sw = weapon->config.damage;
                }
                else if (weapon->type == WeaponType::bomb) {
                    bom = 1;
                }
            }
            printf("%03d:%02d %s %s %d has ", hour, min, config.belong->name.c_str(), config.name.c_str(), config.mark);
            if (arr > 0) {
                printf("arrow(%d)", arr);
            }
            if (bom > 0) {
                if (arr > 0) {printf(",");}
                printf("bomb");
            }
            if (sw > 0) {
                if (arr > 0 || bom > 0) {printf(",");}
                printf("sword(%d)", sw);
            }
            if (arr == 0 && bom == 0 && sw == 0) {
                printf("no weapon");
            }
            printf("\n");
        }
        void set_weapons() {
            for (auto it = weapons.begin(); it != weapons.end();) {
                if (!(*it)->is_useful()) {
                    (*it).reset();
                    it = weapons.erase(it);
                }
                else {
                    ++it;
                }
            }
        }
};
class sword:public weapon {
    public:
        sword(warrior& belonger):weapon() {
            config.name = WeaponNames[0];
            config.use_times = 0;
            config.damage = belonger.config.damage / 5;
            type = WeaponType::sword;
        }
        void attack(warrior* attacker, warrior* opponent) {
            opponent->hurt(config.damage);
            config.damage = config.damage * 4 / 5;
            config.use_times ++;
        }
        bool is_useful() {
            return config.damage != 0;
        }
};
class bomb:public weapon {
    public:
        bomb(warrior& belonger):weapon() {
            config.name = WeaponNames[1];
            config.use_times = 0;
            config.damage = 0;
            type = WeaponType::bomb;
        }
        void attack(warrior* attacker, warrior* opponent) {
            attacker->hurt(attacker->config.damage);
            opponent->hurt(opponent->config.damage);
            config.use_times ++;
        }
        bool is_useful() {return config.use_times < 1;}
};
class arrow:public weapon {
    public:
        arrow(warrior& belonger):weapon() {
            config.name = WeaponNames[2];
            config.use_times = 0;
            config.damage = R;
            type = WeaponType::arrow;
        }
        void attack(warrior* attacker, warrior* opponent) {
            opponent->hurt(config.damage);
            config.use_times ++;
        }
        bool is_useful() {return config.use_times < 3;}
};
class dragon: public warrior {
    public:
        dragon(WarriorType t, headquarter* b, int m):warrior(t, b, m) {
            int tmp = m % 3;
            switch(tmp) {
                case(0):
                weapons.push_back(make_unique<sword>(*this));
                break;
                case(1):
                weapons.push_back(make_unique<bomb>(*this));
                break;
                case(2):
                weapons.push_back(make_unique<arrow>(*this));
                break;
            }
            courage = b->totallife / config.life;
        }
        void win(warrior* opponent) {
            courage += 0.2;
        }
        void lose() {
            courage -= 0.2;
        }
};
class ninja: public warrior {
    public:
        ninja(WarriorType t, headquarter* b, int m):warrior(t, b, m) {
            int tmp1 = m % 3;
            int tmp2 = (m + 1) % 3;
            switch(tmp1) {
                case(0):
                weapons.push_back(make_unique<sword>(*this));
                break;
                case(1):
                weapons.push_back(make_unique<bomb>(*this));
                break;
                case(2):
                weapons.push_back(make_unique<arrow>(*this));
                break;
            }
            switch(tmp2) {
                case(0):
                weapons.push_back(make_unique<sword>(*this));
                break;
                case(1):
                weapons.push_back(make_unique<bomb>(*this));
                break;
                case(2):
                weapons.push_back(make_unique<arrow>(*this));
                break;
            }
        }
        void feedback(warrior* opponent, weapon* w) {
            return;
        }
};
class iceman: public warrior {
    int move_times{0};
    public:
        iceman(WarriorType t, headquarter* b, int m):warrior(t, b, m) {
            int tmp = m % 3;
            switch(tmp) {
                case(0):
                weapons.push_back(make_unique<sword>(*this));
                break;
                case(1):
                weapons.push_back(make_unique<bomb>(*this));
                break;
                case(2):
                weapons.push_back(make_unique<arrow>(*this));
                break;
            }
        }
        bool move( int k) {
            move_times ++;
            if (move_times != 0 && move_times % 2 == 0) {
                config.life -= 9;
                if (config.life <= 0) {
                    config.life = 1;
                }
                config.damage += 20;
            }
            bool tmp = warrior::move(k);
            return tmp;
        }
};
class lion: public warrior {
    public:
        lion(WarriorType t, headquarter* b, int m):warrior(t, b, m) {
            loyalty = b->totallife;
        }
        void lose() {
            config.win = false;
            loyalty -= K;
        }
};
class wolf: public warrior {
    public:
        using warrior::warrior;
        void win(warrior* opponent) {
            bool sw{false}, arr{false}, bom{false};
            for (const auto& w: weapons) {
                if (w->type == WeaponType::arrow) {arr = true;}
                if (w->type == WeaponType::bomb) {bom = true;}
                if (w->type == WeaponType::sword) {sw = true;}
            }
            while(!opponent->weapons.empty()) {
                if (opponent->weapons.back()->type == WeaponType::arrow && arr) {opponent->weapons.pop_back();continue;}
                if (opponent->weapons.back()->type == WeaponType::bomb && bom) {opponent->weapons.pop_back();continue;}
                if (opponent->weapons.back()->type == WeaponType::sword && sw) {opponent->weapons.pop_back();continue;}
                weapons.push_back(std::move(opponent->weapons.back()));
                opponent->weapons.pop_back();
            }
        }
};

void headquarter::reset(){
    warriors.clear();
};

int headquarter::get_op_location() {return (N + 1 - location);}

void headquarter::warrior_create(WarriorType t) {
    switch(t) {
        case WarriorType::dragon:
            warriors.push_back(make_unique<dragon>(WarriorType::dragon, this, warriors.size() + 1));
            break;
        case WarriorType::ninja:
            warriors.push_back(make_unique<ninja>(WarriorType::ninja, this, warriors.size() + 1));
            break;
        case WarriorType::iceman:
            warriors.push_back(make_unique<iceman>(WarriorType::iceman, this, warriors.size() + 1));
            break;
        case WarriorType::lion:
            warriors.push_back(make_unique<lion>(WarriorType::lion, this, warriors.size() + 1));
            break;
        case WarriorType::wolf:
            warriors.push_back(make_unique<wolf>(WarriorType::wolf, this, warriors.size() + 1));
            break;
    }
    if (name == "red") {
        cities[0].red_warrior = warriors.back().get();
    }
    else if (name == "blue") {
        cities[N + 1].blue_warrior = warriors.back().get();
    }
}

bool headquarter::produce(int hour, int min) {
    WarriorType t = loop[loopcount];
    int idx = static_cast<int>(t);
    if (configs[idx].life > totallife) {
        return false;
    }
    else {
        totallife -= configs[idx].life;
        warrior_create(t);
        printf("%03d:%02d %s %s %d born\n", hour, min, name.c_str(), WarriorNames[idx], warriors.back()->config.mark);
        if (t == WarriorType::dragon) {
            printf("Its morale is %.2lf\n", warriors.back()->courage);
        }
        else if (t == WarriorType::lion) {
            printf("Its loyalty is %d\n", warriors.back()->loyalty);
        }
        loopcount = (loopcount + 1) % 5;
        return true;
    }
}

headquarter red("red");
headquarter blue("blue");

class GameEngine {
    public:
    int hour{0};
    int min{0};
    void loop(int upper);
    void produce();
    void lion_runaway();
    bool warriors_move();
    void cities_generate();
    void warriors_take();
    void use_arrow();
    void use_bomb();
    void after_win(warrior* winner, warrior* loser, bool beg, int i);
    void war();
    void headquarters_report();
    void warriors_report();
};

void GameEngine::loop(int upper) {
    bool end = false;
    while(min + 60 * hour <= upper) {
        if (min == 0) {
            produce();
        }
        else if (min == 5) {
            lion_runaway();
        }
        else if (min == 10) {
            end = warriors_move();
        }
        if (end) {break;}
        else if (min == 20) {
            cities_generate();
        }
        else if (min == 30) {
            warriors_take();
        }
        else if (min == 35) {
            use_arrow();
        }
        else if (min == 38) {
            use_bomb();
        }
        else if (min == 40) {
            war();
        }
        else if (min == 50) {
            headquarters_report();
        }
        else if (min == 55) {
            warriors_report();
        }
        min ++;
        if (min == 60) {hour += 1; min = 0;}
    }
}

void GameEngine::produce() {
    red.produce(hour, min);
    blue.produce(hour, min);
}

void GameEngine::lion_runaway() {
    for (int i = 0; i <= N + 1; i ++) {
        warrior* r = cities[i].red_warrior;
        warrior* b = cities[i].blue_warrior;
        if (r != nullptr && r->type == WarriorType::lion) {
            if (r->loyalty <= 0 && i != N + 1) {
                cities[i].red_warrior = nullptr;
                printf("%03d:%02d red lion %d ran away\n", hour, min, r->config.mark);
                r->config.alive = false;
                r = nullptr;
            }
        }
        else if (b != nullptr && b->type == WarriorType::lion) {
            if (b->loyalty <= 0 && i != 0) {
                cities[i].blue_warrior = nullptr;
                printf("%03d:%02d blue lion %d ran away\n", hour, min, b->config.mark);
                b->config.alive = false;
                b = nullptr;
            }
        }
    }
}

bool GameEngine::warriors_move() {
    bool r_end = false;
    bool b_end = false;
    for (int i = N ; i >= 0; i --) {
        if (cities[i].red_warrior != nullptr) {
            if (i == N) {r_end = cities[i].red_warrior->move(K);}
            else {cities[i].red_warrior->move(K);}
        }
    }
    for (int i = 1; i <= N + 1; i ++) {
        if (cities[i].blue_warrior != nullptr) {
            if (i == 1) {b_end = cities[i].blue_warrior->move(K);} 
            else {cities[i].blue_warrior->move(K);}
        }
    }
    for (int i = 0; i <= N + 1; i++) {
        warrior* r = cities[i].red_warrior;
        warrior* b = cities[i].blue_warrior;
        if (r != nullptr) {
            printf("%03d:%02d ", hour, min);
            if (i == N + 1) {
                printf("red %s %d reached blue headquarter with %d elements and force %d\n", r->config.name.c_str(), r->config.mark, r->config.life, r->config.damage);
            }
            else {
                printf("red %s %d marched to city %d with %d elements and force %d\n", r->config.name.c_str(), r->config.mark, r->config.location, r->config.life, r->config.damage);
            }
            if (r_end){
                printf("%03d:%02d ", hour, min);
                printf("blue headquarter was taken\n");
            }
        }
        if (b != nullptr) {
            printf("%03d:%02d ", hour, min);
            if (i == 0) {
                printf("blue %s %d reached red headquarter with %d elements and force %d\n", b->config.name.c_str(), b->config.mark, b->config.life, b->config.damage);
            }
            else {
                 printf("blue %s %d marched to city %d with %d elements and force %d\n", b->config.name.c_str(), b->config.mark, b->config.location, b->config.life, b->config.damage);
            }   
            if (b_end) {
                printf("%03d:%02d ", hour, min);
                printf("red headquarter was taken\n");
            }
        }
    }
    return r_end || b_end;
}

void GameEngine::cities_generate() {
    for (int i = 1; i <= N; i ++) {
        cities[i].life += 10;
    }
}

void GameEngine::warriors_take() {
    for (int i = 0; i <= N + 1; i ++) {
        if (cities[i].red_warrior != nullptr && cities[i].blue_warrior == nullptr) {
            red.totallife += cities[i].life;
            cities[i].life = 0;
        }
        else if (cities[i].red_warrior == nullptr && cities[i].blue_warrior != nullptr) {
            blue.totallife += cities[i].life;
            cities[i].life = 0;
        }
    }
}

void GameEngine::use_arrow() {
    for (int i = 0; i <= N + 1; i ++) {
        warrior* r = cities[i].red_warrior;
        warrior* b = cities[i].blue_warrior;
        if (r != nullptr && i + 1 < N + 1 && cities[i + 1].blue_warrior != nullptr && !r->weapons.empty()) {
            for (auto& weapon: r->weapons) {
                if (weapon->type == WeaponType::arrow) {
                    weapon->attack(r, cities[i + 1].blue_warrior);
                    printf("%03d:%02d red %s %d shot", hour, min, r->config.name.c_str(), r->config.mark);
                    if (cities[i + 1].blue_warrior->config.alive == false) {
                        printf("and killed blue %s %d", cities[i + 1].blue_warrior->config.name.c_str(), cities[i + 1].blue_warrior->config.mark);
                    }
                    printf("\n");
                }
            }
        }
        if (b != nullptr && i - 1 > 0 && cities[i - 1].red_warrior != nullptr && !b->weapons.empty()) {
            for (auto& weapon: b->weapons) {
                if (weapon->type == WeaponType::arrow) {
                    weapon->attack(b, cities[i - 1].red_warrior);
                }
                printf("%03d:%02d blue %s %d shot", hour, min, b->config.name.c_str(), b->config.mark);
                if (cities[i - 1].red_warrior->config.alive == false) {
                    printf("and killed red %s %d", cities[i - 1].red_warrior->config.name.c_str(), cities[i - 1].red_warrior->config.mark);
                }
                printf("\n");
            }
        }
    }
}

void GameEngine::use_bomb() {
    auto sword_damage = [](warrior* w) {
        int d = 0;
        for (auto& wp : w->weapons) {
            if (wp->type == WeaponType::sword) { d = wp->config.damage; break; }
        }
        return d;
    };
    for (int i = 0; i <= N + 1; i ++) {
        warrior* r = cities[i].red_warrior;
        warrior* b = cities[i].blue_warrior;
        if (r == nullptr || b == nullptr) {continue;}
        bool f = false;
        int r_sword = sword_damage(r);
        int b_sword = sword_damage(b);
        bool red_first = (cities[i].beg_war() == "red");

        int dmg_r_to_b = r->config.damage + r_sword;
        int dmg_b_to_r = b->config.damage + b_sword;
        int fb_r_to_b = (r->type == WarriorType::ninja ? 0 : r->config.damage / 2 + r_sword);
        int fb_b_to_r = (b->type == WarriorType::ninja ? 0 : b->config.damage / 2 + b_sword);

        bool red_will_die = false;
        bool blue_will_die = false;
        if (red_first) {
            if (b->config.life > dmg_r_to_b) {
                red_will_die = (r->config.life <= fb_b_to_r);
            }
            blue_will_die = (b->config.life <= dmg_r_to_b);
        } else {
            if (r->config.life > dmg_b_to_r) {
                blue_will_die = (b->config.life <= fb_r_to_b);
            }
            red_will_die = (r->config.life <= dmg_b_to_r);
        }

        if (r != nullptr && !r->weapons.empty()) {
            for (auto& weapon: r->weapons) {
            if (weapon->type == WeaponType::bomb) {
                if (red_will_die && !blue_will_die) {
                    weapon->attack(r, b);
                    printf("%03d:%02d red %s %d used a bomb and killed blue %s %d\n", hour, min, r->config.name.c_str(), r->config.mark, b->config.name.c_str(), b->config.mark);
                    f = true;
                    break;
                }
                break;
            }
        }
        }
        if (b != nullptr && !b->weapons.empty()) {
            for (auto& weapon: b->weapons) {
            if (weapon->type == WeaponType::bomb) {
                if (blue_will_die && !red_will_die) {
                    weapon->attack(b, r);
                    printf("%03d:%02d blue %s %d used a bomb and killed red %s %d\n", hour, min, b->config.name.c_str(), b->config.mark, r->config.name.c_str(), r->config.mark);
                    f = true;
                    break;
                }
                break;
            }
        }
        }
        if (f) {
            cities[i].red_warrior = nullptr;
            cities[i].blue_warrior = nullptr;
        } 
    }
}

void GameEngine::after_win(warrior* winner, warrior* loser, bool beg, int i) {
    winner->win(loser);
    loser->lose();
    if (winner->type == WarriorType::dragon && beg && winner->courage > 0.8) {
        printf("%03d:%02d %s dragon %d yelled in city %d\n", hour, min, winner->config.belong->name.c_str(), winner->config.mark, i);
    }
    if (loser->type == WarriorType::lion) {
        winner->config.life += loser->config.life_pre;
    }
    printf("%03d:%02d %s %s %d earned %d elements for his headquarter\n", hour, min, winner->config.belong->name.c_str(), winner->config.name.c_str(), winner->config.mark, cities[i].life);
    int tmp = (winner->config.belong->name == "red"? 1:-1);
    if (cities[i].win_log == tmp && cities[i].flag != tmp) {
        cities[i].flag = tmp;
        printf("%03d:%02d %s flag raised in city %d\n", hour, min, tmp == 1?"red":"blue", i);
    }
    else {cities[i].win_log = tmp;}
}

void GameEngine::war() {
    for (int i = 1; i <= N; i ++) {
        warrior* r = cities[i].red_warrior;
        warrior* b = cities[i].blue_warrior;
        if (r == nullptr || b == nullptr) {continue;}
        r->config.life_pre = r->config.life;
        b->config.life_pre = b->config.life;
        string beg = cities[i].beg_war();
        if (r->config.alive == false) {
            after_win(b, r, (beg == "blue"), i);
            continue;
        }
        if (b->config.alive == false) {
            after_win(r, b, (beg == "red"), i);
            continue;
        }
        if (beg == "red") {
            weapon* r_sword = nullptr;
            for (auto& w:r->weapons) if (w->type == WeaponType::sword) { r_sword = w.get(); break; }
            printf("%03d:%02d red %s %d attacked blue %s %d in city %d with %d elements and force %d\n", hour, min, r->config.name.c_str(), r->config.mark, b->config.name.c_str(), b->config.mark, i, r->config.life, r->config.damage);
            if (r_sword != nullptr) r->fire(b, r_sword);
            else b->hurt(r->config.damage);
            if (b->config.alive == false) {
                printf("%03d:%02d blue %s was killed in city %d\n", hour, min, b->config.name.c_str(), i);
                after_win(r, b, true, i);
            }
            else {
                weapon* b_sword = nullptr;
                for (auto& w:b->weapons) if (w->type == WeaponType::sword) { b_sword = w.get(); break; }
                printf("%03d:%02d blue %s %d fought back against red %s %d in city %d\n", hour, min, b->config.name.c_str(), b->config.mark, r->config.name.c_str(), r->config.mark, i);
                if (b_sword != nullptr) b->feedback(r, b_sword);
                else r->hurt(b->config.damage / 2);
                if (r->config.alive == false) {
                    printf("%03d:%02d red %s was killed in city %d\n", hour, min, r->config.name.c_str(), i);
                    after_win(b, r, false, i);
                }
                else {
                    r->lose();b->lose();
                    cities[i].win_log = 0;
                }
            }
        }
        else if (beg == "blue") {
            weapon* b_sword = nullptr;
            for (auto& w:b->weapons) if (w->type == WeaponType::sword) { b_sword = w.get(); break; }
            printf("%03d:%02d blue %s %d attacked red %s %d in city %d with %d elements and force %d\n", hour, min, b->config.name.c_str(), b->config.mark, r->config.name.c_str(), r->config.mark, i, b->config.life, b->config.damage);
            if (b_sword != nullptr) b->fire(r, b_sword);
            else r->hurt(b->config.damage);
            if (r->config.alive == false) {
                printf("%03d:%02d red %s was killed in city %d\n", hour, min, r->config.name.c_str(), i);
                after_win(b, r, true, i);
            }
            else {
                weapon* r_sword = nullptr;
                for (auto& w:r->weapons) if (w->type == WeaponType::sword) { r_sword = w.get(); break; }
                printf("%03d:%02d red %s %d fought back against blue %s %d in city %d\n", hour, min, r->config.name.c_str(), r->config.mark, b->config.name.c_str(), b->config.mark, i);
                if (r_sword != nullptr) r->feedback(b, r_sword);
                else b->hurt(r->config.damage / 2);
                if (b->config.alive == false) {
                    printf("%03d:%02d blue %s was killed in city %d\n", hour, min, b->config.name.c_str(), i);
                    after_win(r, b, false, i);
                }
                else {
                    r->lose();b->lose();
                    cities[i].win_log = 0;
                }
            }
        }
    }
    vector<int> red_win_city;
    vector<int> blue_win_city;
    for (int i = 1;i <= N; i ++) {
        warrior* r = cities[i].red_warrior;
        if (r != nullptr && r->config.alive == false) {
            cities[i].red_warrior = nullptr;
            continue;
        }
        if (r != nullptr && r->config.win) {
            red_win_city.push_back(i);
        }
    }
    for (int i = N; i >= 1; i --) {
        warrior* b = cities[i].blue_warrior;
        if (b != nullptr && b->config.alive == false) {
            cities[i].blue_warrior = nullptr;
            continue;
        }
        if (b != nullptr && b->config.win) {
            blue_win_city.push_back(i);
        }
    }
    for (int i = N; i >= 1; --i) {
        warrior* r = cities[i].red_warrior;
        if (r != nullptr && r->config.win && red.totallife >= 8) {
            r->config.life += 8;
            red.totallife -= 8;
        }
    }
    for (int i = 1; i <= N; ++i) {
        warrior* b = cities[i].blue_warrior;
        if (b != nullptr && b->config.win && blue.totallife >= 8) {
            b->config.life += 8;
            blue.totallife -= 8;
        }
    }
    int r_life = 0, b_life = 0;
    for (int i: red_win_city) { r_life += cities[i].life; cities[i].life = 0; }
    for (int i: blue_win_city) { b_life += cities[i].life; cities[i].life = 0; }
    red.totallife += r_life;
    blue.totallife += b_life;
}

void GameEngine::headquarters_report() {
    printf("%03d:%02d %d elements in red headquarter\n", hour, min, red.totallife);
    printf("%03d:%02d %d elements in blue headquarter\n", hour, min, blue.totallife);
}

void GameEngine::warriors_report() {
    for (int i = 0; i <= N + 1; i++) {
        if (cities[i].red_warrior != nullptr) {
            cities[i].red_warrior->report(hour, min);
        }
        if (cities[i].blue_warrior != nullptr) {
            cities[i].blue_warrior->report(hour, min);
        }
    }
}

int main() {
    int t{0};
    cin >> t;
    for (int c = 1 ;c <= t; c++) {
        printf("Case %d:\n", c);
        red.reset();blue.reset();cities.clear();
        int M, T;
        cin >> M >> N >> R >> K >> T;
        cities.push_back(city(0));
        for (int j = 1; j <= N; j++) {
            cities.push_back(city(j));
        }
        cities.push_back(city(N + 1));
        red.totallife = M; blue.totallife = M;
        red.location = 0;blue.location = N + 1;
        for (int i = 0, l; i < 5; i++) {
            cin >> l;
            configs[i].life = l;
        };
        for (int i = 0, d; i < 5; i++) {
            cin >> d;
            configs[i].damage = d;
        };
        GameEngine engine;
        engine.loop(T);
    }
    getchar();
    return 0;
}
