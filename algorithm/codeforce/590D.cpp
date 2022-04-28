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

// Some predefined templates
template <typename T>
ostream &operator<<(ostream &out, const vector<T> &a)
{
  out << "[";
  bool first = true;
  for (auto v : a)
  {
    out << (first ? "" : ", ");
    out << v;
    first = 0;
  }
  out << "]";
  return out;
}

template <typename T>
ostream &operator<<(ostream &out, const unordered_set<T> &a)
{
  out << "[";
  bool first = true;
  for (auto v : a)
  {
    out << (first ? "" : ", ");
    out << v;
    first = 0;
  }
  out << "]";
  return out;
}

template <typename T>
ostream &operator<<(ostream &out, const set<T> &a)
{
  out << "[";
  bool first = true;
  for (auto v : a)
  {
    out << (first ? "" : ", ");
    out << v;
    first = 0;
  }
  out << "]";
  return out;
}

template <typename U, typename T, class Cmp>
ostream &operator<<(ostream &out, const map<U, T, Cmp> &a)
{
  out << "{";
  bool first = true;
  for (auto &p : a)
  {
    out << (first ? "" : ", ");
    out << p.first << ":" << p.second;
    first = 0;
  }
  out << "}";
  return out;
}

template <typename U, typename T, class Cmp>
ostream &operator<<(ostream &out, const unordered_map<U, T, Cmp> &a)
{
  out << "{";
  bool first = true;
  for (auto &p : a)
  {
    out << (first ? "" : ", ");
    out << p.first << ":" << p.second;
    first = 0;
  }
  out << "}";
  return out;
}


ll gcd(ll x, ll y)
{
  return (y == 0 ? x : gcd(y, x % y));
}
ll lcm(ll x, ll y)
{
  return x * y / gcd(x, y);
}

int to_int(string &s)
{
  int res = 0;
  for (char c : s)
  {
    res = res * 10 + (c - '0');
  }
  return res;
}

bool COMP(ve<int>& a, ve<int>& b) {
  return a[0] < b[0];
}

/*class Compare
{
public:
    bool operator() (ve<ll>& a, ve<ll>& b)
    {
        return a[0] > b[0];
    }
    //a[0] > b[0] : min
};*/


int n, k, s;
int a[200];


void solve() {
  scanf("%d%d%d", &n, &k, &s);
  FOR(i, 0, n) {
    scanf("%d", &a[i]);
  }

  const int SIZE = min(s + 1, n * (n - 1) / 2 + 5);
  const int MAX = 1000000000;
  int dp[k + 1][SIZE];
  for(int i = 0; i < k + 1; i++) {
    for(int j = 0; j < SIZE; j++) {
      dp[i][j] = MAX;
    }
  }

  int res = MAX;
  for(int i = 0; i < n; i++) {
    int dp1[k + 1][SIZE]; 
    for(int x = 0; x < k + 1; x++) {
        for(int y = 0; y < SIZE; y++) {
          dp1[x][y] = MAX;
        }
    }
      
    if(i < SIZE) {
        dp1[0][i] = min(dp1[0][i], a[i]);  
    }
    
    for(int kk = 1; kk <= min(i, k - 1); kk++) {
      //i element place as kth
      int swapNeed = i - kk;
      for(int change = swapNeed; change < SIZE; change++) {
        dp1[kk][change] = min(dp1[kk][change], a[i] + dp[kk - 1][change - swapNeed]);
      }
    }
    
    
    for(int x = 0; x < k + 1; x++) {
        for(int y = 0; y < SIZE; y++) {
          dp[x][y] = min(dp1[x][y], dp[x][y]);
        }
    }
  }


  for(int i = 0; i < SIZE; i++) {
    res = min(res, dp[k - 1][i]);
  }
  cout << res << endl;
}

int main()
{
  int t = 1;
  //cin >> t;
  W (t--)
  {
    solve();
  }
  return 0;
}
