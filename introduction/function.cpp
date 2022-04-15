#include<iostream> 
#include<string> 
using namespace std;

int add1(int a, int b) {
    return a + b;
}

double add2(double a, double b) {
    return a + b;
}

string Hi() {
    return "Hi";
}

void print(string s) {
    cout << s << endl;
}

int main() {
    cout << Hi();
    return 0;
}
