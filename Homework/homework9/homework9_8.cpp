#include <iostream>
#include <string>
#include <map>
#include <iterator>
#include <algorithm>
#include <cstdlib>

using namespace std;
// 在此处补充你的代码
template <typename T, typename U, typename F = greater<T>>
class MyMultimap {
    public:
    multimap<T, U, F> mm;
	class iterator {
		public:
		typename multimap<T, U, F>::iterator it;
		iterator(typename multimap<T, U, F>::iterator i):it(i) {}
		pair<const T, U>* operator-> () {
			return &(*it);
		}
		string operator* () {
			string ans = "(" + toString(it->first) + "," + toString(it->second) + ")";
			return ans;
		}
		iterator& operator++ () {
			it ++;
			return *this;
		}
		iterator operator++ (int) {
			iterator tmp = *this;
			it ++;
			return tmp;
		}
		bool operator!= (iterator i) {
			return it != i.it;
		}
		bool operator== (iterator i) {
			return it == i.it;
		}
		private:
			template<class V>
			static string toString(const V& val) {
				return to_string(val);
			}
			static string toString(const string& s) {
				return s;
			}
	};
    void insert(pair<T, U> p) {
        mm.insert(p);
    }
    void Set(T k, U val) {
		auto p = mm.equal_range(k);
		int num = mm.count(k);
		mm.erase(p.first, p.second);
		while(num --) {
			mm.insert(make_pair(k, val));
		}
	}
	void clear() {
		mm.clear();
	}
	iterator find(T k) {
		return iterator(mm.find(k));
	}
	iterator begin() {
		return iterator(mm.begin());
	}
	iterator end() {
		return iterator(mm.end());
	}
};
struct Student 
{
	string name;
	int score;
};
template <class T>
void Print(T first,T last) {
	for(;first!= last; ++ first)
		cout << * first << ",";
	cout << endl;
}
int main()
{
	
	Student s[] = { {"Tom",80},{"Jack",70},
					{"Jone",90},{"Tom",70},{"Alice",100} };
	
	MyMultimap<string,int> mp;
	for(int i = 0; i<5; ++ i)
		mp.insert(make_pair(s[i].name,s[i].score));
	Print(mp.begin(),mp.end()); //按姓名从大到小输出

	mp.Set("Tom",78); //把所有名为"Tom"的学生的成绩都设置为78
	Print(mp.begin(),mp.end());
	
	
	
	MyMultimap<int,string,less<int> > mp2;
	for(int i = 0; i<5; ++ i) 
		mp2.insert(make_pair(s[i].score,s[i].name));
	
	Print(mp2.begin(),mp2.end()); //按成绩从小到大输出
	mp2.Set(70,"Error");          //把所有成绩为70的学生，名字都改为"Error"
	Print(mp2.begin(),mp2.end());
	cout << "******" << endl;
	
	mp.clear();
	
	string name;
	string cmd;
	int score;		
	while(cin >> cmd ) {
		if( cmd == "A") {
			cin >> name >> score;
			if(mp.find(name) != mp.end() ) {
				cout << "erroe" << endl;
			}
			mp.insert(make_pair(name,score));
		}
		else if(cmd == "Q") {
			cin >> name;
			MyMultimap<string,int>::iterator p = mp.find(name);
			if( p!= mp.end()) {
				cout << p->second << endl;
			}
			else {
				cout << "Not Found" << endl; 
			}		
		}
	}
	return 0;
}