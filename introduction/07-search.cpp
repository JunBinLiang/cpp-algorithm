#include<iostream> 
#include<string> 
using namespace std;

//array
int main() {
  int a[5];
  bool found = false;
  for(int i = 0; i < 5; i++) {
      cin >> a[i];
      if(a[i] == 4) {
          found = true;
      }
  }
  
  if(found) {
      cout << "YES" << endl;
  } else {
      cout << "NO" <<endl;
  }
}
