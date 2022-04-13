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
ve<int> res;
int a[200000 + 100];
ll Hash1[200000 + 100];
ll Hash2[200000 + 100];
ll Pow[200000 + 100];
int Base = 23333;
int mod = 1000000007;

ll get(int left, int right) {
  if(left > right) return 0;
  if(left == 0) {
    return Hash1[right];
  }
  ll res = (Hash1[right] - (Hash1[left - 1] * Pow[right - left + 1] % mod) + mod) % mod;
  if(res < 0)res += mod;
  return res % mod;
}

void solve() {
  scanf("%d%d", &n, &m);
  FOR(i, 0, n) {
    scanf("%d", &a[i]);
  }

  ve<pair<int, int>> segs;
  if(a[0] != 0) segs.pb({0, a[0] - 1});
  FOR(i, 1, n) {
    if(a[i] != a[i - 1] + 1) {
      int l = a[i - 1] + 1, r = a[i] - 1;
      segs.pb({l, r});
    }
  }
  if(a[n - 1] != m - 1) {
    segs.pb({a[n - 1] + 1, m - 1});
  }
  

  ve<ve<int>> b;
  for(int i = 0; i < (int)(segs.size()); i++) {
    pair<int, int >& p = segs[i];
    int x = p.first, y = p.second;
    int ll = (x + a[0]) % m, rr = (y + a[0]) % m;
    if(ll <= rr) {
      b.pb({ll, rr});
    } else {
      b.pb({0, rr});
      b.pb({ll, m - 1});
    }
  }
  b.pb({-1, -1});
  b.pb({m, m});
  sort(b.begin(), b.end(), COMP);

  
  ve<int> candidates;
  for(int i = 1; i < (int)(b.size()); i++) {
    if(b[i][0] != b[i - 1][1] + 1) {
      int l = b[i - 1][1] + 1, r = b[i][0] - 1;
      for(int x = l; x <= r; x ++) {
        candidates.pb(x); 
      }
    }
  }

  Pow[0] = 1;
  FOR(i, 1, n + 1) {
    Pow[i] = Pow[i - 1] * Base;
    Pow[i] %= mod;
  }
  //hash the movement
  ll h1 = 0;
  for(int i = 1; i < n; i++) {
    int c = a[i] - a[i - 1];
    h1 = h1 * Base + c;
    h1 %= mod;
  }

 

  ve<int> dif;
  ll h2 = 0; 
  int j = 0;
  for(int i = candidates.size() - 1; i >= 0; i--) {
    int c = candidates[(i + 1) % candidates.size()] - candidates[i];
    c += m;
    c %= m;
    dif.pb(c);
    h2 = h2 * Base + c;
    h2 %= mod;
    Hash1[j++] = h2;
  }
  
  ll l = 0;
  j = dif.size() - 1;
  int p = 0;
  int SIZE = dif.size();
  for(int i = 0; i < (int)(dif.size()); i++) {
    ll r = get(0, SIZE - 2 - i);
    ll l = get(SIZE - i, SIZE - 1);
    l = l * Pow[SIZE - i - 1];
    l %= mod;
    if((l + r) % mod == h1) {
      res.pb(candidates[i]);
    }
  }

  printf("%d\n", res.size());
  for(int &i : res) {
    printf("%d ", i);
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
