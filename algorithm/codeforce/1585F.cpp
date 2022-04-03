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



int a[200000 + 100];
ll pre[200000 + 100];
ll sums[200000 + 100];
ll dp[200000 + 100];
ll get(int l, int r) {
  if(l > r) return 0;
  if(l == 0) return pre[r];
  return (pre[r] - pre[l - 1] + mod ) % mod;
}


void solve() {
  int n;
  scanf("%d", &n);
  FOR(i, 1, n + 1) {
    scanf("%d", &a[i]);
  }
  memset(pre, 0, sizeof(pre));
  ve<int> st;
  dp[0] = 1;
  pre[0] = -1;
  pre[0] += mod;
  sums[0] = 1;

  FOR(i, 1, n + 1) {
    dp[i] = dp[i - 1] * a[i];
    dp[i] %= mod;
    W(st.size() > 0 && a[i] <= a[st[st.size() - 1]]) {
      st.pop_back();
    }
    if(st.size() == 0) {
      ll x = 0;
      if(i % 2 == 1) {
        if(i - 2 >= 0) x =  -pre[i - 2];
        x += mod;
        x %= mod;
      } else {
        if(i - 2 >= 0) x =  ((pre[i - 2]));
        x %= mod;
      }
      x *= a[i];
      x %= mod;
      dp[i] += x;
      dp[i] += mod;
      dp[i] %= mod;
      sums[i] = x;
      
    } else {
      ll x = 0;
      int index = st[st.size() - 1];
      ll sum = get(index, i - 2);
      ll y = (dp[index - 1]) * (a[index]);
      int cnt = i - index - 1;
      if(cnt % 2 == 0) {
        y = -y;
        y += mod;
        y %= mod;
        
        x = -sums[index];
        x += mod;
        x %= mod;
      } else {
      

         x = sums[index];
      }
      y %= mod;

      if(i % 2 == 1) {
        sum = -sum;
        sum += mod; 
        sum %= mod;
      } else {

      }
      sum *= a[i];
      sum %= mod;

      x += y;
      x %= mod;
      x += sum;
      x %= mod;


      dp[i] += x;
      dp[i] += mod;
      dp[i] %= mod;
      sums[i] = x;
    }

    st.pb(i);
    if(i % 2 == 1) {
      pre[i] += dp[i];
    } else {
      pre[i] -= dp[i];
    }
    pre[i] += mod;
    pre[i] %= mod;
    pre[i] += pre[i - 1];
    pre[i] %= mod;
  }

  cout << dp[n] << endl;
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
