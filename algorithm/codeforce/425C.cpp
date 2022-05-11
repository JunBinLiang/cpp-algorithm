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

/*class Compare
{
public:
    bool operator() (ve<ll>& a, ve<ll>& b)
    {
        return a[0] > b[0];
    }
    //a[0] > b[0] : min
};*/


bool COMP(pair<int, int>& p1, pair<int, int>& p2) {
  return p1.first < p2.first;
}

int dp[100000 + 5][320];
void solve() {
  int n, m, s, e;
  cin >> n >> m >> s >> e;
  ve<int> a(n), b(m);
  int res = 0;
  for(int i = 0; i < n; i++) {
    cin >> a[i];
  }

  um<int, ve<int>> f;
  for(int i = 0; i < m; i++) {
    int x;
    cin >> x;
    f[x].pb(i);
  }

  int INF = 10000000;
  for(int i = 0; i <= n; i++) {
    for(int j = 0; j < 320; j++) {
      dp[i][j] = INF;
    }
    dp[i][0] = -1;
  } 

  


  
  for(int i = 0; i < a.size(); i++) {
    if(f.find(a[i]) == f.end()) {
      for(int j = 1; j < 320; j++) {
        dp[i + 1][j] = dp[i][j];
      }
    } else {
      ve<int>& b = f[a[i]];
      for(int j = 1; j < 320; j++) {
        int l = 0, r = b.size() - 1;
        int bound = dp[i][j - 1];
        ll pos = -1;
        W(l <= r) {
          int mid = l + (r - l) / 2;
          if(b[mid] > bound) {
            pos = mid;
            r = mid - 1;
          } else {
            l = mid + 1;
          }
        }
        dp[i + 1][j] = dp[i][j];
        if(pos != -1) {
          dp[i + 1][j] = min(dp[i + 1][j], b[pos]);
        }
        if((j + 0ll) * e + (i + 1) + (dp[i + 1][j] + 1) <= s) {
          res = max(res, j);
        }
      }
    }
  }
  cout << res << endl;
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
