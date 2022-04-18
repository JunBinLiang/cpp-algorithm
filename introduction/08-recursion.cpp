#include<iostream> 
using namespace std;

int sum1(int n) {
    //1 + 2 + 3 + ... n
    int sum = 0;
    for(int i = 1; i <= n; i++) {
        sum += i;
    }
    return sum;
}

//recursion : function call function
int sum2(int n) {
    if(n == 1) {
        return 1;
    }
    return n + sum2(n - 1);
}


int main() {
    cout << sum2(4) << endl;
    
    return 0;
}
