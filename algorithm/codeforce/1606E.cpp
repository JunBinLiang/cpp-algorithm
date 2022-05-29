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
    bool operator() (ve<ll>& a, ve<ll>& b)
    {
        return a[0] > b[0];
    }
    //a[0] > b[0] : min
};*/

bool COMP(const ve<int>& a, const ve<int>& b) {
  return a[0] < b[0];
}


int mod = 998244353;

ll fpow(ll x, int y){
	ll res = 1;
	while(y){
		if(y & 1) res = (res * x) % mod;
		x = (x * x) % mod;
		y >>= 1;
	}
	return res;
}

int c[600][600];
void init() {
    memset(c, 0, sizeof(c));
    c[0][0] = 1;
    for(int i = 1;i <= 510; i++) {
      c[i][0]=1;
      for(int j = 1;j <= i; j++) {
        c[i][j] = (c[i-1][j] + c[i-1][j-1] ) % mod;
      }
    }
  }

ll dp[510][510];
void solve() {
  int n, x;
  cin >> n >> x;
  init();
  memset(dp, 0, sizeof(dp));
  

  dp[n][0] = 1;
  for(int i = n; i > 1; i--) {
    for(int j = 0; j < x; j++) { //damage
      if(!dp[i][j]) continue;
      int to = min(x, (i - 1) + j);
      for(int k = 0; k <= i; k++) {//still alive
        int kill = (i - k);
        //kill people must has ability from [j + 1 : to]
        ll cnt = c[i][kill] * fpow((to - (j + 1) + 1) , kill);
        cnt %= mod;
        dp[k][to] += (dp[i][j] * cnt);
        dp[k][to] %= mod;
      }
    }
  }


  ll res = 0;
  for(int i = 0; i <= x; i++) {
    res += dp[0][i];
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
