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
  return p1.second < p2.second;
}


int a[305][305];
int indexs[305];
int INF = 1000000000;
void solve() {
  int n, m, p;
  int res = 0;
  scanf("%d%d%d", &n, &m, &p);
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      scanf("%d", &a[i][j]);
    }
  }


  ve<ve<pair<int, int>>> all(p + 1);
  um<int, ve<pair<int, int>>> last1;
  um<int, ve<pair<int, int>>> last2;


  for(int i = 0; i < n; i++) {
    for(int j = 0; j < m; j++) {
      if(a[i][j] == 1) {
        last1[i].pb({j, i + j - j});
        last2[i].pb({j, i + j + j});
      } else {
        all[a[i][j]].pb({i, j});
      }
    }

    if(last1.find(i) != last1.end()) {
      ve<pair<int, int>>& rows1 = last1[i];
      for(int j = 1; j < rows1.size(); j++) {
        rows1[j].second = min(rows1[j].second, rows1[j - 1].second);
      }
      ve<pair<int, int>>& rows2 = last2[i];
      for(int j = rows2.size() - 2; j >= 0; j--) {
        rows2[j].second = min(rows2[j].second, rows2[j + 1].second);
      }
    } 
  }

  for(int i = 2; i <= p; i++) {
    ve<pair<int, int>>& b = all[i];
    sort(b.begin(), b.end(), COMP);
    ve<int> dp(b.size(), INF);
    
    memset(indexs, 0, sizeof(indexs));
    for(int j = 0; j < b.size(); j++) {
      pair<int, int>& p = b[j];
      int r = p.first, c = p.second;
      
      for(int R = 0; R < n; R++) {
        if(last1.find(R) == last1.end()) continue;
        int d1 = abs(R - r);
        ve<pair<int, int>>& rows = last1[R];
        W(indexs[R] < rows.size() && rows[indexs[R]].first <= c) {
          indexs[R]++;
        }
        if(indexs[R] > 0) {
          dp[j] = min(dp[j], d1 + c + rows[indexs[R] - 1].second);
        }
      }
    }

    for(int j = 0; j < 301; j++) {
      if(last2.find(j) != last2.end()) {
        indexs[j] = last2[j].size() - 1;
      }
    }
    

    for(int j = b.size() - 1; j >= 0; j--) {
      pair<int, int>& p = b[j];
      int r = p.first, c = p.second;
      for(int R = 0; R < n; R++) {
        if(last2.find(R) == last2.end()) continue;
        int d1 = abs(R - r);
        ve<pair<int, int>>& rows = last2[R];
        W(indexs[R] >= 0 && rows[indexs[R]].first >= c) {
          indexs[R]--;
        }
        if(indexs[R] + 1 < rows.size()) {
          dp[j] = min(dp[j], d1 - c + rows[indexs[R] + 1].second);
        }
      }
    }

    last1.clear();
    last2.clear();
    for(int j = 0; j < b.size(); j++) {
      pair<int, int>& p = b[j];
      int r = p.first, c = p.second;
      last1[r].pb({c, dp[j] - c});
      last2[r].pb({c, dp[j] + c});
    }

    for(auto it = last1.begin(); it != last1.end(); it++) {
      ve<pair<int, int>>& rows = it -> second;
      for(int j = 1; j < rows.size(); j++) {
        rows[j].second = min(rows[j].second, rows[j - 1].second);
      }
    }

    for(auto it = last2.begin(); it != last2.end(); it++) {
      ve<pair<int, int>>& rows = it -> second;
      for(int j = rows.size() - 2; j >= 0; j--) {
        rows[j].second = min(rows[j].second, rows[j + 1].second);
      }
    }
    
    if(i == p) {
      res = dp[0];
    }
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
