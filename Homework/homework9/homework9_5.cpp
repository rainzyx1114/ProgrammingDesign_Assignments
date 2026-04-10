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
        if (s != members.begin()) {s--;}
        auto b = members.upper_bound(nm);
        if (b != members.end() && abs(b->f - nm.f) < abs(s->f - nm.f)) {
            cout << nm.id << ' ' << b->id << endl;
        }
        else {
            cout << nm.id << ' ' << s->id << endl;
        }
        members.insert(nm);
    }
}