#include <iostream> 
#include <cstring> 
#include <cstdlib> 
#include <cstdio> 
using namespace std;
const int MAX = 110; 
class CHugeInt {
// 在此处补充你的代码
    string s;
    public:
        CHugeInt(const char* c):s(c) {}
        CHugeInt(int n) {
            s = "";
            while(n != 0) {
                s = (char)(n % 10 +'0') + s;
                n /= 10;
            }
        }
        friend CHugeInt operator+ (CHugeInt left, CHugeInt right) {
            string ans = "";
            string l = left.s;
            string r = right.s;
            int llen = l.size();
            int rlen = r.size();
            int len = max(llen, rlen);
            while (llen != rlen) {
                if (llen < rlen) {
                    l = '0' + l;
                    llen ++;
                }
                else if(llen > rlen) {
                    r = '0' + r;
                    rlen ++;
                }
            }
            int lef = 0;
            for (int i = len - 1; i >= 0; i--) {
                int lt = l[i] - '0';
                int rt = r[i] - '0';
                int sum = lt + rt + lef;
                ans = (char)(sum % 10 + '0') + ans;
                lef = sum / 10; 
            }
            if (lef != 0) {
                ans = (char)(lef + '0') + ans;
            }
            return CHugeInt(ans.c_str());
        }
        friend CHugeInt operator+ (int n, CHugeInt& right) {
            return CHugeInt(n) + right;
        }
        friend CHugeInt operator+ (CHugeInt& left, int n) {
            return left + CHugeInt(n);
        }
        CHugeInt& operator+= (int n) {
            *this = *this + n;
            return *this;
        }
        CHugeInt& operator++ () {
            *this += 1;
            return *this;
        }
        CHugeInt operator++ (int) {
            CHugeInt temp = *this;
            *this += 1;
            return temp;
        }
        friend ostream& operator<< (ostream& out, CHugeInt i) {
            out << i.s;
            return out;
        }
};
int  main() 
{ 
	char s[210];
	int n;

	while (cin >> s >> n) {
		CHugeInt a(s);
		CHugeInt b(n);

		cout << a + b << endl;
		cout << n + a << endl;
		cout << a + n << endl;
		b += n;
		cout  << ++ b << endl;
		cout << b++ << endl;
		cout << b << endl;
	}
	return 0;
}