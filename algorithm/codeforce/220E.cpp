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

namespace Fenwick {
  const int SIZE = 100000 + 100;
  int tree[2][SIZE];
  void init() {
    FOR(i, 0, SIZE) {
      tree[0][i] = 0;
      tree[1][i] = 0;
    }
  }

  void update(int which, int i, int val) {
    i++;
    while(i < SIZE){
      tree[which][i] += val;
      i += (i & -i);
    }
  }

  int pre(int which, int i) {
    int sum = 0;
    while(i > 0){
      sum += tree[which][i];
      i -= ( i & -i);
    }
    return sum;
  }
  int query(int which, int i, int j) {
      return pre(which, j + 1) - pre(which, i);
  }
}


int a[100000 + 50];
map<int, int> f;

void solve() {
 int n;
 cin >> n;
 ll k;
 cin >> k;
 ve<int> b;
 FOR(i, 0, n) {
   scanf("%d", &a[i]);
   b.pb(a[i]);
 }

  sort(b.begin(), b.end());
  int id = 1;
  FOR(i, 0, n) {
    if(f.find(b[i]) == f.end()) {
      f[b[i]] = id++;
    }
  }

  ll res = 0;
  Fenwick :: init();

  ll total = 0;
  for(int i = n - 1; i >= 0; i--) {
    int ith = f[a[i]];
    int less = Fenwick :: query(0, 0, ith - 1);
    total += less;
    Fenwick :: update(0, ith, 1);
  }
  if(total <= k) {
    res += (n - 1);
  }

  //0 : right
  //1 : left
  int RIGHT = 100000 + 50;
  Fenwick :: update(0, f[a[0]], -1);
  total -= Fenwick :: query(0, 0, f[a[0]] - 1);
  Fenwick :: update(0, f[a[1]], -1);
  total -= Fenwick :: query(0, 0, f[a[1]] - 1);
  for(int i = 2, j = 0; i < n; i++) {
    int cur = a[i];
    W(total <= k && j + 1 < i) {
      int cnt1 = Fenwick :: query(0, 0, f[a[j]] - 1);
      int cnt2 = Fenwick :: query(1, f[a[j]] + 1, RIGHT);
      if(total + cnt1 + cnt2 > k) {
        break;
      }
      total += (cnt1 + cnt2);
      Fenwick :: update(1, f[a[j]], 1);
      j++;
    }
    res += (j);
    Fenwick :: update(0, f[a[i]], -1);
    total -= Fenwick :: query(0, 0, f[a[i]] - 1);
    total -= Fenwick :: query(1, f[a[i]] + 1, RIGHT);
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
