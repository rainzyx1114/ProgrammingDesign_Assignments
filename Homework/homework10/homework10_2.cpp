#include <iostream>
using namespace std;
// 在此处补充你的代码
template <class func1, class func2, class T> 
class combine {
    public:
        func1 f;
        func2 g;
        combine(func1 f1, func2 f2):f(f1), g(f2) {}
        T operator() (T x) {return f(f(x) + g(x));}
};
int main()
{
    auto Square = [] (double a) { return a * a; };
    auto Inc = [] (double a) { return a + 1; };
    cout << combine<decltype(Square),decltype(Inc),int>(Square,Inc)(3) << endl;
    cout << combine<decltype(Inc),decltype(Square),double>(Inc,Square)(2.5) << endl;

    return 0;
}
