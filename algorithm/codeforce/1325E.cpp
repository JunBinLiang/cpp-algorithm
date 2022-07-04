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


struct Tuple {
  int l, r, idx;
};



int INF = 1000000000;
int a[100000 + 5];
ve<int> primes[1000000 + 5];
ve<int> graph[1000000 + 5];
bool is[1000000 + 5];
int res = INF;
int dis[1000000 + 5];
void bfs(int s) {
  memset(dis, -1, sizeof(dis));
  dis[s] = 0;
  queue<pair<int, int>> q;
  q.push({-1, s});
  W(q.size() > 0) {
    pair<int, int> p = q.front(); q.pop();
    int pa = p.first, root = p.second;
    for(int& nxt : graph[root]) {
      if(nxt == pa) continue;
      if(dis[nxt] != -1) {
        res = min(res, dis[nxt] + dis[root] + 1);
        return;
      }
      dis[nxt] = 1 + dis[root];
      q.push({root, nxt});
    }
  }
}


void solve() {
  int n;
  scanf("%d", &n);
  for(int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }

  for(int i = 2; i <= 1000000; i++) {
    int x = i;
    for(int j = 2; j * j <= x; j++) {
        if(x % j == 0) {
            int cnt = 0;
            W(x % j == 0)  {
                x /= j; cnt++;
            }
            if(cnt % 2 == 1) primes[i].pb(j);
        }
    }
    if(x != 1) primes[i].pb(x);
  }

  bool check = false;
  for(int i = 0; i < n; i++) {
    if(primes[a[i]].size() == 0 || a[i] == 1) {
      printf("1 \n");
      return;
    }
    if(is[a[i]]) {
      check = true;
    }
    is[a[i]] = true;
  }
  if(check) {
    printf("2 \n");
    return;
  }
  
  for(int i = 0; i < n; i++) {
    ve<int>&p = primes[a[i]];
    if(p.size() == 1) {
      int u = p[0];
      graph[1].pb(u);
      graph[u].pb(1);
    } else {
      int u = p[0], v = p[1];
      graph[u].pb(v);
      graph[v].pb(u);
    }
  }
  
  
  for(int i = 1; i <= 1000; i++) {
    bfs(i);
  }

  if(res == INF) cout << -1 << endl;
  else cout << res << endl;
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
