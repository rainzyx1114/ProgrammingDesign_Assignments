#include <iostream>
#include <cstdio>
#include <vector>
#include <array>
#include <cstring>
#include <algorithm>
#include <stdlib.h>
#include <stack>

using namespace std;

class warrior;
class city {
        public:
            int location;
            warrior* red_warrior{nullptr};
            warrior* blue_warrior{nullptr};
            city(int l): location(l) {}
            void war(int hour, int min);
};

vector<city> cities;
int N;

struct weapon {
    string name;
    int use{0};
    int mark;
    weapon(const char* s, int m): name(s), use(0), mark(m){}
    virtual void attack(warrior* attacker, warrior* opponent) {}
    virtual bool is_use() {return true;}
    virtual ~weapon() = default;
};

string w[3] = {"sword", "bomb", "arrow"};

class warrior {
    protected:
        int life;
        string warrior_name;
        int damage;    
        int location;
        
    public:
        vector<weapon*> weapons;
        int mark;
        char belong;
        bool alive{true};

        warrior(int m, int l, string n, int d):mark(m), life(l), warrior_name(n), damage(d){}
        warrior() = default;
        warrior(string n):warrior_name(n){}
        virtual ~warrior(){
            for (auto w : weapons) {
                if (w != nullptr) {
                    delete w;
                } 
            }
            // cout << "I'm here" << endl;
            weapons.clear();
        }
        int get_life() const{return life;}
        int get_damage() const{return damage;}
        int get_location() const{return location;}
        string get_warrior_name() const{return warrior_name;}
        void set_life(int l) {life = l;}
        void set_damage(int d) {damage = d;}
        void set_location(int l) {location = l;}
        void belong_to(char b) {belong = b;}
        virtual void rob(int hour, int min, warrior* opponent) {}
        virtual void fire(warrior* opponent, weapon* w) {}
        virtual void hurt(int d) {
            life -= d;
            if (life <= 0){alive = false;life = 0;}
        }
        virtual void move(int k) {
            if (belong == 'r') {
                if (location == N + 1) return;
                cities[location].red_warrior = nullptr;
                location ++;
                cities[location].red_warrior = this;
                
            }
            else if (belong == 'b') {
                if (location == 0) return;
                cities[location].blue_warrior = nullptr;
                location --;
                cities[location].blue_warrior = this;
            }
        }
        void report(int hour, int min) {
            if (!alive) {return;}
            int sw{0}, bom(0), arr(0);
            for (const auto& w: weapons) {
                if (w != nullptr && w->is_use()) {
                    if (w->mark == 0) {sw++;}
                    else if (w->mark == 1) {bom++;}
                    else if (w->mark == 2) {arr++;}
                }
            }
            printf("%03d:%02d %s %s %d has %d sword %d bomb %d arrow and %d elements\n", hour, min, belong == 'r'? "red":"blue", warrior_name.c_str(), mark, sw, bom, arr, life);
        }
        bool cmp1(weapon* w1, weapon* w2) {
            if (w1 != nullptr && w2 == nullptr) {return true;}
            else if (w1 == nullptr && w2 != nullptr) {return false;}
            else if (w1 == nullptr && w2 == nullptr) {return false;}
            if (w1->mark != w2->mark) {
                return w1->mark < w2->mark;
            }
            else {
                if (w1->name == "arrow") {
                    return w1->use > w2->use;
                }
            }
            return false;
        };
        bool cmp2(weapon* w1, weapon* w2) {
            if (w1 != nullptr && w2 == nullptr) {return true;}
            else if (w1 == nullptr && w2 != nullptr) {return false;}
            else if (w1 == nullptr && w2 == nullptr) {return false;}
            if (w1->mark != w2->mark) {
                return w1->mark < w2->mark;
            }
            else {
                if (w1->name == "arrow") {
                    return w1->use < w2->use;
                }
            }
            return false;
        }
        void set_weapons1() {
            sort(weapons.begin(), weapons.end(), [this](weapon* a, weapon*b){return this->cmp1(a, b);});
            auto it = remove_if(weapons.begin(), weapons.end(), [](weapon* w) {
                if (w == nullptr){return true;}
                else if (!w->is_use()) {
                    delete w;
                    return true;
                }
                else{return false;}
            });
            weapons.erase(it, weapons.end());
        }
        void set_weapons2() {
            sort(weapons.begin(), weapons.end(), [this](weapon* a, weapon*b){return this->cmp2(a, b);});
            auto it = remove_if(weapons.begin(), weapons.end(), [](weapon* w) {
                if (w == nullptr){return true;}
                else if (!w->is_use()) {
                    delete w;
                    return true;
                }
                else{return false;}
            });
            weapons.erase(it, weapons.end());
        }
        virtual int get_loyalty()const{return 1000;};
};

warrior* ice = new warrior("iceman");
warrior* lio = new warrior("lion");
warrior* wol = new warrior("wolf");
warrior* nin = new warrior("ninja");
warrior* dra = new warrior("dragon");

class sword:public weapon {
    public:
        sword():weapon("sword", 0) {}
        void attack(warrior* attacker, warrior* opponent) {
            opponent->hurt(attacker->get_damage() / 5);
        }
        bool is_use() {return true;}
};

class bomb:public weapon {
    public:
        bomb():weapon("bomb", 1) {}
        void attack(warrior* attacker, warrior* opponent) {
            // cout << "bomb attack" << endl;
            int d = attacker->get_damage() * 2 / 5;
            opponent->hurt(d);
            if (attacker->get_warrior_name() != "ninja"){attacker->hurt(d / 2);}
            use = 1;
        }
        bool is_use() {return use != 1;}
};

class arrow:public weapon {
    public:
        arrow():weapon("arrow", 2) {}
        void attack(warrior* attacker, warrior* opponent) {
            opponent->hurt(attacker->get_damage() * 3 / 10);
            use ++;
        }
        bool is_use() {return use <= 1;}
};

class dragon: public warrior {
        double courage;
    public:
        dragon(int m, int l, string n, int lef, int d):warrior::warrior(m, l, n, d), courage(static_cast<double>(lef) / l){
            string s = w[m % 3];
            if (s == "sword") {
                weapons.push_back(new sword());
            }
            else if(s == "bomb") {
                weapons.push_back(new bomb());
            }
            else if(s == "arrow") {
                weapons.push_back(new arrow());
            }
        }
        double get_courage() const{return courage;};
        void fire(warrior* opponent, weapon* w) {
            w->attack(this, opponent);
        }
};

class ninja: public warrior {
    public:
        ninja(int m, int l, string n, int d):warrior::warrior(m, l, n, d) {
            string s1 = w[m % 3];
            if (s1 == "sword") {
                weapons.push_back(new sword());
            }
            else if(s1 == "bomb") {
                weapons.push_back(new bomb());
            }
            else if(s1 == "arrow") {
                weapons.push_back(new arrow());
            }
            string s2 = w[(m + 1) % 3];
            if (s2 == "sword") {
                weapons.push_back(new sword());
            }
            else if(s2 == "bomb") {
                weapons.push_back(new bomb());
            }
            else if(s2 == "arrow") {
                weapons.push_back(new arrow());
            }
        }
        void fire(warrior* opponent, weapon* w) {
            w->attack(this, opponent);
        }
};

class iceman: public warrior {
    public:
        iceman(int m, int l, string n, int d):warrior::warrior(m, l, n, d) {
            string s = w[m % 3];
            if (s == string("sword")) {
                weapons.push_back(new sword());
            }
            else if(s == string("bomb")) {
                weapons.push_back(new bomb());
            }
            else if(s == string("arrow")) {
                weapons.push_back(new arrow());
            }
        }
        void fire(warrior* opponent, weapon* w) {
            w->attack(this, opponent);
        }
        void move( int k) {
            life -= life / 10;
            warrior::move(k);
        }
};

class lion: public warrior {
    int loyalty;
    public:
        lion(int m, int l, string n, int lef, int d):warrior::warrior(m, l, n, d), loyalty(lef) {
            string s = w[m % 3];
            if (s == "sword") {
                weapons.push_back(new sword());
            }
            else if(s == "bomb") {
                weapons.push_back(new bomb());
            }
            else if(s == "arrow") {
                weapons.push_back(new arrow());
            }
        }
        int get_loyalty()const{return loyalty;}
        void fire(warrior* opponent, weapon* w) {
            w->attack(this, opponent);
        }
        void move(int k) {
            loyalty -= k;
            warrior::move(k);
        }
};

class wolf: public warrior {
    public:
        using warrior::warrior;
        void fire(warrior* opponent, weapon* w) {
            w->attack(this, opponent);
        }
        void rob(int hour, int min, warrior* opponent) {
            if (opponent->get_warrior_name() == "wolf") return;
            else if(!opponent->weapons.empty() && opponent->weapons[0] != nullptr){
                if (opponent->weapons[0]->mark == 0) {
                    int count = 0;
                    for (int i = 0; i < opponent->weapons.size() && weapons.size() < 10; i ++) {
                        weapon* w = opponent->weapons[i];
                        if (w == nullptr || w->name != "sword") {break;}
                        else {
                            count ++;
                            weapons.push_back(w);
                            opponent->weapons[i] = nullptr;
                        }
                    }
                    printf("%03d:%02d %s %s %d took %d sword from %s %s %d in city %d\n", hour, min, belong == 'r'? "red":"blue", warrior_name.c_str(), mark, count, belong=='r'? "blue":"red", opponent->get_warrior_name().c_str(), opponent->mark, location);
                }
                else if(opponent->weapons[0]->mark == 1) {
                    int count = 0;
                    for (int i = 0; i < opponent->weapons.size() && weapons.size() < 10; i ++) {
                        weapon* w = opponent->weapons[i];
                        if (w == nullptr || w->name != "bomb") {break;}
                        else {
                            count ++;
                            weapons.push_back(w);
                            opponent->weapons[i] = nullptr;
                        }
                    }
                    printf("%03d:%02d %s %s %d took %d bomb from %s %s %d in city %d\n", hour, min, belong == 'r'? "red":"blue", warrior_name.c_str(), mark, count, belong=='r'? "blue":"red", opponent->get_warrior_name().c_str(), opponent->mark, location);
                }
                else if(opponent->weapons[0]->mark == 2) {
                    int count = 0;
                    for (int i = 0; i < opponent->weapons.size() && weapons.size() < 10; i ++) {
                        weapon* w = opponent->weapons[i];
                        if (w == nullptr || w->name != "arrow") {break;}
                        else {
                            count ++;
                            weapons.push_back(w);
                            opponent->weapons[i] = nullptr;
                        }
                    }
                    printf("%03d:%02d %s %s %d took %d arrow from %s %s %d in city %d\n", hour, min, belong == 'r'? "red":"blue", warrior_name.c_str(), mark, count, belong=='r'? "blue":"red", opponent->get_warrior_name().c_str(), opponent->mark, location);
                }
            }
            return;
        }
};

class headquarter {
    int totallife{0};
    int loopcount{0};
    int total_warrior{0};
    string name;
    array <warrior*, 5> loops;
    vector<dragon*> dragons;
    vector<ninja*> ninjas;
    vector<iceman*> icemans;
    vector<lion*> lions;
    vector<wolf*> wolfs;

    public:
        int location;
        headquarter(string n, const array<warrior*, 5>& loop):name(n), loops(loop){}

        void set_totallife(int l) {totallife = l;};
        int get_totallife() const{return totallife;};
        void reset(){
            loopcount = 0;
            total_warrior = 0;
            for(auto d: dragons) {delete d;}
            for(auto n: ninjas) {delete n;}
            for(auto i: icemans) {delete i;}
            for(auto l: lions) {delete l;}
            for(auto w: wolfs) {delete w;}
            dragons.clear();
            ninjas.clear();
            icemans.clear();
            lions.clear();
            wolfs.clear();
        };
        string get_name() const{return name;}
        int get_op_location() {return (N + 1 - location);}
        bool produce(int hour, int min) {
            if (totallife < loops[loopcount]->get_life()) {
                return false;
            }
            else {
                printf("%03d:%02d ", hour, min);
                totallife -= loops[loopcount]->get_life();
                total_warrior ++;
                if (name == "red") {
                    switch(loopcount) {
                        case 0:
                            icemans.push_back(new iceman(total_warrior, loops[loopcount]->get_life(), loops[loopcount]->get_warrior_name(), loops[loopcount]->get_damage()));
                            icemans.back()->belong_to('r');icemans.back()->set_location(0);
                            cities[0].red_warrior = icemans.back();
                            printf("red iceman %d born\n", total_warrior);
                            break;
                        case 1:
                            lions.push_back(new lion(total_warrior, loops[loopcount]->get_life(), loops[loopcount]->get_warrior_name(), totallife, loops[loopcount]->get_damage()));
                            lions.back()->belong_to('r');
                            cities[0].red_warrior = lions.back();lions.back()->set_location(0);
                            printf("red lion %d born\n", total_warrior);
                            printf("Its loyalty is %d\n", lions.back()->get_loyalty());
                            break;
                        case 2:
                            wolfs.push_back(new wolf(total_warrior, loops[loopcount]->get_life(), loops[loopcount]->get_warrior_name(), loops[loopcount]->get_damage()));
                            cities[0].red_warrior = wolfs.back();wolfs.back()->set_location(0);
                            wolfs.back()->belong_to('r');
                            printf("red wolf %d born\n", total_warrior);
                            break;
                        case 3:
                            ninjas.push_back(new ninja(total_warrior, loops[loopcount]->get_life(), loops[loopcount]->get_warrior_name(), loops[loopcount]->get_damage()));
                            cities[0].red_warrior = ninjas.back();ninjas.back()->set_location(0);
                            ninjas.back()->belong_to('r');
                            printf("red ninja %d born\n", total_warrior);
                            break;
                        case 4:
                            dragons.push_back(new dragon(total_warrior, loops[loopcount]->get_life(), loops[loopcount]->get_warrior_name(), totallife, loops[loopcount]->get_damage()));
                            cities[0].red_warrior = dragons.back();dragons.back()->set_location(0);
                            dragons.back()->belong_to('r');
                            printf("red dragon %d born\n", total_warrior);
                            break;
                        }
                    }
                else if (name == "blue") {
                    switch(loopcount) {
                            case 0:
                                lions.push_back(new lion(total_warrior, loops[loopcount]->get_life(), loops[loopcount]->get_warrior_name(), totallife, loops[loopcount]->get_damage()));
                                cities[N + 1].blue_warrior = lions.back();lions.back()->set_location(N + 1);
                                lions.back()->belong_to('b');
                                printf("blue lion %d born\n", total_warrior);
                                printf("Its loyalty is %d\n", lions.back()->get_loyalty());
                                break;
                            case 1:
                                dragons.push_back(new dragon(total_warrior, loops[loopcount]->get_life(), loops[loopcount]->get_warrior_name(), totallife, loops[loopcount]->get_damage()));
                                cities[N + 1].blue_warrior = dragons.back();dragons.back()->set_location(N + 1);
                                dragons.back()->belong_to('b');
                                printf("blue dragon %d born\n", total_warrior);
                                break;
                            case 2:
                                ninjas.push_back(new ninja(total_warrior, loops[loopcount]->get_life(), loops[loopcount]->get_warrior_name(), loops[loopcount]->get_damage()));
                                cities[N + 1].blue_warrior = ninjas.back();ninjas.back()->set_location(N + 1);
                                ninjas.back()->belong_to('b');
                                printf("blue ninja %d born\n", total_warrior);
                                break;
                            case 3:
                                icemans.push_back(new iceman(total_warrior, loops[loopcount]->get_life(), loops[loopcount]->get_warrior_name(), loops[loopcount]->get_damage()));
                                cities[N + 1].blue_warrior = icemans.back();icemans.back()->set_location(N + 1);
                                icemans.back()->belong_to('b');
                                printf("blue iceman %d born\n", total_warrior);
                                break;
                            case 4:
                                wolfs.push_back(new wolf(total_warrior, loops[loopcount]->get_life(), loops[loopcount]->get_warrior_name(), loops[loopcount]->get_damage()));
                                cities[N + 1].blue_warrior = wolfs.back();wolfs.back()->set_location(N + 1);
                                wolfs.back()->belong_to('b');
                                printf("blue wolf %d born\n", total_warrior);
                                break;
                        }
                }
                loopcount = (loopcount + 1) % 5;
                return true;
            }
        }
};

headquarter red("red", {ice, lio, wol, nin, dra});
headquarter blue("blue", {lio, dra, nin, ice, wol});

void city::war(int hour, int min) {
    int flag = 0;
    int red_life = red_warrior->get_life();
    int blue_life = blue_warrior->get_life();
    int r_index = 0;
    int b_index = 0;
    int limit = 5000;
    while(limit --) {
        if(red_life > 0 && blue_life <= 0) {flag = 1;break;}
        if(red_life <= 0 && blue_life > 0) {flag = -1;break;}
        if(red_life <= 0 && blue_life <= 0) {flag = -2;break;}
        weapon* r_w = nullptr;
        weapon* b_w = nullptr;
        for (int i = 0; i < red_warrior->weapons.size(); i ++) {
            // cout << "I'm here" << endl;
            if (red_warrior->weapons[r_index] != nullptr && red_warrior->weapons[r_index]->is_use()) {
                r_w = red_warrior->weapons[r_index];
                r_index = (r_index + 1) % (red_warrior->weapons.size());
                break;
            }
            r_index = (r_index + 1) % (red_warrior->weapons.size());
        }
        for (int i = 0; i < blue_warrior->weapons.size(); i ++) {
            if (blue_warrior->weapons[b_index] != nullptr && blue_warrior->weapons[b_index]->is_use()) {
                b_w = blue_warrior->weapons[b_index];
                b_index = (b_index + 1) % blue_warrior->weapons.size();
                break;
            }
            b_index = (b_index + 1) % blue_warrior->weapons.size();
        }
        if (r_w == nullptr && b_w == nullptr) break;
        if(location % 2 != 0) {
            if (r_w != nullptr) {
                red_warrior->fire(blue_warrior, r_w);
                red_life = red_warrior->get_life();
                blue_life = blue_warrior->get_life();
                if (red_life <=0 || blue_life <=0) continue;
            }
            if (b_w != nullptr) {blue_warrior->fire(red_warrior, b_w);}
        }
        else {
            if (b_w != nullptr) {
                blue_warrior->fire(red_warrior, b_w);
                red_life = red_warrior->get_life();
                blue_life = blue_warrior->get_life();
                if (red_life <=0 || blue_life <= 0) continue;
            }
            if (r_w != nullptr) {red_warrior->fire(blue_warrior, r_w);}
        }
        red_life = red_warrior->get_life();
        blue_life = blue_warrior->get_life();
    }
    if (flag == 1) {
        printf("%03d:%02d red %s %d killed blue %s %d in city %d remaining %d elements\n", hour, min, red_warrior->get_warrior_name().c_str(), red_warrior->mark, blue_warrior->get_warrior_name().c_str(), blue_warrior->mark, location, red_life);
        red_warrior->set_weapons2();
        blue_warrior->set_weapons2();
        for (int i = 0; i < blue_warrior->weapons.size() && red_warrior->weapons.size() < 10; i++) {
            weapon* w = blue_warrior->weapons[i];
            if (w == nullptr) {break;}
            red_warrior->weapons.push_back(w);
            blue_warrior->weapons[i] = nullptr;
        }
        blue_warrior->alive = false;
        blue_warrior = nullptr;
    }
    else if (flag == -1) {
        printf("%03d:%02d blue %s %d killed red %s %d in city %d remaining %d elements\n", hour, min, blue_warrior->get_warrior_name().c_str(), blue_warrior->mark, red_warrior->get_warrior_name().c_str(), red_warrior->mark, location, blue_life);
        red_warrior->set_weapons2();
        blue_warrior->set_weapons2();
        for (int i = 0; i < red_warrior->weapons.size() && blue_warrior->weapons.size() < 10; i++) {
            weapon* w = red_warrior->weapons[i];
            if (w == nullptr) {break;}
            blue_warrior->weapons.push_back(w);
            red_warrior->weapons[i] = nullptr;
        }
        red_warrior->alive = false;
        red_warrior = nullptr;
    }
    else if (flag == -2) {
        printf("%03d:%02d both red %s %d and blue %s %d died in city %d\n", hour, min, red_warrior->get_warrior_name().c_str(), red_warrior->mark, blue_warrior->get_warrior_name().c_str(), blue_warrior->mark, location);
        red_warrior->alive = false;blue_warrior->alive = false;
        red_warrior = nullptr;blue_warrior = nullptr;
    }
    else if (flag == 0) {
        printf("%03d:%02d both red %s %d and blue %s %d were alive in city %d\n", hour, min, red_warrior->get_warrior_name().c_str(), red_warrior->mark, blue_warrior->get_warrior_name().c_str(), blue_warrior->mark, location);
        red_warrior->set_weapons1();
        blue_warrior->set_weapons1();
    }
    if (red_warrior != nullptr && red_warrior->get_warrior_name() == "dragon"){
        printf("%03d:%02d red dragon %d yelled in city %d\n", hour, min, red_warrior->mark, location);
    }
    if (blue_warrior != nullptr && blue_warrior->get_warrior_name() == "dragon"){
        printf("%03d:%02d blue dragon %d yelled in city %d\n", hour, min, blue_warrior->mark, location);
    }
}

int main() {
    int t{0};
    cin >> t;
    for (int c = 1 ;c <= t; c++) {
        printf("Case %d:\n", c);
        red.reset();blue.reset();cities.clear();
        int M, K, T;
        cin >> M >> N >> K >> T;
        cities.push_back(city(0));
        for (int j = 1;j <= N; j++) {
            cities.push_back(city(j));
        }
        cities.push_back(city(N + 1));
        red.set_totallife(M);red.location = 0;
        blue.set_totallife(M);blue.location = N + 1;
        for (int i = 0, l; i < 5; i++) {
            cin >> l;
            switch(i) {
                case 0:dra->set_life(l);break;
                case 1:nin->set_life(l);break;
                case 2:ice->set_life(l);break;
                case 3:lio->set_life(l);break;
                case 4:wol->set_life(l);break;
            }
        };
        for (int i = 0, d; i < 5; i++) {
            cin >> d;
            switch(i) {
                case 0:dra->set_damage(d);break;
                case 1:nin->set_damage(d);break;
                case 2:ice->set_damage(d);break;
                case 3:lio->set_damage(d);break;
                case 4:wol->set_damage(d);break;
            }
        };
        bool end = false;
        bool mark_red = true;
        bool mark_blue = true;
        for (int tim = 0, hour, min; tim <= T && !end; tim ++) {
            hour = tim / 60;min = tim % 60;
            if (min == 0 || min == 5 || min == 10 || min == 35 || min == 40 || min == 50 || min ==55) {
                if (min == 0) {
                    if (mark_red) mark_red = red.produce(hour, min);
                    if (mark_blue) mark_blue = blue.produce(hour, min);
                }
                else if (min == 5) {
                    for (int i = 0 ; i <= N + 1; i++) {
                        if (cities[i].red_warrior != nullptr && i <= N && cities[i].red_warrior->get_warrior_name() == "lion") {
                            if (cities[i].red_warrior->get_loyalty() <= 0) {
                                cities[i].red_warrior->alive = false;
                                printf("%03d:%02d ", hour, min);
                                printf("red lion %d ran away\n", cities[i].red_warrior->mark);
                                cities[i].red_warrior = nullptr;
                            }
                        }
                        if (cities[i].blue_warrior != nullptr && i >= 1 && cities[i].blue_warrior->get_warrior_name() == "lion") {
                            if (cities[i].blue_warrior-> get_loyalty() <= 0) {
                                cities[i].blue_warrior->alive = false;
                                printf("%03d:%02d ", hour, min);
                                printf("blue lion %d ran away\n", cities[i].blue_warrior->mark);
                                cities[i].blue_warrior = nullptr;
                            }
                        }
                    }
                }
                else if (min == 10) {
                    for (int i = N ; i >= 0; i --) {
                        if (cities[i].red_warrior != nullptr) {
                            cities[i].red_warrior->move(K);
                        }
                    }
                    for (int i = 1; i <= N + 1; i ++) {
                        if (cities[i].blue_warrior != nullptr) {
                            cities[i].blue_warrior->move(K);
                        }
                    }
                    for (int i = 0; i <= N + 1; i++) {
                        warrior* r = cities[i].red_warrior;
                        warrior* b = cities[i].blue_warrior;
                        if (r != nullptr) {
                            if (i == N + 1) {
                                printf("%03d:%02d ", hour, min);
                                printf("%s %s %d reached blue headquarter with %d elements and force %d\n", "red", r->get_warrior_name().c_str(), r->mark, r->get_life(), r->get_damage());
                                printf("%03d:%02d ", hour, min);
                                printf("blue headquarter was taken\n");
                                end = true;
                            }
                            else {
                                printf("%03d:%02d ", hour, min);
                                printf("%s %s %d marched to city %d with %d elements and force %d\n", "red", r->get_warrior_name().c_str(), r->mark, r->get_location(), r->get_life(), r->get_damage());
                            }
                        }
                        if (b != nullptr) {
                            if (i == 0) {
                                printf("%03d:%02d ", hour, min);
                                printf("%s %s %d reached red headquarter with %d elements and force %d\n", "blue", b->get_warrior_name().c_str(), b->mark, b->get_life(), b->get_damage());
                                printf("%03d:%02d ", hour, min);
                                printf("red headquarter was taken\n");
                                end = true;
                            }
                            else {
                                printf("%03d:%02d ", hour, min);
                                printf("%s %s %d marched to city %d with %d elements and force %d\n", "blue", b->get_warrior_name().c_str(), b->mark, b->get_location(), b->get_life(), b->get_damage());
                            }
                        }
                    }
                    if (end) {break;}
                }
                else if (min == 35) {
                    for (int i = 1; i <= N; i++) {
                        if (cities[i].red_warrior != nullptr && cities[i].blue_warrior != nullptr) {
                            cities[i].red_warrior->set_weapons2();
                            cities[i].blue_warrior->set_weapons2();
                            if (cities[i].red_warrior -> get_warrior_name() == "wolf") {
                                cities[i].red_warrior->rob(hour, min, cities[i].blue_warrior);
                            }
                            else if (cities[i].blue_warrior -> get_warrior_name() == "wolf") {
                                cities[i].blue_warrior->rob(hour, min, cities[i].red_warrior);
                            }
                        }
                    }
                }
                else if (min == 40) {
                    for (int i = 1; i <= N; i++) {
                        if (cities[i].red_warrior != nullptr && cities[i].blue_warrior != nullptr) {
                            cities[i].red_warrior->set_weapons1();
                            cities[i].blue_warrior->set_weapons1();
                            cities[i].war(hour, min);
                        }
                    }
                }
                else if (min == 50) {
                    printf("%03d:%02d %d elements in %s headquarter\n", hour, min, red.get_totallife(), red.get_name().c_str());
                    printf("%03d:%02d %d elements in %s headquarter\n", hour, min, blue.get_totallife(), blue.get_name().c_str());
                }
                else if (min == 55) {
                    for (int i = 0; i <= N + 1; i++) {
                        if (cities[i].red_warrior != nullptr) {
                            cities[i].red_warrior->report(hour, min);
                        }
                        if (cities[i].blue_warrior != nullptr) {
                            cities[i].blue_warrior->report(hour, min);
                        }
                    }
                }
            }
        }
    }
    blue.reset();red.reset();
    delete ice;delete lio;delete wol;delete nin;delete dra;
    return 0;
}