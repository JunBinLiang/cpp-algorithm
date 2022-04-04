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
int mod = 998244353;

namespace Fenwick {
  const int SIZE = 400000 + 100;
  int tree[3][SIZE];
  void init(int n) {
    FOR(i, 0, n + 5) {
      tree[0][i] = 0;
      tree[1][i] = 0;
      tree[2][i] = 0;
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



int a[200000 + 100];
void solve() {
  int n;
  scanf("%i", &n);
  string s;
  cin >> s;
  FOR(i, 0, s.size()) {
    if(s[i] == '+') a[i] = -1;
    else a[i] = 1;
  }

  Fenwick :: init(n + n + 10);
  int OFFSET = n;
  ll res = 0;
  int sum = 0;
  int m = 0;
  FOR(i, 0, n) {
    sum += a[i];
    m += a[i];
    if(m < 0) m += 3;
    m %= 3;
    if(m == 0 && sum >= 0) res++;
    int which = m;
    res += Fenwick :: query(which, 0, sum + OFFSET);
    Fenwick :: update(which, sum + OFFSET, 1);

   // cout << sum << " " << m <<" " << res << endl;
  }
  cout <<  res << endl;
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
