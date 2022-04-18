#include<iostream> 
using namespace std;


void change1(int x, int y) {
    x = 10;
    y = 5;
}

void change2(int &x, int &y) {
    x = 11;
    y = 12;
}



int main() {
    int x = 1, y = 2;
    change1(x, y);
    cout <<x << " " << y << endl;//1, 2
    cout << endl;
    
    change2(x, y);
    cout <<x << " " << y << endl;//11 12
    
    return 0;
}
