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


int n;
int cnt[3001][3001];
int fa[3001][3001];
int dp[3001][3001];
int Root = -1;
int dfs(ve<ve<int>> &graph, int pa, int root) {
  cnt[Root][root] = 1;
  fa[Root][root] = pa;
  for(int nxt : graph[root]) {
    if(nxt == pa) continue;
    cnt[Root][root] += dfs(graph, root, nxt);
  }
  return cnt[Root][root];
}

ll dfs1(int x, int y) {
  if(x == y) {
    return 1;
  }
  if(dp[x][y] != -1) {
    return dp[x][y];
  }
  return (cnt[x][y] * cnt[y][x]) + max(dfs1(x, fa[x][y]), dfs1(dfs[y][x], y)); 
}


void solve() {
  scanf("%d", &n);
  ve<ve<int>> graph(n);
  FOR(i, 0, n - 1) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--; v--;
    graph[u].pb(v);
    graph[v].pb(u);
  }
  
  for(int i = 0; i < n; i++) {
    Root = i;
    dfs(graph, -1, i);
  }

  memset(dp, -1, sizeof(dp));
  ll res = 0;
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      res = max(res, dfs(i, j));
    }
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
