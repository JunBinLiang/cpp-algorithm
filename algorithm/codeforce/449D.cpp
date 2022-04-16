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


int mod = 1000000007;
int Pow[1000000 + 10];
ll dp[1000000 + 5];
void solve() {
  int n;
  scanf("%d", &n);
  memset(a, 0, sizeof(a));
  memset(dp, 0, sizeof(dp));
  FOR(i, 0, n) {
    int x;
    scanf("%d", &x);
    dp[x]++;
  }

  Pow[0] = 1;
  for(int i = 1; i <= 1000000 + 1; i++) {
    Pow[i] = Pow[i - 1] * 2;
    Pow[i] %= mod;
  }

  for(int i = 0; i < 20; i++) {
    for(int j = 0; j <= 1000000; j++) {
      if((j & (1 << i)) == 0) {
        int mask = j ^ (1 << i);
        if(mask <= 1000000) {
          dp[j] += dp[mask];
        }
      }
    }
  }

  ll res = Pow[n];
  for(int i = 1; i <= 1000000; i++) {
    ll sum = Pow[dp[i]];
    int cnt = 0;
    for(int j = 0; j < 20; j++) {
      if(j & (1 << i)) cnt++;
    }
    if(cnt % 2 == 0) {
      res += sum;
    } else {
      res -= sum;
    }
    res += mod;
    res %= mod;
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
