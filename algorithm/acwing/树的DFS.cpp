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
#define f first
#define se second
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define RFOR(i, a, b) for (int i = a; i >= b; i--)
#define W while
#define um unordered_map
#define us unordered_set
#define str string

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
  return false;
}


int MOD = 998244353;
int mod = 1000000007;

ve<int> order;
int cnt[200000 + 10];
int dfs(ve<ve<int>>& graph, int root) {
  order.pb(root);
  cnt[root] = 1;
  FOR(i, 0, graph[root].size()) {
    int cur = graph[root][i];
    cnt[root] += dfs(graph, cur);
    
  }
  return cnt[root];
}

void solve() {
  int n, m;
  cin >> n >> m;
  ve<ve<int>> graph(n);
  memset(cnt, -1, sizeof(cnt));
  FOR(i, 1, n) {
    int a;
    scanf("%i", &a);
    int pa = a - 1;
    int u = i;
    graph[pa].pb(u);
  }

  for(ve<int>& a : graph) {
    sort(a.begin(), a.end());
  }
  dfs(graph, 0);
  um<int, int> f;
  FOR(i, 0, order.size()) {
    f[order[i]] = i;
  }

  FOR(i, 0, m) {
    int u, k;
    scanf("%i", &u);
    scanf("%i", &k);
    u--;

    int index = f[u];
    int ith = index + k - 1;
    if(k > cnt[u] ) {
      cout << -1 << endl;
    } else {
      cout << order[ith] + 1 << endl;
    }
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
