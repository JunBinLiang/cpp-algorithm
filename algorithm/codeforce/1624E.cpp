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
  int l, r, i;
};

void solve() {
  int n, m;
  cin >> n >> m;
  ve<string> a(n);
  for(int i = 0; i < n; i++) {
    cin >> a[i];
  }

  string s;
  cin >> s;

  um<string, pair<int, int>> f; //2
  um<string, pair<int, int>> g; // 3
  for(int i = 0; i < a.size(); i++) {
    for(int j = 1; j < a[i].size(); j++) {
      string t = "";
      t += a[i][j - 1]; t += a[i][j];
      if(f.find(t) == f.end()) {
        f[t] = {j, i};
      }
    }
  } 

  for(int i = 0; i < a.size(); i++) {
    for(int j = 2; j < a[i].size(); j++) {
      string t = "";
      t += a[i][j - 2]; 
      t += a[i][j - 1];
      t += a[i][j];
      if(g.find(t) == g.end()) {
        g[t] = {j, i};
      }
    }
  } 

  
  ve<int> dp(m + 1, -1);
  dp[0] = 0;
  for(int i = 1; i < m; i++) {
    string t1 = "";
    t1 += s[i - 1]; t1 += s[i];
    if(f.find(t1) != f.end() && dp[i + 1 - 2] != -1) {
      dp[i + 1] = 2;
    }

    if(i > 1) {
      string t2 = "";
      t2 += s[i - 2]; t2 += s[i - 1]; t2 += s[i];
      if(g.find(t2) != g.end() && dp[i + 1 - 3] != -1) {
        dp[i + 1] = 3;
      }
    }
  }

  

  if(dp[m] == -1) {
    printf("-1 \n");
    return;
  } 

  int last = m;
  ve<Tuple> res;
  W(last > 0) {
    int cnt = dp[last];
    string sub = substring(s, last - cnt, last - 1);
    if(cnt == 2) {
      pair<int, int> p = f[sub];
      res.pb({p.first - cnt + 1, p.first, p.second});
    } else {
      pair<int, int> p = g[sub];
      res.pb({p.first - cnt + 1, p.first, p.second});
    }
    last -= cnt;
  }

  reverse(res.begin(), res.end());
  printf("%d \n", res.size());
  for(int i = 0; i < res.size(); i++) {
    printf("%d %d %d \n", res[i].l + 1, res[i].r + 1, res[i].i + 1);
  }
  
}

int main()
{

  int t = 1;
  cin >> t;
  W (t--)
  {
    solve();
  }
  return 0;
}
