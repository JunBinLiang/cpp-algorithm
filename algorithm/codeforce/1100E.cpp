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
  return a[2] < b[2];
}

int MOD = 998244353;
int mod = 998244353;

ve<ve<int>> a[1000000 + 5];
int in[100000 + 5];
bool is[100000 + 5];
bool seen[100000 + 5];
int Rank[100000 + 5];
bool check(ve<ve<int>>& edges, int n, int mid) {
  queue<int> q;
  int total = 0;
  FOR(i, 0, n + 1) {
    in[i] = 0;
    seen[i] = false;
    Rank[i] = 0;
  }

  FOR(i, 0, edges.size()) {
    ve<int>& edge = edges[i];
    if(edge[2] <= mid) continue;
    in[edge[1]]++;
  }

  int x = 0;
  int cnt = 0;
  FOR(i, 0, n) {
    if(in[i] == 0) {
      q.push(i);
    }
  }

  
  W(q.size()) {
    int root = q.front(); q.pop();
    cnt++;
    Rank[root] = ++x;
    for(ve<int>& p : a[root]) {
      int ne = p[0], w = p[1];
      if(w <= mid) continue;
      in[ne]--;
      if(in[ne] == 0) {
        q.push(ne);
      }
    }
  }
  return cnt == n;
}

void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  ve<ve<int>> edges;
  FOR(i, 0, n + 1) {
    a[i].clear();
  }

  int mx = 0;
  FOR(i, 0, m) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    u--;
    v--;
    edges.pb({u, v, w});
    a[u].pb({v, w});
    mx = max(mx, w);
  }

  int res = -1;
  int l = 0, r = mx;
  W(l <= r) {
    int mid = l + (r - l) / 2;
    if(check(edges, n, mid)) {
      res = mid;
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }

  check(edges, n, res);

  ve<int> b;
  FOR(i, 0, m) {
    ve<int>& edge = edges[i];
    if(edge[2] > res) continue;
    int u = edge[0], v = edge[1];
    if(Rank[v] < Rank[u]) {
      b.pb(i);
    }
  }

  sort(b.begin(), b.end());
  printf("%d %d\n", res, b.size());
  for(int i : b) {
    printf("%d ", i + 1);
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
