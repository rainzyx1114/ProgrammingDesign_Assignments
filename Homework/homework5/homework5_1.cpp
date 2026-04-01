#include <cstdlib>
#include <iostream>
using namespace std;
int strlen(const char * s) 
{	int i = 0;
	for(; s[i]; ++i);
	return i;
}
void strcpy(char * d,const char * s)
{
	int i = 0;
	for( i = 0; s[i]; ++i)
		d[i] = s[i];
	d[i] = 0;
		
}
int strcmp(const char * s1,const char * s2)
{
	for(int i = 0; s1[i] && s2[i] ; ++i) {
		if( s1[i] < s2[i] )
			return -1;
		else if( s1[i] > s2[i])
			return 1;
	}
	return 0;
}
void strcat(char * d,const char * s)
{
	int len = strlen(d);
	strcpy(d+len,s);
}
class MyString
{
// 在此处补充你的代码
char* ptr{nullptr};
public:
    MyString():ptr(new char[1]) {ptr[0] = 0;}
    MyString(const char* str) {
        if (ptr) {
            delete[] ptr;
        }
        if (str) {
            ptr = new char[strlen(str) + 1];
            strcpy(ptr, str);
        }
        else {
            ptr = nullptr;
        }
    }
    MyString(const MyString& s) {
        if (ptr) {
            delete[] ptr;
        }
        if (s.ptr) {
            ptr = new char[strlen(s.ptr) + 1];
            strcpy(ptr, s.ptr);
        }
        else {
            ptr = nullptr;
        }
    }
    friend ostream& operator<< (ostream& out, MyString s) {
        out << s.ptr;
        return out;
    }
    MyString& operator= (MyString s) {
        if (ptr != nullptr) {
            delete[] ptr;
        }
        if (s.ptr != nullptr) {
            ptr = new char[strlen(s.ptr) + 1];
            strcpy(ptr, s.ptr);
        }
        else {
            ptr = nullptr;
        }
        return *this;
    }
    friend MyString operator+ (MyString left, MyString right) {
        char* temp = new char[strlen(left.ptr) + 1];
        strcpy(temp, left.ptr);
        strcat(temp, right.ptr);
        return MyString(temp);
    }
    friend MyString operator+ (MyString left, const char* right) {
        char* temp = new char[strlen(left.ptr) + 1];
        strcpy(temp, left.ptr);
        strcat(temp, right);
        return MyString(temp);
    }
    friend MyString operator+ (const char* left, MyString right) {
        char* temp = new char[strlen(left) + 1];
        strcpy(temp, left);
        strcat(temp, right.ptr);
        return MyString(temp);
    }
    char& operator[] (int index) {
        return ptr[index];
    }
    MyString& operator+= (const char* str) {
        strcat(ptr, str);
        return *this;
    }
    friend bool operator< (const MyString& s1, const MyString& s2) {
        return strcmp(s1.ptr, s2.ptr) < 0;
    }
    friend bool operator> (const MyString& s1, const MyString& s2) {
        return strcmp(s1.ptr, s2.ptr) > 0;
    }
    friend bool operator== (const MyString& s1, const MyString& s2) {
        return strcmp(s1.ptr, s2.ptr) == 0;
    }
    const char* operator() (int s, int len){
        char* temp = new char[len + 1];
        for (int i = s; i < s + len; i ++) {
            temp [i - s] = ptr[i];
        }
        return temp;
    }
};


int CompareString( const void * e1, const void * e2)
{
	MyString * s1 = (MyString * ) e1;
	MyString * s2 = (MyString * ) e2;
	if( * s1 < *s2 )
	return -1;
	else if( *s1 == *s2)
	return 0;
	else if( *s1 > *s2 )
	return 1;
}
int main()
{
	MyString s1("abcd-"),s2,s3("efgh-"),s4(s1);
	MyString SArray[4] = {"big","me","about","take"};
	cout << "1. " << s1 << s2 << s3<< s4<< endl;
	s4 = s3;
	s3 = s1 + s3;
	cout << "2. " << s1 << endl;
	cout << "3. " << s2 << endl;
	cout << "4. " << s3 << endl;
	cout << "5. " << s4 << endl;
	cout << "6. " << s1[2] << endl;
	s2 = s1;
	s1 = "ijkl-";
	s1[2] = 'A' ;
	cout << "7. " << s2 << endl;
	cout << "8. " << s1 << endl;
	s1 += "mnop";
	cout << "9. " << s1 << endl;
	s4 = "qrst-" + s2;
	cout << "10. " << s4 << endl;
	s1 = s2 + s4 + " uvw " + "xyz";
	cout << "11. " << s1 << endl;
	qsort(SArray,4,sizeof(MyString),CompareString);
	for( int i = 0;i < 4;i ++ )
	cout << SArray[i] << endl;
	//s1的从下标0开始长度为4的子串
	cout << s1(0,4) << endl;
	//s1的从下标5开始长度为10的子串
	cout << s1(5,10) << endl;
	return 0;
}