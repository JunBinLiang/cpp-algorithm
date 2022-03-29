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
#define RFOR(i, a, b) for (int i = a; i >= b; i--)
#define W while
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

namespace Combination {
  int mod = 998244353;
  ll fact[1000000 + 100];
  ll inv[1000000 + 100];
  int c[505][505];
  ll modInverse(ll a, ll m) {
      ll m0 = m;
      ll y = 0, x = 1;
      if (m == 1)
          return 0;
      while (a > 1) {
          // q is quotient
          ll q = a / m;
          ll t = m;
          // m is remainder now, process
          // same as Euclid's algo
          m = a % m;
          a = t;
          t = y;
          // Update x and y
          y = x - q * y;
          x = t;
      }
      // Make x positive
      if (x < 0)
          x += m0;
      return x;
  }

  ll Pow(ll a, ll b, ll mo){
    ll ans=1;
    for(;b;b>>=1) {
      if(b&1) ans = 1ll *a * ans % mo;
      a = 1ll * a * a % mo;
    }
	  return ans;
  }

  ll C(int n,int m) {
      return fact[n] * Pow(fact[n-m], mod - 2, mod) % mod * Pow (fact[m], mod - 2, mod) % mod;
  }

  void init() {
    fact[0] = 1;
    FOR(i, 1, 1000000 + 50) {
      fact[i] = fact[i - 1] * i;
      fact[i] %= mod;
    }

    inv[0] = inv[1]=1;
    for (int i=2;i < 1000000 + 50;i++){
        inv[i] = modInverse(i,mod) * inv[i-1];
        inv[i] %= mod;
    }

    c[0][0] = 1;
    for(int i = 1;i <= 500; i++) {
      c[i][0]=1;
      for(int j = 1;j <= i;j++) {
        c[i][j] = ( c[i-1][j] + c[i-1][j-1] ) % mod;
      }
    }
  }
}


ll dp[500][500];
void solve(int n, int k) {
    //minimum spanning tree == sum incident to 1
  Combination :: init();
  memset(dp, 0, sizeof(dp));

  dp[0][0] = 1;
  FOR(i, 1, k + 1) {// maximum weight
    FOR(ver, 0, n) {
      FOR(j, 0, ver + 1) {
        //add j vertexs
        //Combination :: c[ver][j]
        ll connect = j * (j - 1) / 2 + j * (ver - j);
        dp[i][ver] = dp[i][ver] + (((dp[i - 1][ver - j]) * Combination :: c[n - 1 -  (ver - j)][j]) % mod) 
          * Combination::Pow(k - i + 1, connect, mod); 
        dp[i][ver] %= mod;
      }
    }
  } 
  cout << dp[k][n - 1] << endl;

}




int main()
{
  int t = 1;
  //cin >> t;
  W (t--)
  {
    int n, k;
    cin >> n >> k;
    solve(n, k);
  }
  return 0;
}
