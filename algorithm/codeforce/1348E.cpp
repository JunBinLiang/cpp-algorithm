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
  return p1.second < p2.second;
}




void solve() {
  int n, k;
  scanf("%d%d", &n, &k);

  ll s1 = 0, s2 = 0;
  ll dp[500];
  memset(dp, -1, sizeof(dp));
  dp[0] = 0;
  for(int i = 0; i < n; i ++) {
    int x, y;
    scanf("%d%d", &x, &y);
    ll cur[500];
    memset(cur, -1, sizeof(cur));
    for(int lastr = 0; lastr < k; lastr ++) {
      if(dp[lastr] == -1) continue;
      ll user = s1 - lastr;
      ll b = s2 - (dp[lastr] * k - user);
      for(int red = 0; red < k; red ++) {
        if(lastr + x >= red) {
          int to = lastr + x - red;
          int m = to % k;
          if(m == 0 || (m <= x && (m + y) >= k)) {;
            cur[red] = max(cur[red], dp[lastr] + (to / k) + (m + y + b) / k);
          }
        } else {
            break;
        }
      }
    }
    s1 += x;
    s2 += y;
    for(int j = 0; j < k; j++) {
      dp[j] = cur[j];
    }
  }

  ll res = 0;
  for(int i = 0; i < k; i++) {
    res = max(res, dp[i]);
  }
  printf("%lld", res);
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
