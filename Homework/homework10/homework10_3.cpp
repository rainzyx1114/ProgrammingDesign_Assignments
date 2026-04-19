#include <iostream>
#include <cstring>
using namespace std;
template <int bitNum>
struct MyBitset 
{
	char a[bitNum/8+1];
	MyBitset() { memset(a,0,sizeof(a));};
	void Set(int i,int v) {
		char & c = a[i/8];
		int bp = i % 8;
		if( v ) 
			c |= (1 << bp);
		else 
			c &= ~(1 << bp);
	}
// 在此处补充你的代码
	class bitref {
		public:
		MyBitset& p;
		int idx;
		bitref(MyBitset& m, int i):p(m), idx(i) {}
		operator bool() {
			char c = p.a[idx / 8];
			int bp = idx % 8;
			return (c >> bp) & 1;
		}
		bitref& operator= (bitref& b) {
			p.Set(idx, static_cast<bool>(b));
			return *this;
		}
		bitref& operator= (int v) {
			p.Set(idx, v);
			return *this;
		}
		friend ostream& operator<< (ostream& out, bitref& b) {
			out << static_cast<bool>(b);
			return out;
		}
	};
	bitref operator[] (int idx) {
		return bitref(*this, idx);
	}
void Print() {
		for(int i = 0;i < bitNum; ++i) 
			cout << (*this) [i];
		cout << endl;
	}
};

int main()
{
	int n;
	int i,j,k,v;
	while( cin >>  n) {
		MyBitset<20> bs;
		for(int i = 0;i < n; ++i) {
			int t;
			cin >> t;
			bs.Set(t,1);
		}
		bs.Print();
		cin >> i >> j >> k >> v;
		bs[k] = v;
		bs[i] = bs[j] = bs[k];
		bs.Print();
		cin >> i >> j >> k >> v;
		bs[k] = v;
		(bs[i] = bs[j]) = bs[k];
		bs.Print();
	}
	return 0;
}