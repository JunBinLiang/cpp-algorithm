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

/*class Compare
{
public:
    bool operator() (ve<ll>& a, ve<ll>& b)
    {
        return a[0] > b[0];
    }
    //a[0] > b[0] : min
};*/


bool COMP(pair<int, int>& p1, pair<int, int>& p2) {
  return p1.second < p2.second;
}

int mx = 0;
int dfs(ve<ve<int>>& graph, int pa, int root) {
  int son = 0;
  ve<int> a;
  for(int& nxt : graph[root]) {
    if(nxt == pa) continue;
    int x = dfs(graph, root, nxt);
    a.pb(1 + x);
  }

  if(a.size() == 0) {
    return 0;
  }

  sort(a.begin(), a.end());
  if(root == 0) {
    mx = max(mx, a[a.size() - 1]);
    if(a.size() >= 2) {
      mx = max(mx, a[a.size() - 2] + 1);
    }

  } else {
    if(a.size() > 1) mx = max(mx, a[a.size() - 1] + 1);
  }
  return a[0];
  
}

void solve() {
  int n;
  scanf("%d", &n);
  ve<ve<int>> graph(n);
  for(int i = 0; i < n - 1; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--; v--;
    graph[u].pb(v);
    graph[v].pb(u);
  }
  mx = 0;
  dfs(graph, -1, 0);
  cout << mx << endl;

}

int main()
{
  int t = 1;
  cin >> t;
  W (t--)
  {
    solve();
  }
  return 0;
}
