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

int n;
int a[600][600];
int res[1000000];
int cnt = 0;
ve<pair<int, int>> edges;
int dfs(ve<int>& b) {
  if(b.size() == 1) {
    return b[0];
  }

  int mx = 0;
  for(int i = 0; i < b.size(); i++) {
    for(int j = i + 1; j < b.size(); j++) {
      mx = max(mx, a[b[i]][b[j]]);
    }
  }

  int u = cnt;
  res[u] = mx;
  cnt++;

  ve<bool> is(b.size());
  for(int i = 0; i < b.size(); i++) {
    if(!is[i]) {
      ve<int> c;
      c.pb(b[i]);
      is[i] = true;
      for(int j = 0; j < b.size(); j++) {
        if(is[j] || a[b[i]][b[j]] == mx) continue;
        is[j] = true;
        c.pb(b[j]);
      }
      if(c.size() > 0) {
        int v = dfs(c);
        edges.pb({u, v});
      }
    }
  }
  

  ve<int> c;
  for(int i = 0; i < b.size(); i++) {
    if(!is[i]) {
      edges.pb({u, b[i]});
    }
  }

  return u;
}


void solve() {
  scanf("%d", &n);
  cnt = n;
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      scanf("%d", &a[i][j]);
      if(i == j) {
        res[i] = a[i][j];
      }
    }
  }

  ve<int> c(n);
  for(int i = 0; i < n; i++) {
    c[i] = i;
  }

  int root = dfs(c);
  printf("%d \n", cnt);
  for(int i = 0; i < cnt; i++) {
    printf("%d ", res[i]);
  }
  printf("\n");
  printf("%d \n", root + 1);
  for(int i = 0; i < cnt - 1; i++) {
    printf("%d %d \n", edges[i].second + 1, edges[i].first + 1);
  }


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
