#include<iostream> 
#include<vector> 
using namespace std;


//array : fix size
//vercor : (object) array, dynamic size

int main() {
    vector<int> a = {1, 2};
    cout << a.size() << endl;
    a.push_back(10);
    cout << a.size() << endl;
    cout << endl;
    for(int i = 0; i < a.size(); i++) {
        cout << a[i] << endl;
    }
    return 0;
}
