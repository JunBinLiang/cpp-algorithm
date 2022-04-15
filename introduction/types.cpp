#include<iostream> 
#include<string> 
using namespace std;

//Types : 
//int : 2 ^ 32
//double
//char
//string
//long long : 2 ^ 64
//ascii table for character : https://www.alpharithms.com/ascii-table-512119/

int main() {
    int a = 2;
    double b = 2.5;
    char c = '1';
    string s = "100";
    cout << a << "   " << b << endl;
    cout << s << endl;
    cout << c << endl;
    cout << s + to_string(a) << endl;
    return 0;
}
