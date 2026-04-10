# include <iostream>
# include <list>
# include <map>

using namespace std;

map<int, list<int>> ls;

int main() {
    int arg_num;
    cin >> arg_num;
    for (int i = 0; i < arg_num; i ++) {
        string com;
        cin >> com;
        if (com == "new") {
            list<int> l;
            int id;
            cin >> id;
            ls[id] = l;
        }
        else if (com == "add") {
            int id, num;
            cin >> id >> num;
            ls[id].push_back(num);
        }
        else if (com == "out") {
            int id;
            cin >> id;
            ls[id].sort();
            for (auto it = ls[id].begin(); it != ls[id].end(); it ++) {
                if (it != ls[id].begin()) {cout << ' ';}
                cout << (*it);
            }
            cout << endl;
        }
        else if (com == "merge") {
            int id1, id2;
            cin >> id1 >> id2;
            if (id1 == id2) {continue;}
            list<int> & l1 = ls[id1];
            list<int> & l2 = ls[id2];
            l1.sort();
            l2.sort();
            l1.merge(l2);
        }
        else if (com == "unique") {
            int id;
            cin >> id;
            ls[id].sort();
            ls[id].unique();
        }
    }
}