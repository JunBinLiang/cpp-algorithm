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
  if(p1.first == p2.first) {
    return p1.second < p2.second;
  }
  return p1.first < p2.first;
}

int a[150], b[150];
int mod = 1000000007;
int C[1001][1001];
ll dp[150][1001];
void solve() {
  int n;
  scanf("%d", &n);
  for(int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }

  for(int i = 0; i < n; i++) {
    scanf("%d", &b[i]);
  }
  C[0][0] = 1;
  for (int i = 1; i <= 1000; i++) {
    C[i][0] = C[i][i] = 1;
    for (int j = 1; j < i; j++)
      C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
  }


  
  int sum = a[0];
  memset(dp, 0, sizeof(dp));
  for(int i = 0; i <= a[0]; i++) {
    dp[0][i] = C[a[0]][i];
  }

  for(int i = 1; i < n; i++) {
    sum += a[i];
    for(int j = 0; j <= b[i]; j++) {
      for(int pre = 0; pre <= sum - a[i]; pre ++) {
        int have = pre + a[i];
        if(have >= j) {
          dp[i][have - j] += dp[i - 1][pre] * C[pre + a[i]][j];
          dp[i][have - j] %= mod;
          //cout << i << " " << (have - j) << " " << dp[i - 1][pre] << " " << C[pre + a[i]][j] << endl;
        }
      }
    } 
  }


  ll res = dp[n - 1][0];
  for(int i = 0; i < n; i++) {
    res = res * C[sum][a[i]];
    res %= mod;
    sum -= a[i];
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
