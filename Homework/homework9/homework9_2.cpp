# include <iostream>
# include <sstream>
# include <stack>
# include <vector>
# include <algorithm>
# include <cmath>

using namespace std;

stack<double> nums;

vector<double> memo;


int main() {
    int n;
    cin >> n;
    memo.resize(n);
    for (int i = 0; i < n; i ++) {
        scanf("%lf", &memo[i]);
    }
    string s;
    getline(cin, s);
    while (getline(cin, s)) {
        stringstream ss(s);
        string token;
        while(ss >> token) {
            char* end;
            double num = strtod(token.c_str(), &end);
            if (*end == '\0') {nums.push(num);}
            else if (token[0] != '=') {
                char op = token[0];
                double rig = nums.top();nums.pop();
                double lef = nums.top();nums.pop();
                if (op == '^') {
                    nums.push(pow(lef, rig));
                }
                else if (op == '+') {
                    nums.push(lef + rig);
                }
                else if (op == '-') {
                    nums.push(lef - rig);
                }
                else if (op == '/') {
                    nums.push(lef / rig);
                }
                else if (op == '*') {
                    nums.push(lef * rig);
                }
            }
            else if (token[0] == '=') {
                break;
            }
        }
        sort(memo.begin(), memo.end());
        memo[0] = nums.top();
        printf("%e\n", memo[0]);
        nums.pop();
    }
    sort(memo.begin(), memo.end());
    for (int i = 0; i < memo.size(); i ++) {
        if (i % 10 == 0) {cout << endl;}
        else {cout << ' ';}
        printf("%e", memo[i]);
    }
}