#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#include <list>

using namespace std;
using ll = long long;
#define pb push_back
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define RFOR(i, a, b) for (int i = a; i >= b; i--)
#define f first
#define se second
#define W while
#define um unordered_map
#define us unordered_set
#define be begin
#define en end


// Q: You are given an array a, you can do the following operations any number of times :
// 1. add 1 to every odd index a[1] += 1, a[3] += 1 ... 
// 2. add 1 to every even index a[0] += 1, a[2] += 1 ... 
// Determine if you can make all numbers even or odd (that is, all numbers must have the same parity)
// Print "YES" if you can, or "NO" if you can not

//Example1 : n = 4, a = [2 2 2 3] : NO
//Example2 : n = 3, a = [1 2 1] : YES
// n is the size of the array

void solve(vector<int>& a) {
  
  
}

int main()
{
  int t = 1;
  //cin >> t;
  W (t--)
  {
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
      cin >> a[i];
    }
    solve(a);
  }
  return 0;
}
