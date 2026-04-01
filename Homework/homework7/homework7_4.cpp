#include <iostream>
using namespace std;
class MyCin
{
// 在此处补充你的代码
bool MyStop{false};
public:
MyCin& operator>> (int& n) {
    cin >> n;
    if (n == -1) {MyStop = true;}
    return *this;
}
operator bool() {return !MyStop;}
};
int main()
{
    MyCin m;
    int n1,n2;
    while( m >> n1 >> n2) 
        cout  << n1 << " " << n2 << endl;
    return 0;
}