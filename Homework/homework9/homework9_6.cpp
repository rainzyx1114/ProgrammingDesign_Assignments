# include <set>
# include <iostream>

using namespace std;

struct member {
    int id;
    long long f;
    friend bool operator< (member x, member y) {
        if (x.f != y.f) {return x.f < y.f;}
        else {
            return x.id < y.id;
        }
    }
};

set<member> members;

int main() {
    int n;
    cin >> n;
    member facer = {1, 1000000000};
    members.insert(facer);
    for (int i = 1; i <= n; i ++) {
        member nm;
        cin >> nm.id >> nm.f;
        auto s = members.lower_bound(nm);
        if (s == members.begin()) {
            cout << nm.id << ' ' << s->id << endl;
        }
        else {
            s --;
            while (s != members.begin()) {
                auto it = s;
                it --;
                if (it->f < s->f) {
                    break;
                }
                s --;
            }
            auto b = members.upper_bound(nm);
            if (b == members.end()) {
                cout << nm.id << ' ' << s->id << endl;
            }
            else {
                if (abs(b->f - nm.f) < abs(s->f - nm.f)) {
                    cout << nm.id << ' ' << b->id << endl;
                }
                else if (abs(b->f - nm.f) > abs(s->f - nm.f)) {
                    cout << nm.id << ' ' << s->id << endl;
                }
                else {
                    cout << nm.id << ' ' << (b->id < s->id? b->id : s->id) << endl;
                }
            }
        }
        members.insert(nm);
    }
}