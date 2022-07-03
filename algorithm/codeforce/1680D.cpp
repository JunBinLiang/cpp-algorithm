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

ll get(ve<ll>& a, int l, int r) {
  if(l == 0) return a[r];
  return a[r] - a[l - 1];
}

int a[3000 + 5];
ve<ll> cnts(3005);
ve<ll> sums(3005);
void solve() {
  int n, k;
  scanf("%d%d", &n, &k);
  for(int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    sums[i] = a[i];
    cnts[i] = (a[i] == 0);
    if(i) {
      sums[i] += sums[i - 1];
      cnts[i] += cnts[i - 1];
    }
  }

  if(cnts[n - 1] * k < abs(sums[n - 1])) {
    cout << -1 << endl;
    return;
  }

  ll res = 0;
  for(int i = 0; i < n; i++) {
    for(int j = i; j < n; j++) {
      ll lcnt = get(cnts, i, j), rcnt = cnts[n - 1] - lcnt;
      ll lsum = get(sums, i, j), rsum = sums[n - 1] - lsum;
      res = max(res, min(abs(lsum + lcnt * k), abs(rsum - k * rcnt)));
      res = max(res, min(abs(lsum - lcnt * k), abs(rsum + k * rcnt)));
    }
  }
  cout << res + 1 << endl;
}

//1 -1 (-1) 2 -2 3

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
