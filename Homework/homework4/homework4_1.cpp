#include <iostream>
#include <string>
#include <cstring>
using namespace std;
class MyString {
	char * p;
public:
	MyString(const char * s) {
		if(s) {
			p = new char[strlen(s) + 1];
			strcpy(p,s);
		}
		else
			p = NULL;

	}
	~MyString() { if(p) delete [] p; }
    MyString(const MyString& str) {
        if(p) delete [] p;
        if(str.p) {
            p = new char[strlen(str.p) + 1];
            strcpy(p, str.p);
        }
        else {
            p = NULL;
        }
    }
    void Copy(const char* str) {
        if(p) delete [] p;
        if(str) {
            p = new char[strlen(str) + 1];
            strcpy(p, str);
        }
        else {
            p = NULL;
        }
    }
    MyString& operator= (const MyString& str) {
        if (this != &str) {
            this->Copy(str.p);
        }
        return *this;
    }
    friend ostream& operator<< (ostream& out, const MyString& str) {
        if(str.p) {
            out << str.p;
        }
        return out;
    }
};
 
int main()
{
	char w1[200],w2[100];
	while( cin >> w1 >> w2) {
		MyString s1(w1),s2 = s1;
		MyString s3(NULL);
		s3.Copy(w1);
		cout << s1 << "," << s2 << "," << s3 << endl;

		s2 = w2;
		s3 = s2;
		s1 = s3;
		cout << s1 << "," << s2 << "," << s3 << endl;
		
	}
}