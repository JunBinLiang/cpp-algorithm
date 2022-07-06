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
  int l, r, idx;
};

bool COMP(pair<int, int>& p1, pair<int, int>& p2) {
  return p1.second < p2.second;
}


int a[5005];
bool is[5005][5005];
int dp[5005];
void solve() {
  int n; 
  scanf("%d", &n); 
  int res = 0; 
  for(int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    dp[i] = -1;
  }

  for(int i = 0; i < n; i++) {
    for(int j = i; j < n; j++) {
      is[i][j] = false;
    }
  }

  for(int i = 0; i < n; i++) {
    ve<int> cnt(n + 1);
    int mx = 0;
    for(int j = i; j < n; j ++) {
      cnt[a[j]]++;
      mx = max(mx, cnt[a[j]]);
      if((j - i + 1) % 2 == 0) {
        if(mx <= (j - i + 1) / 2) {
          is[i][j] = true;
        }
      }
    }
  }



  for(int i = 0; i < n; i++) {
    if(i == 0 || is[0][i - 1]) {
        dp[i] = 1;
    }
    for(int j = i - 1; j >= 0; j--) {
      if(a[i] == a[j]) {
        if(dp[j] != -1) {
          if(j + 1 == i || is[j + 1][i - 1]) {
            dp[i] = max(dp[i], 1 + dp[j]);
            //cout << j << " " << i << endl;
          }
        }
      }
    }
  }

  for(int i = 0; i < n; i++) {
    //cout << dp[i] << " ";
    if(i + 1 >= n || is[i + 1][n - 1]) {
      res = max(res, dp[i]);
    }
  }
  //cout << endl;


  printf("%d \n", res);
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
