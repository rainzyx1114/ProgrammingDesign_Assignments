# include <iostream>
# include <set>

using namespace std;

set<int> visited;
multiset<int> integer;

int main() {
    int arg_nums;
    cin >> arg_nums;
    for (int i = 0; i < arg_nums; i ++) {
        string com;
        cin >> com;
        int x;
        cin >> x;
        if (com == "add") {
            visited.insert(x);
            integer.insert(x);
            cout << integer.count(x) << endl;
        }
        else if (com == "del") {
            cout << integer.count(x) << endl;
            integer.erase(x);
        }
        else if (com == "ask") {
            cout << (visited.find(x) != visited.end()) << integer.count(x) << endl;
        }
    }
}