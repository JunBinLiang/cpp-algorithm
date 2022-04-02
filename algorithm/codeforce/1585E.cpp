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
  return false;
}

int MOD = 998244353;
int mod = 1000000007;

const int MAX = 1000000 + 10;
struct Node {
  int l, r;
  int val = 0, sum = 0;
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

void update(int id, int index, int val) { 
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    tree[id].val += val; 
    tree[id].sum += val; 
    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(index <= mid) {
    update(left, index, val);
  } else {
    update(right, index, val);
  }
  tree[id].sum = (tree[left].sum + tree[right].sum);
}

int query(int id, int s, int e) { // query sum from [0 : l]
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return tree[id].sum;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(e <= mid){
      return query(left, s, e);
  } else if(s >= mid + 1) {
      return query(right, s, e);
  } else {
    return query(left, s, mid) + query(right, mid + 1, e);
  }
}

int search(int id, int k) {//find kth element
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    return l;
  }

  

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;

  if(k <= tree[left].sum) {
    return search(left, k);
  } else {
    return search(right, k - tree[left].sum);
  }
}



int a[1000000 + 5];
ve<ve<int>> b[1000000 + 5];
int res[1000000 + 5];
um<int, int> f;
um<int, us<int>> g;
void dfs(ve<ve<int>>&graph, int root) {
  int val = a[root];
  int old = f[val];
  f[val]++;
  if(old != 0) {
    g[old].erase(val);
    update(0, old, -1);
  }
  int newf = f[val];
  g[newf].insert(val);
  update(0, newf, 1);

  for(ve<int>& q : b[root]) {
    int i = q[0], l = q[1], k = q[2];
    
    int leftsum = query(0, 0, l - 1);
    int total = tree[0].sum;

    if(leftsum + k > total) {
      res[i] = -1;
    } else {
      int fre = search(0, leftsum + k);
      auto first = g[fre].begin();
      res[i] = (*first);
    }
  }
  
  for(int &next : graph[root]) {
    dfs(graph, next);
  }

  //revover
  old = f[val];
  f[val]--;
  if(old != 0) {
    g[old].erase(val);
    update(0, old, -1);
  }
  newf = f[val];
  g[newf].insert(val);
  update(0, newf, 1);

}

void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  ve<ve<int>> graph(n);
  f.clear();
  g.clear();
  FOR(i, 0, n) {
    scanf("%i", &a[i]);
    b[i].clear();
  }

  FOR(i,1, n) {
    int p;
    scanf("%i", &p);
    p--;
    graph[p].pb(i);
  }
  FOR(i, 0, m) {
    int v, l, k;
    scanf("%d%d%d", &v, &l, &k);
    v--;
    b[v].pb({i, l, k});
  }


  tree[0] = {0, n + 1, 0, 0};
  build(0);
  dfs(graph, 0);

  FOR(i, 0, m) {
    printf("%d ", res[i]);
  }
  printf("\n"); 
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
