#include <iostream>
#include <cstdio>
#include <vector>
#include <array>
#include <cstring>

using namespace std;

struct weapon {
    string name;
    weapon(const char* s): name(s) {};
};
weapon w[3] = {"sword", "bomb", "arrow"};

class warrior {
    protected:
        int mark;
        int life;
        string warrior_name;    
    public:
        vector<weapon> weapons;
        warrior(int m, int l, string n):mark(m), life(l), warrior_name(n){}
        warrior() = default;
        warrior(string n):warrior_name(n){}
        int get_life() const{return life;}
        void set_life(int l) {life = l;}
        string get_warrior_name() const{return warrior_name;}
};

class dragon: public warrior {
        double courage;
    public:
        dragon(int m, int l, string n, int lef):warrior::warrior(m, l, n), courage(static_cast<double>(lef) / l){
            weapons.push_back(w[m % 3]);
        }
        double get_courage() const{return courage;};
};

class ninja: public warrior {
    public:
        ninja(int m, int l, string n):warrior::warrior(m, l, n) {
            weapons.push_back(w[m % 3]);
            weapons.push_back(w[(m + 1) % 3]);
        }
};

class iceman: public warrior {
    public:
        iceman(int m, int l, string n):warrior::warrior(m, l, n) {
            weapons.push_back(w[m % 3]);
        }
};

class lion: public warrior {
    int loyalty;
    public:
        lion(int m, int l, string n, int lef):warrior::warrior(m, l, n), loyalty(lef) {}
        int get_loyalty()const{return loyalty;}
};

class wolf: public warrior {
    public:
        using warrior::warrior;
};
class headquarter {
    static string weapons[3];
    int totallife{0};
    int loopcount{0};
    int total_warrior{0};
    string name;
    array <warrior*, 5> loops;
    vector<dragon> dragons;
    vector<ninja> ninjas;
    vector<iceman> icemans;
    vector<lion> lions;
    vector<wolf> wolfs;

    public:
        void set_totallife(int l) {totallife = l;};
        headquarter(string n, const array<warrior*, 5>& loop):name(n), loops(loop){}
        void reset(){
            loopcount = 0;
            total_warrior = 0;
            dragons.clear();
            ninjas.clear();
            icemans.clear();
            lions.clear();
            wolfs.clear();
        };
        string get_name() const{return name;}
        bool produce(int tim) {
            int index = loopcount % 5;
            for (int i = 0; i < 5; i++) {
                if (totallife < loops[index]->get_life()) {
                    index = (index + 1) % 5;
                }
                else {
                    totallife -= loops[index]->get_life();
                    total_warrior ++;
                    int m;
                    if (name == "red") {
                        switch(index) {
                            case 0:
                                icemans.push_back(iceman(total_warrior, loops[index]->get_life(), loops[index]->get_warrior_name()));
                                m = icemans.size();
                                break;
                            case 1:
                                lions.push_back(lion(total_warrior, loops[index]->get_life(), loops[index]->get_warrior_name(), totallife));
                                m = lions.size();
                                break;
                            case 2:
                                wolfs.push_back(wolf(total_warrior, loops[index]->get_life(), loops[index]->get_warrior_name()));
                                m = wolfs.size();
                                break;
                            case 3:
                                ninjas.push_back(ninja(total_warrior, loops[index]->get_life(), loops[index]->get_warrior_name()));
                                m = ninjas.size();
                                break;
                            case 4:
                                dragons.push_back(dragon(total_warrior, loops[index]->get_life(), loops[index]->get_warrior_name(), totallife));
                                m = dragons.size();
                                break;
                        }
                    }
                    else if (name == "blue") {
                        switch(index) {
                            case 0:
                                lions.push_back(lion(total_warrior, loops[index]->get_life(), loops[index]->get_warrior_name(), totallife));
                                m = lions.size();
                                break;
                            case 1:
                                dragons.push_back(dragon(total_warrior, loops[index]->get_life(), loops[index]->get_warrior_name(), totallife));
                                m = dragons.size();
                                break;
                            case 2:
                                ninjas.push_back(ninja(total_warrior, loops[index]->get_life(), loops[index]->get_warrior_name()));
                                m = ninjas.size();
                                break;
                            case 3:
                                icemans.push_back(iceman(total_warrior, loops[index]->get_life(), loops[index]->get_warrior_name()));
                                m = icemans.size();
                                break;
                            case 4:
                                wolfs.push_back(wolf(total_warrior, loops[index]->get_life(), loops[index]->get_warrior_name()));
                                m = wolfs.size();
                                break;
                        }
                    }
                    printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n", tim, name.c_str(), loops[index]->get_warrior_name().c_str(), total_warrior, loops[index]->get_life(), m, loops[index]->get_warrior_name().c_str(), name.c_str());
                    string who = loops[index]->get_warrior_name();
                    if (who == "dragon") {
                        printf("It has a %s,and it's morale is %.2lf\n", dragons.back().weapons[0].name.c_str(), dragons.back().get_courage());
                    }
                    else if (who == "ninja") {
                        printf("It has a %s and a %s\n", ninjas.back().weapons[0].name.c_str(), ninjas.back().weapons[1].name.c_str());
                    }
                    else if (who == "iceman") {
                        printf("It has a %s\n", icemans.back().weapons[0].name.c_str());
                    }
                    else if (who == "lion") {
                        printf("It's loyalty is %d\n",lions.back().get_loyalty());
                    }
                    loopcount = index + 1;
                    return true;
                }
            }
            printf("%03d %s headquarter stops making warriors\n", tim, name.c_str());
            return false;
        }
};

warrior* ice = new warrior("iceman");
warrior* lio = new warrior("lion");
warrior* wol = new warrior("wolf");
warrior* nin = new warrior("ninja");
warrior* dra = new warrior("dragon");

headquarter red("red", {ice, lio, wol, nin, dra});
headquarter blue("blue", {lio, dra, nin, ice, wol});
int main() {
    int t{0};
    cin >> t;
    for (int i = 1 ;i <= t; i++) {
        printf("Case:%d\n", i);
        red.reset();blue.reset();
        int l{0};
        cin >> l;
        red.set_totallife(l);
        blue.set_totallife(l);
        for (int i = 0; i < 5; i++) {
            cin >> l;
            switch(i) {
                case 0:dra->set_life(l);break;
                case 1:nin->set_life(l);break;
                case 2:ice->set_life(l);break;
                case 3:lio->set_life(l);break;
                case 4:wol->set_life(l);break;
            }
        };
        bool mark_red = true;
        bool mark_blue = true;
        int tim = 0;
        while(mark_red || mark_blue) {
            if (mark_red) {
                mark_red = red.produce(tim);
            }
            if (mark_blue) {
                mark_blue = blue.produce(tim);
            }
            tim ++;
        }
    }
    delete ice;delete lio;delete wol;delete nin;delete dra;
    return 0;
}