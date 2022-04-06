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
#define W while
#define RFOR(i, a, b) for (int i = a; i >= b; i--)
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

int MOD = 998244353;
int mod = 998244353 ;

ll dp[5001][5002];
ll temp[5002];
int n, k;
int dfs(ve<ve<int>>& graph, int pa, int root) {
  dp[root][0] = 1;
  ve<ve<int>> a;
  for(int & ne : graph[root]) {
    if(ne == pa) continue;
    int dia = dfs(graph, root, ne);
    a.pb({ne, dia});
  }

  int d = 0; 
  FOR(i, 0, a.size()) {
    int ne = a[i][0], dia = a[i][1];
    d = max(d, dia + 1);
    if(i == 0) {
      ll sum = 0;
      FOR(j, 0, min(k + 1, d + 1)) {
        dp[root][j + 1] = dp[ne][j];
        sum += dp[ne][j];
        sum %= mod;
      }
      dp[root][0] = sum;
      continue;
    }

    FOR(j, 0, min(d + 1, k + 1)) {
      temp[j] = 0;
    }  
    //connect
    FOR(x, 0, min(d + 1, k + 1)) {
      FOR(y, 0, min(d + 1, k + 1)) {
        if(y + x + 1 <= k) {
          int mx = max(y, x + 1);
          temp[mx] += dp[root][y] * dp[ne][x];
          temp[mx] %= mod;
        } else {
          break;
        }
      }
    }

    //not connect
    FOR(x, 0, min(d + 1, k + 1)) {
      FOR(y, 0, min(d + 1, k + 1)) {
        if(y <= k) {
          int mx = y;
          temp[mx] += dp[root][y] * dp[ne][x];
          temp[mx] %= mod;
        } 
      }
    }

    FOR(j, 0, min(d + 1, k + 1)) {
      dp[root][j] = temp[j];
      dp[root][j] %= mod;
    }
  }  
  return d;  
}

void solve() {
  scanf("%d%d", &n, &k);
  ve<ve<int>> graph(n);
  FOR(i, 0, n - 1) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--;
    v--;
    graph[u].pb(v);
    graph[v].pb(u); 
  }

  memset(dp, 0, sizeof(dp));
  dfs(graph, -1, 0);
  ll res = 0;
  FOR(i, 0, k + 1) {
    res += dp[0][i];
    res %= mod;
  }
  printf("%d", res);
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
