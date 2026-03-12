#include <iostream>
#include <cstdio>
#include <vector>
#include <array>
#include <cstring>

using namespace std;

struct warrior {
    protected:
        int mark;
        int life;
        string warrior_name;
    public:
        warrior(int m, int l, string n):mark(m), life(l), warrior_name(n){}
        warrior() = default;
        warrior(string n):warrior_name(n){}
        int get_life() const{return life;}
        void set_life(int l) {life = l;}
        string get_warrior_name() const{return warrior_name;}
};

class headquarter {
    int totallife{0};
    int loopcount{0};
    int total_warrior{0};
    string name;
    array <warrior*, 5> loops;
    vector<warrior> dragons;
    vector<warrior> ninjas;
    vector<warrior> icemans;
    vector<warrior> lions;
    vector<warrior> wolfs;

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
                                icemans.push_back(warrior(total_warrior, loops[index]->get_life(), loops[index]->get_warrior_name()));
                                m = icemans.size();
                                break;
                            case 1:
                                lions.push_back(warrior(total_warrior, loops[index]->get_life(), loops[index]->get_warrior_name()));
                                m = lions.size();
                                break;
                            case 2:
                                wolfs.push_back(warrior(total_warrior, loops[index]->get_life(), loops[index]->get_warrior_name()));
                                m = wolfs.size();
                                break;
                            case 3:
                                ninjas.push_back(warrior(total_warrior, loops[index]->get_life(), loops[index]->get_warrior_name()));
                                m = ninjas.size();
                                break;
                            case 4:
                                dragons.push_back(warrior(total_warrior, loops[index]->get_life(), loops[index]->get_warrior_name()));
                                m = dragons.size();
                                break;
                        }
                    }
                    else if (name == "blue") {
                        switch(index) {
                            case 0:
                                lions.push_back(warrior(total_warrior, loops[index]->get_life(), loops[index]->get_warrior_name()));
                                m = lions.size();
                                break;
                            case 1:
                                dragons.push_back(warrior(total_warrior, loops[index]->get_life(), loops[index]->get_warrior_name()));
                                m = dragons.size();
                                break;
                            case 2:
                                ninjas.push_back(warrior(total_warrior, loops[index]->get_life(), loops[index]->get_warrior_name()));
                                m = ninjas.size();
                                break;
                            case 3:
                                icemans.push_back(warrior(total_warrior, loops[index]->get_life(), loops[index]->get_warrior_name()));
                                m = icemans.size();
                                break;
                            case 4:
                                wolfs.push_back(warrior(total_warrior, loops[index]->get_life(), loops[index]->get_warrior_name()));
                                m = wolfs.size();
                                break;
                        }
                    }
                    printf("%03d %s %s %d born with strength %d,%d %s in %s headquarter\n", tim, name.c_str(), loops[index]->get_warrior_name().c_str(), total_warrior, loops[index]->get_life(), m, loops[index]->get_warrior_name().c_str(), name.c_str());
                    loopcount = index + 1;
                    return true;
                }
            }
            printf("%03d %s headquarter stops making warriors\n", tim, name.c_str());
            return false;
        }
};

warrior* iceman = new warrior("iceman");
warrior* lion = new warrior("lion");
warrior* wolf = new warrior("wolf");
warrior* ninja = new warrior("ninja");
warrior* dragon = new warrior("dragon");

headquarter red("red", {iceman, lion, wolf, ninja, dragon});
headquarter blue("blue", {lion, dragon, ninja, iceman, wolf});
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
                case 0:dragon->set_life(l);break;
                case 1:ninja->set_life(l);break;
                case 2:iceman->set_life(l);break;
                case 3:lion->set_life(l);break;
                case 4:wolf->set_life(l);break;
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
    delete iceman;delete lion;delete wolf;delete ninja;delete dragon;
    return 0;
}