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



const int N = 200000 + 100;
const int M = 2000000;
int h1[N], h2[N], e[M], w[M], ne[M], idx;
int dfn[N], low[N], cnt;
int fa[N][19], depth[N];
int d[N];
bool see[N];
int n, m, q;
int new_n;
int X, Y;
ve<int> sta;


void add(int h[], int a, int b, int c) {
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ;
    idx++;
}


void tarjan(int u, int parent) {
    dfn[u] = low[u] = ++ cnt;
    sta.pb(u);
    for(int i = h1[u]; ~i; i = ne[i]) {
      int nxt = e[i];
      if(!dfn[nxt]) {
        tarjan(nxt, u);
        low[u] = min(low[u], low[nxt]);
        if(dfn[u] <= low[nxt]) {
          add(h2, u, new_n, 0);
         
          W(sta.size() > 0) {
            int v = sta[sta.size() - 1];
            if(v != nxt) {
               add(h2, new_n, v, 1);
               sta.pop_back();
            } else {
              add(h2, new_n, v, 1);
              sta.pop_back();
              break;
            }
          }
          new_n ++;
        }
      } else {
        if(nxt != (parent)) {
          low[u] = min(low[u], dfn[nxt]);
        }
      }
    }
}

int LCA(int x,int y) {
  if(depth[x] < depth[y]){
    swap(x, y);
  }

  for(int i = 18; i>=0; i--) {
    if(fa[x][i] != 0 && depth[fa[x][i]] >= depth[y]) {
      x = fa[x][i];
    }
  }
  if(x == y) return x;
  
  for(int i= 18; i>=0; i--) {
    if(fa[x][i] != fa[y][i]) {                    
      x = fa[x][i];
      y = fa[y][i];
    }
  }
  X = x, Y = y;
  return fa[x][0];
}


void init() {
  for(int i = 1; i < 19; i++){//construc sparse table
    for(int j = 0; j < N; j++){
      int parent = fa[j][i-1];
      if(parent == -1) continue;
      fa[j][i] = fa[parent][i-1];
    }
  }
}

void dfs_lca(int u, int father)
{
    depth[u] = depth[father] + 1;
    fa[u][0] = father;
    for (int i = h2[u]; ~i; i = ne[i])
    {
        int j = e[i];
        d[j] = d[u] + w[i];
        dfs_lca(j, u);
    }
}


void solve() {
  scanf("%d%d%d", &n, &m, &q);
  new_n = n + 1;
  idx = 0;
  memset(h1, -1, sizeof h1);
  memset(h2, -1, sizeof h2);
  memset(fa, -1, sizeof(fa));
  memset(ne, 0, sizeof(ne));
  for(int i = 0; i < m; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    add(h1, a, b, 0), add(h1, b, a, 0);
  }

  cnt = 0;
  
  tarjan(1, -1);
  dfs_lca(1, 0);
  init();
  W(q--) {
    int a, b;
    scanf("%d%d", &a, &b);
    int lca = LCA(a, b);
    if(lca > n) {
      printf("%d\n", d[a] + d[b] - 2 * d[lca] - 1);
    } else {
      printf("%d\n", d[a] + d[b] - 2 * d[lca]);
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
