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

const int MAX = 1000000 + 10;


int dp[1000000 + 5][2];
char s[1000000 + 5];
ve<int> a[1000000 + 5];
int f[1000000 + 5];

int find(int x){
  if(f[x] == x) return x;
  int root = find(f[x]);
  f[x] = root;
  return root;
}

void solve() {
  int n; 
  scanf("%d%s",&n, s);
  
  dp[n][0] = dp[n][1] = 0;
  for(int i = n - 1; i >= 0; i--) {
    if(s[i] == '?') {
      dp[i][0] = 1 + dp[i + 1][0];
      dp[i][1] = 1 + dp[i + 1][1];
    } else if(s[i] == '0') {
      dp[i][1] = 0;
      dp[i][0] = 1 + dp[i + 1][0];
    } else {
      dp[i][0] = 0;
      dp[i][1] = 1 + dp[i + 1][1];
    }
    int mx = max(dp[i][0], dp[i][1]);
    f[i] = i;
    a[mx].pb(i);
  }
  f[n] = n;

  for(int i = 1; i <= n; i++) {
    int res = 0;
    int j = 0;
    W(j < n) {
      int nxt = find(j);
      if(nxt >= n) break;
      res++;
      j = nxt + i;
    }
    
    for(int id : a[i]) {
      f[id] = id + 1;
    }

    printf("%d ", res);
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
