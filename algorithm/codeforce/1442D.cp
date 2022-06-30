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

bool COMP(const pair<int, int>&p1, const pair<int, int>&p2) {
  return p1.second < p2.second;
}

struct Tuple {
  int a, b, c;
};


ve<ve<ll>> a;
int sizes[3005];
ll dp[3005];
int n, k;
ll res = 0;

void divide(int l, int r) {
  if(l == r) {
   // if(l == 2) cout << dp[1] << " " << dp[2] << " " << dp[3] << " " << dp[4] << " " << dp[5] << a[l] << endl;
    for(int i = 0; i < a[l].size(); i++) {
      if(k >= i + 1) {
        res = max(res, dp[k - (i + 1)] + a[l][i]);
      }
    }
    return;
  }
  
  int mid = l + (r - l) / 2;
  ll temp[3005];
  for(int i = 0; i <= k; i++) temp[i] = dp[i];
  for(int i = mid + 1; i <= r; i++) {
    ll x = a[i][sizes[i] - 1];
    for(int j = k; j >= sizes[i]; j--) {
      if(j >= sizes[i] && dp[j - sizes[i]] != -1 ) {
        dp[j] = max(dp[j], dp[j - sizes[i]] + x);
      }
    }
  }
  res = max(res, dp[k]);
  
  divide(l, mid);
  for(int i = 0; i <= k; i++) dp[i] = temp[i];

  for(int i = l; i <= mid; i++) {
    ll x = a[i][sizes[i] - 1];
    for(int j = k; j >= sizes[i]; j--) {
      if(j >= sizes[i] && dp[j - sizes[i]] != -1 ) {
        dp[j] = max(dp[j], dp[j - sizes[i]] + x);
      }
    }
  }
  res = max(res, dp[k]);
  divide(mid + 1, r);
}

void solve() {
  scanf("%d%d", &n, &k);
  for(int i = 0; i < n; i++) {
    int m;
    scanf("%d", &m);
    ve<ll> b(m);
    for(int j = 0; j < m; j++) {
      scanf("%lld", &b[j]);
      if(j > 0) b[j] += b[j - 1];
    }
    a.pb(b);
    sizes[i] = min(k, (int)(b.size()));
  }

  memset(dp, -1, sizeof(dp));
  dp[0] = 0;
  divide(0, n - 1);
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
