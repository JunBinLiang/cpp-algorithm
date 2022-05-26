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
ll cnt[200000 + 5];
int pa[200000 + 5];
bool seen[200000 + 5];
int dfs(ve<ve<int>>& graph, int p, int root) {
  cnt[root] = 1;
  pa[root] = p;
  for(int& nxt : graph[root]) {
    if(nxt == p)continue;
    cnt[root] += dfs(graph, root, nxt);
  }
  return cnt[root];
}

void solve() {
  
  int n;
  scanf("%d", &n);
  ve<ve<int>> graph(n);
  ve<ll> res(n + 1);
  for(int i = 0; i < n - 1; i ++) {
    int u, v;
    scanf("%d%d", &u, &v);
    graph[u].pb(v);
    graph[v].pb(u);
  }

  for(int i = 0; i <= n; i++) {
    seen[i] = false;
  }
  dfs(graph, - 1, 0);

  ll sum = n;
  int l = 0, r = 0;
  seen[0] = true;

  for(int MEX = 1; MEX <= n ; MEX++) {
    if(seen[MEX]) {
      continue;
    }

    if(MEX == n) {
      res[MEX] = 1;
      break;
    }

    int cur = MEX, pre = -1, step = 0;
    W(!seen[cur]) {
      seen[cur] = true;
      pre = cur;
      cur = pa[cur];
      step ++;
    }

    if(cur == l || cur == r) {
      if(l == 0 && r == 0) {
        sum -= (cnt[pre] + 1);
        ve<int> a;
        ll all = 0;
        for(int nxt : graph[0]) {
            if(nxt == pre) {
                a.pb(cnt[nxt] - cnt[MEX]);
            } else {
                a.pb(cnt[nxt]);
            }
        }
        
        for(int x : a) all += x;
        res[MEX] += all;
        for(int x : a) {
            all -= x;
            res[MEX] += (x * all);
        }
        
        
        l = MEX;
      } else {
        if(r == 0) {
          if(cur == l) {
            res[MEX] = (cnt[l] - cnt[MEX]) * (sum + 1);
            l = MEX;
          } else {
            res[MEX] = (sum + 1 - cnt[MEX]) * cnt[l];
            r = MEX;
          }
        } else {
          if(cur == l) {
            res[MEX] = cnt[r] * (cnt[l] - cnt[MEX]);
            l = MEX;
          } else {
            res[MEX] = cnt[l] * (cnt[r] - cnt[MEX]);
            r = MEX;
          }
        }
      }
    } else {
      if(r == 0) {
        res[MEX] = cnt[l] * (sum + 1);
      } else {
        res[MEX] = cnt[l] * cnt[r];
      }
      break;
    }
    
  }


  for(int nxt : graph[0]) {
    ll x = cnt[nxt];
    res[0] += (x * (x - 1) / 2);
  }
  for(ll &i : res) {
    printf("%lld ", i);
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
