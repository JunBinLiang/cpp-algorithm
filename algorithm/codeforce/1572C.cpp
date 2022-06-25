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


int a[3005];
int dp[3005][3005];
ve<int> pos[3005];
void solve() {
  int n;
  scanf("%d", &n);
  for(int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    pos[a[i]].pb(i);
  }

  int INF = 1000000000;
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      dp[i][j] = INF;
    }
  }

  for(int i = 0; i < n; i++) {
    int j = i;
    W(j < n && a[j] == a[i]) {
      j++;
    }
    
    /*for(int x = i; x < j; x++) {
        for(int y = x; y < j; y++) {
            dp[x][y] = 0;
        }
    }*/
    i = j - 1;
  }

  for(int l = n - 1; l >= 0; l--) {
    for(int r = l; r < n; r++) {
      if(l == r) {
          dp[l][r] = 0;
          continue;
      }
      for(int x : pos[a[l]]) {
        if(x >= l && x <= r) {
          if(x == r) {
            dp[l][r] = min(dp[l][r], dp[l][r - 1]);
            continue;
          }    
            
          int add = 0;
          if(a[l] != a[x + 1]) add = 1;
          dp[l][r] = min(dp[l][r], dp[l][x] + dp[x + 1][r] + add);
        }
      }
      //cout << l << " " << r <<"      " << dp[l][r] <<  endl;
    }

  }
  
  /*for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      cout << dp[i][j] << " ";
    }cout << endl;
  }*/
  
  
  printf("%d \n", dp[0][n - 1]);
  for(int i = 0; i <= n; i++) pos[i].clear();
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
