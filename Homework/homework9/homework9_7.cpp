# include <iostream>
# include <queue>
# include <stack>

using namespace std;

bool isprime(int n) {
    if (n == 1) {return false;}
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {return false;}
    }
    return true;
}

int count(int n) {
    int a = 0;
    for (int i = 1;i * i <= n; i++) {
        if (n % i == 0) {
            if(isprime(i)) {a ++;}
            if (isprime(n / i)) {a ++;}
        }
    }
    return a;
}

class cmp {
    public:
    bool operator() (int x, int y) {
        int x_n = count(x);
        int y_n = count(y);
        if (x_n != y_n) {
            return x_n < y_n;
        }
        return x < y;
    }
};

priority_queue<int, vector<int>, cmp> p_m;

int main() {
    int num;
    cin >> num;
    for (int i = 0; i < 10 * num; i++) {
        int n;
        cin >> n;
        p_m.push(n);
        if (i % 10 == 9) {
            int maxx = p_m.top();
            p_m.pop();
            cout << maxx << ' ';
            stack<int> help;
            while (!p_m.empty()) {
                help.push(p_m.top());
                p_m.pop();
            }
            cout << help.top() << endl;
            help.pop();
            while (!help.empty()) {
                p_m.push(help.top());
                help.pop();
            }
        }
    }
}