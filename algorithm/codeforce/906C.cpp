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
    bool operator() (ve<int>& a, ve<int>& b)
    {
        return a[0] > b[0];
    }
};*/

int n, m;
int dp[(1 << 22) + 5][2];
int target = -1;
int dfs(ve<int>& a, int state) {
  if(state == target) {
    return 0;
  }
  if(dp[state][0] != -1) {
    return dp[state][0];
  }

  int res = n;
  for(int i = 0; i < n; i++) {
    if(state & (1 << i)) {
      if(state == (state | a[i])) continue;
      int newstate = state | a[i];
      int val = 1 + dfs(a, newstate);
      if(val < res) {
        res = val;
        dp[state][1] = i;
      }
    }
  }
  return dp[state][0] = res;
}


void solve() {
  scanf("%d%d", &n, &m);
  
  
  ve<int> a(n);
  target = (1 << n) - 1;
  FOR(i, 0, m) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--; v--;
    a[u] |= (1 << v);
    a[v] |= (1 << u);
  }

  bool all = true;
  for(int i = 0; i < n; i++) {
    a[i] |= (1 << i);
    if(a[i] != target) all = false;
  }
  
  if(all) {
      cout << 0 << endl;
      return;
  }
  
 

  memset(dp, -1, sizeof(dp));
  int res = n;
  int u = -1, state = 0;
  for(int i = 0; i < n; i++) {
    int val = 1 + dfs(a, a[i]);
    if(val < res) {
      res = val, u = i;
    }
  }

  ve<int> b;
  for(int i = 0; i < res; i++) {
    b.pb(u);
    state |= a[u];
    u = dp[state][1];
  }

  cout << res << endl;
  for(int i : b) {
    cout << (i + 1) << " " ;
  } cout << endl;
  
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
