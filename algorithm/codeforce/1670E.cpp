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
    bool operator() (ve<ll>& a, ve<ll>& b)
    {
        return a[0] > b[0];
    }
    //a[0] > b[0] : min
};*/






int res1[300000 + 5];
int res2[300000 + 5];
int mid;
set<int> s1, s2;
void dfs(ve<ve<pair<int, int>>>& graph, int pa, int root, int val) {
  for(pair<int, int>& p : graph[root]) {
    if(p.second == pa) continue;
    int nxt = p.second, eIdx = p.first;
    int nxtV = -1;
    if(val == mid) {
      int b1 = *(s2.begin());
      s2.erase(b1);
      res2[eIdx] = b1;
      res1[nxt] = b1 - mid;
      s1.erase(b1 - mid);
      nxtV = 0;
    } else {
      int b1 = *(s1.begin());
      s1.erase(b1);
      res2[eIdx] = b1;
      res1[nxt] = b1 + mid;
      s2.erase(b1 + mid);
      nxtV = mid;
    }
    dfs(graph, root, nxt, nxtV);
  }
}

void solve() {
  int p; 
  scanf("%d", &p);
  int n = (1 << p);
  mid = n;
  ve<ve<pair<int, int>>> graph(n);
  for(int i = 0; i < n - 1; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--; v--;
    graph[u].pb({i, v});
    graph[v].pb({i, u});
  }
  
  for(int i = 1; i <= n - 1; i++) s1.insert(i);
  for(int i = n + 1; i <= 2 * n - 1; i++) s2.insert(i);

  dfs(graph, -1, 0, mid);
  res1[0] = mid;    
  printf("%d\n", 1);
  for(int i = 0; i < n; i++) {
    printf("%d ", res1[i]);
  }
  printf("\n");
  for(int i = 0; i < n - 1; i++) {
    printf("%d ", res2[i]);
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
