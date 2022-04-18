#include<iostream> 
using namespace std;

int sum(int a, int b) {
    int sum = 0;
    for(int i = 0; i < b; i++) {
        sum += a;
    }
    return sum;
}

int sum1(int a, int b) {
    if(b == 1) {
        return a;
    }
    return a + sum1(a, b - 1);
}

//f(3,4) = 3 + f(3,3)
//f(3,3) = 3 + f(3, 2)
//f(3, 2) = 3 + f(3, 1)
//f(3, 1) = 3

int main() {
    cout << sum1(4,5) << endl;
    return 0;
}


