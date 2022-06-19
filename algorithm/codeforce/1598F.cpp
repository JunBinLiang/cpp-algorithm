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

string substring(string& s, int l, int r) {
  string res = "";
  for(int i = l; i <= r; i++) res += s[i];
  return res;
}

/*class Compare
{
public:
    bool operator() (pair<int, int>& a, pair<int, int>& b)
    {
        return a.first > b.first;
    }
    //a[0] > b[0] : min
};*/

bool COMP(const pair<int, int>&p1, const pair<int, int>&p2) {
  return p1.second < p2.second;
}

um<int, int> maps[21];
um<int, int> mmaps[21];
int cnts[21];
int mins[21]; 
int dp[(1 << 20) + 5][2];
void solve() {
  int n;
  cin >> n;
  ve<string> a(n);
  for(int i = 0; i < n; i++) {
    cin >> a[i];
  }

  for(int i = 0; i < n; i++) {
    string& s = a[i];
    int cnt = 0;
    int mn = 1000000000;
    for(int j = 0; j < s.size(); j++) {
      if(s[j] == '(') {
        cnt++;
      } else {
        cnt--;
      }
      maps[i][cnt]++;
      if(j + 1 < s.size() && s[j + 1] == ')') {
        if(mmaps[i].find(cnt) == mmaps[i].end()) {
          mmaps[i][cnt] = maps[i][cnt];
        }
      }
      mn = min(mn, cnt);
    }
    
    if(s[0] == ')') {
        mmaps[i][0] = 0;
    }
    
    cnts[i] = cnt;
    mins[i] = mn;
  }
  

  for(int i = 0; i < (1 << n); i++) {
    dp[i][0] = -1;
    dp[i][1] = 0;
  }


  dp[0][0] = dp[0][1] = 0;
  int res = 0;
  for(int state = 1; state < (1 << n); state++) {
    for(int i = 0; i < n; i++) {
      if((state & (1 << i)) > 0) {
        int last = state ^ (1 << i);
        if(dp[last][0] >= 0) {
          int mn = mins[i];
          if(mn < 0 && abs(mn) > dp[last][0]) {
            int x = mmaps[i][-(dp[last][0])];
            res = max(res, dp[last][1] + x);
            continue;
          }
          dp[state][1] = max(dp[state][1], dp[last][1] + maps[i][-dp[last][0]]);
          dp[state][0] = dp[last][0] + cnts[i];
        }
      }
    }
  }

 
  for(int i = 0; i < (1 << n); i++) {
    res = max(res, dp[i][1]);  
  }
  
  printf("%d \n", res);
  
  
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
