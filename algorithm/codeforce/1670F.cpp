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
  int a, b, c;
};

bool is[65];
ll mod = 1000000007;
ll C[1210][1210];
ll dp[63][4100];
ll cnt[63][1005];
int n;
ll l, r, z;

void init() {
  C[0][0] = 1;
  for(int i = 1; i <= 1200; i++) {
    C[i][0]=1;
    for(int j = 1; j <= i; j++) {
      C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % mod;
    }
  }
}


ll dfs(ll num, int i, int all) {
  if(i < 0) {
    return 1;
  }
  if(dp[i][all] != -1) return dp[i][all];
  int bit = 0;
  if((num & (1ll << i)) > 0) bit = 1;
  int alll = all + bit;
  ll res = 0;
  if(is[i]) {
    for(int j = 1; j <= min(alll, n); j += 2) {
      res += (C[n][j] * dfs(num, i - 1, min((alll - j) * 2, 4000)));
      res %= mod;
    }
  } else {
    for(int j = 0; j <= min(alll, n); j += 2) {
      res += (C[n][j] * dfs(num, i - 1, min((alll - j) * 2, 4000)));
      res %= mod;
    }
  }
  res %= mod;
  return dp[i][all] = res;
}

ll cal(ll num) {
  memset(dp, -1, sizeof(dp));
  ll res = dfs(num, 62, 0);
  return res;
}

void solve() {
  cin >> n >> l >> r >> z;
  memset(is, false, sizeof(is));
  for(int i = 0; i < 63; i++) {
    if(z & (1ll << i)) {
      is[i] = true;
    }
  }
  init();
  ll x = cal(l - 1);
  ll y = cal(r);
  cout << (y - x + mod) % mod << endl;
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
