#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <cstdlib>
using namespace std;

class Student {
// 在此处补充你的代码
string m_name;
int m_age;
int m_number;
int score[4];
double m_average;
public:
    void input() {
        string s,n{""};
        getline(cin,s);
        int flag{0};
        for(int i = 0 ;i < s.size(); i++) {
            if(s[i] == ',') {
                flag ++;
                if(flag == 1) {
                    m_name = n;
                }
                else if(flag == 2) {
                    m_age = stoi(n);
                }
                else if(flag == 3) {
                    m_number = stoi(n);
                }
                else if(flag >=4) {
                    score[flag - 4] = stoi(n);
                }
                n = "";
                continue;
            }
            n.append(1,s[i]);
            if(i == s.size() - 1) {
                score[3] = stoi(n);
            }
        }
    }
    void calculate() {
        m_average = (score[0] + score[1] + score[2] + score[3]) / 4.0;
    }
    void output() {
        cout << m_name << ',' << m_age << ',' << m_number << ',' << m_average << endl;
    }
};

int main() {
	Student student;        // 定义类的对象
	student.input();        // 输入数据
	student.calculate();    // 计算平均成绩
	student.output();       // 输出数据
}