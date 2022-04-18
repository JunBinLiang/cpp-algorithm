#include<iostream> 
#include<string> 
using namespace std;

//i += 2    i = i + 2

int main() {
    for(int i = 0; i < 5; i += 2) {
        cout << i << endl;
    }
    
    int i = 0;
    while(i < 5) {
        cout << i << endl;
        i++;
    }
    
    
    return 0;
}
