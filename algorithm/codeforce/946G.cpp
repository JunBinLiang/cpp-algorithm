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
  return a[2] < b[2];
}

int MOD = 998244353;
int mod = 998244353;

int LIS(ve<int>& mxs, ve<int>& a) {
  int n = a.size();
  ve<int> dp(n + 1, 2000000000);
  int res = 0;
  FOR(i, 0, n) {
      int l = 1, r = n;
      int pos = -1;
      W(l <= r) {
          int mid = l + (r - l) / 2;
          if(a[i] < dp[mid]) {
              pos = mid;
              r = mid - 1;
          } else {
              l = mid + 1;
          }
      }
      if(i != n - 1) res = max(res, pos + 1);
      else res = max(res, pos);
      dp[pos] = a[i];
      mxs[i] = pos;
  }
  return res;
}


void solve() {
  int n;
  scanf("%d", &n);
  ve<int> a(n);
  ve<int> b(n);
  FOR(i, 0, n) {
    scanf("%d", &a[i]);
    b[i] = a[i] - i;
  }

  //cout << a.size() <<" " << b.size() << endl;

  ve<int> mxs1(n + 1);
  ve<int> mxs2(n + 1);
  ve<int> dp1(n + 1, -2000000000);
  ve<int> dp2(n + 1, 2000000000);
  int res = LIS(mxs1, b);
  
  for(int i = n - 1; i >= 0; i--) {
    int x = a[i] - i + 1;
    int l = 1, r = n, pos = - 1;
    W(l <= r) {
      int mid = l + (r - l) / 2;
      if(x > dp1[mid]) {
        pos = mid;
        r = mid - 1;
      } else {
        l = mid + 1;
      }
    }
    dp1[pos] = a[i] - i + 1;
    if(i != 0) res = max(res, pos + 1);
    else res = max(res, pos);
    mxs2[i] = pos;

    if(i - 2 >= 0) {
      int len1 = mxs1[i - 2];
      x = a[i - 2] - (i - 2);

      l = 1; r = n; pos = - 1;
      W(l <= r) {
        int mid = l + (r - l) / 2;
        if(x > dp1[mid]) {
          pos = mid;
          r = mid - 1;
        } else {
          l = mid + 1;
        }
      }
      res = max(res, pos + len1);
    }
  }
  cout << n - res << endl;
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
