#include <iostream>
using namespace std;
// 在此处补充你的代码
template <class U, class V>
class f {
    public:
    U n;
    f (U nn):n(nn) {}
    auto operator() (V x) {return (x + n);}
};
int main()
{
   cout << f<int,int>(7)(9) << endl;   //16
   cout << f<string,string> (" hello!")("world")  <<endl; // world hello!
   cout << f<char,string> ('!')("world") << endl;
   
   
   return 0;    //world!
}