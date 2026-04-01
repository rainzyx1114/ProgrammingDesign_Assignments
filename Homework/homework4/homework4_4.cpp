#include <iostream>
#include <cstring>
using namespace std;

class Array2 {
// 在此处补充你的代码
    int** arr;
    int row,col;
    public:
        Array2() = default;
        Array2(int r, int l):arr(new int*[r]), row(r), col(l){
            for (int i = 0; i < r; i++) {
                arr[i] = new int[l];
            }
        }
        int* operator[] (int i) {
            return arr[i];
        }
        int operator() (int i, int j) {
            return arr[i][j];
        }
        Array2& operator= (const Array2 a) {
            if(this != &a) {
                if (arr) delete[] arr;
                if (a.arr) {
                    row = a.row;
                    col = a.col;
                    arr = new int*[a.row];
                    for (int i = 0; i < row; i++) {
                        arr[i] = new int[a.col];
                    }
                    for (int i = 0; i < row; i++) {
                        for (int j =0; j < col; j++) {
                            arr[i][j] = a.arr[i][j];
                        }
                    }
                }
                else {
                    arr = nullptr;
                }
            }
            return *this;
        }
};

int main() {
    Array2 a(3,4);
    int i,j;
    for(  i = 0;i < 3; ++i )
        for(  j = 0; j < 4; j ++ )
            a[i][j] = i * 4 + j;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << a(i,j) << ",";
        }
        cout << endl;
    }
    cout << "next" << endl;
    Array2 b;     b = a;
    for(  i = 0;i < 3; ++i ) {
        for(  j = 0; j < 4; j ++ ) {
            cout << b[i][j] << ",";
        }
        cout << endl;
    }
    return 0;
}