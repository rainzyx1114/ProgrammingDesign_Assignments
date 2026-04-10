# include <iostream>
# include <cstring>
# include <vector>
# include <sstream>

using namespace std;

vector<string> strs;

int com_to_int(int& idx, vector<string>& coms);

string com_to_str(int& idx, vector<string>& coms) {
    string com = coms[idx];
    idx ++;
    if (com == "copy") {
        int N = com_to_int(idx, coms);
        int X = com_to_int(idx, coms);
        int L = com_to_int(idx, coms);
        return strs[N].substr(X, L);
    }
    else if (com == "add") {
        string s1 = com_to_str(idx, coms);
        string s2 = com_to_str(idx, coms);
        char* end;
        long long n1 = strtod(s1.c_str(), &end);
        if (*end != '\0' || n1 < 0 || n1 > 99999) {return s1 + s2;}
        long long n2 = strtod(s2.c_str(), &end);
        if (*end != '\0' || n1 < 0 || n2 > 99999) {return s1 + s2;}
        return to_string(n1 + n2);
    }
    return com;
}

int com_to_int(int& idx, vector<string>& coms) {
    string com = coms[idx];
    idx ++;
    if (com == "find") {
        string s = com_to_str(idx, coms);
        int N = com_to_int(idx, coms);
        if (strs[N].find(s) != strs[N].npos) {
            return strs[N].find(s);
        }
        else {
            return strs[N].size();
        }
    }
    else if (com == "rfind") {
        string s = com_to_str(idx, coms);
        int N = com_to_int(idx, coms);
        if (strs[N].rfind(s) != strs[N].npos) {
            return strs[N].rfind(s);
        }
        else {
            return strs[N].size();
        }
    }
    return stoi(com);
}

bool com_to_do(int& idx, vector<string>& coms) {
    string com = coms[idx];
    idx ++;
    if (com == "insert") {
        string s = com_to_str(idx, coms);
        int N = com_to_int(idx, coms);
        int X = com_to_int(idx, coms);
        strs[N].insert(X, s);
        return true;
    }
    else if (com == "reset") {
        string s = com_to_str(idx, coms);
        int N = com_to_int(idx, coms);
        strs[N] = s;
        return true;
    }
    else if (com == "print") {
        int N = com_to_int(idx, coms);
        cout << strs[N] << endl;
        return true;
    }
    else if (com == "printall") {
        for (int i = 1; i < strs.size(); i ++) {
            cout << strs[i] << endl;
        }
        return true;
    }
    return false;
}

vector<string> tokens;

int main() {
    int n;
    cin >> n;
    strs.resize(n + 1);
    for (int i = 1; i <= n; i ++) {
        cin >> strs[i];
    }
    string help;
    getline(cin, help);
    bool flag = true;
    while(flag) {
        tokens.clear();
        getline(cin, help);
        stringstream ss(help);
        string token;
        while(ss >> token) {
            tokens.push_back(token);
        }
        int idx = 0;
        flag = com_to_do(idx, tokens);
    }
}