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




int n, m;
int a[1000000 + 5];
ve<ll> all[1000000 + 5];
ve<ll> pref[1000000 + 5];

int find(int root, ll add, ll x) {
  if(root > n) return -1;
  ve<ll>& c = all[root];
  int l = 0, r = c.size() - 1;
  int pos = -1;
  W(l <= r) {
    int mid = l + (r - l) / 2;
    if(add + c[mid] <= x) {
      pos = mid;
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  return pos;
}

void solve() {
  scanf("%d%d", &n, &m);
  for(int i = 1; i <= n - 1; i++) {
    scanf("%d", &a[i]);
  }
  for(int i = 1; i <= n; i++) {
    int u = i;
    ll add = 0;
    W(u != 1) {
      add += a[u - 1];
      u /= 2;
      all[u].pb(add);
    }
  }

  for(int i = 1; i <= n; i++) {
    all[i].pb(0);
    sort(all[i].begin(), all[i].end());
    ve<ll>& b = all[i];
    ll sum = 0;
    for(int j = 0; j < b.size(); j++) {
      sum += b[j];
      pref[i].pb(sum);
    }
  }




  W(m--) {
    int u, h;
    scanf("%d%d", &u, &h);
    ll res = 0, add = 0;
    int pre = -1;
    W(true) {
      if(pre == -1) {
        int pos = find(u, add, h);
        if(pos != -1) {
          res += ((h + 0ll) * (pos + 1ll) - pref[u][pos]);
        }

      } else {
        int nxt = -1;
        if(u * 2 == pre) {
          nxt = u * 2 + 1;
        } else {
          nxt = u * 2;
        }
        ll pos = find(nxt, add + a[nxt - 1], h);
        if(pos != -1) {
          res += ((h - add - a[nxt - 1]) * (pos + 1) - pref[nxt][pos]);
        }
        if(add <= h) {
          res += (h - add);
        }
      }
      
      if(u == 1) break;
      add += a[u - 1];
      if(h - add < 0) break;
      pre = u;
      u /= 2;
    }
    printf("%lld\n", res);
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
