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

int MOD = 998244353;
int mod = 998244353;
int INF = INT_MAX;
const int MAX = 1000000 + 10;
struct Node {
  int l, r;
  int setTo = 0, mx = 0;
} tree[MAX * 4];

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  tree[id * 2 + 1] = {l, mid, 0, 0};
  tree[id * 2 + 2] = {mid + 1, r, 0, 0};
  build(id * 2 + 1);
  build(id * 2 + 2);
}

void update(int id, int s, int e, int val) { 
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e) {
    tree[id].setTo += val;
    tree[id].mx += val; 
    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;

  if(tree[id].setTo != 0) {
    update(left, tree[left].l, tree[left].r, tree[id].setTo);
    update(right, tree[right].l, tree[right].r, tree[id].setTo);
    tree[id].setTo = 0;
  }

  if(e <= mid) {
    update(left, s, e, val);
  } else if(s >= mid + 1) {
    update(right, s, e, val);
  } else {
    update(left, s, mid, val);
    update(right, mid + 1, e, val);
  }
  tree[id].mx = max(tree[left].mx, tree[right].mx);
}



int cnt[1000000 + 10];
int ids[1000000 + 10];
int id = 0;
void dfs(ve<ve<int>>& graph, int cur) {
  for(int& next : graph[cur]) {
    dfs(graph, next);
  }
  ids[cur] = id;
  id++;
}

int cal(ve<ve<int>>& graph, int cur) {
  cnt[cur] = 1;
  for(int& next : graph[cur]) {
    cnt[cur] += cal(graph, next);
  }
  return cnt[cur];
}

void solve(ve<int>& a, int k) {
  int n = a.size();
  ve<int> next(n, -1);
  ve<ve<int>> graph(n);
  memset(cnt, 0, sizeof(cnt));
  memset(ids, -1, sizeof(ids));

  tree[0] = {0, n, 0, 0};
  build(0);



  ve<int> sta;
  FOR(i, 0, n) {
    while(sta.size() > 0 && a[i] > a[sta[sta.size() - 1]]) {
      int index = sta[sta.size() - 1];
      sta.pop_back();
      next[index] = i;
    }
    sta.pb(i);
  }


  FOR(i, 0, n) {
    if(next[i] == -1) continue;
    int u = i, v = next[i];
    graph[v].pb(u);
  }


  FOR(i, 0, n) {
    if(next[i] == -1) { // root
      cal(graph, i);
      dfs(graph, i);
    }
  }


  for(int i = 0, j = 0; i < n; i++) {
    int r = ids[i], l = r - cnt[i] + 1;
    update(0, l, r, 1);
    if(i + 1 < k) continue;
    int mx = tree[0].mx;
    printf("%d ",mx);
    r = ids[j]; l = r - cnt[j] + 1;
    j++;
    update(0, r, r, -10000000);
  }

}



int main()
{
  int t = 1;
  //cin >> t;
  while (t--)
  {
    int n, k;
    cin >> n >> k;
    ve<int> a(n);
    FOR(i, 0, n) {
      cin >> a[i];
    }
    solve(a, k);
  }
  return 0;
}
