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
#define str string

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
  return false;
}

int MOD = 998244353;
int mod = 1000000007;

int a[100000 + 100];
int Next[100000 + 100];
int Pre[100000 + 100];
int Skip[100000 + 100];
int k;

int link[2000];

void update(int u) {
  int cur = u;  
  link[0] = u;
  FOR(i, 1, k + 1) {
    cur = Next[cur];
    link[i] = cur;
  }
  int j = k; cur = u;
  while(j >= 0) {
    Skip[cur] = link[j];
    cur = Pre[cur];
    j--;
  }
}

int query(int u, int m) {
  W(m >= k) {
    m -= k;
    u = Skip[u];
  }
  W(m--) {
    u = Next[u];
  }
  return u;
}


void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  FOR(i, 1, n + 1) {
    scanf("%d", &a[i]);
  }
  k = (int)(sqrt(n));

  FOR(i, 1, n + 1) {
    Next[i] = a[i];
    Pre[a[i]] = i;
  }

  FOR(i, 1, n + 1) {
    int cur = i;
    FOR(j, 0, k) {
      cur = Next[cur];
    }
    Skip[i] = cur;
  }

  FOR(i, 0, m) {
    int op, x, y;
    scanf("%d%d%d", &op, &x, &y);
    if(op == 1) { //swap
      int pre1 = Pre[a[x]];
      int pre2 = Pre[a[y]];
      Next[pre1] = a[y];
      Next[pre2] = a[x];
      Pre[a[x]] = pre2;
      Pre[a[y]] = pre1;
      //print();
      update(a[x]);
      update(a[y]);
      swap(a[x], a[y]);
    } else {
      int p = query(x, y);
      printf("%d\n", p);
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
