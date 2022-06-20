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


int n, L;
ll S;
int a[100000 + 5];
int f[100000 + 5][18];
ll sums[100000 + 5][18];
int dep[100000 + 5];
int to[100000 + 5];
int dp[100000 + 5];
int ans = 0;

void dfs(ve<ve<int>>& graph, int pa, int root) {
  if(pa == -1) {
    dep[root] = 0;
  } else {
    dep[root] = dep[pa] + 1;
  }
  for(int& nxt : graph[root]) {
    if(nxt != pa) {
      dfs(graph, root, nxt);
    }
  }
}

void dfs1(ve<ve<int>>& graph, int pa, int root) {
  int res = -1;
  for(int& nxt : graph[root]) {
    if(nxt == pa) continue;
    dfs1(graph, root, nxt);
    if(dp[nxt] == nxt) continue;
    if(res == -1 || dep[res] > dep[dp[nxt]]) {
      res = dp[nxt];
    }
  }

  if(res == -1) {
    ans++;
    res = to[root];
  }
  dp[root] = res;

}

void solve() {
  cin >> n >> L >> S;
  bool check = false;
  for(int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    if(a[i] > S) {
      check = true;
    }
    sums[i][0] = a[i];
  }
    

  ve<ve<int>> graph(n);
  memset(f, -1, sizeof(f));
  for(int i = 1; i < n; i++) {
    int u;
    scanf("%d", &u);
    int pa = u - 1;
    graph[pa].pb(i);
    graph[i].pb(pa);
    f[i][0] = pa;
    sums[i][0] += a[pa];
  }

  if(check) {
    cout << -1 << endl;
    return;
  }

  for(int j = 1; j < 18; j++) {
    for(int i = 0; i < n; i++) {
      if(f[i][j - 1] != -1){
        f[i][j] = f[f[i][j - 1]][j - 1];
        sums[i][j] = sums[i][j - 1] + sums[f[i][j - 1]][j - 1] - a[f[i][j - 1]];
      }
    }
  }

  for(int i = 0; i < n; i++) {
    ll sum = a[i];
    int cur = i;
    int len = 1;
    for(int j = 17; j >= 0; j--) {
      if(f[cur][j] == -1) continue;
      if(sum + sums[cur][j] - a[cur] <= S && len + (1 << j) <= L) {
        sum += sums[cur][j];
        sum -= a[cur];
        cur = f[cur][j];
        len += (1 << j);
      }
    }
    //cout << i + 1 << " " << cur + 1 << " " << sum << endl;
    to[i] = cur;
  }
  
  dfs(graph, -1, 0);
  dfs1(graph, -1, 0);

  cout << ans << endl;
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
