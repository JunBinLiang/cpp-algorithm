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

bool COMP(const ve<pair<int, int>>& a, const ve<pair<int, int>>& b) {
  return a[0].first > b[0].first;
}


void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  ve<ve<pair<int, int>>> a(n, ve<pair<int, int>>(m));
  
  ve<ve<int>> mins(n, ve<int>(m, 0));
  ve<ve<int>> maxs(n, ve<int>(m, 0));


  ve<ve<int>> mins1(n, ve<int>(m, 0));
  ve<ve<int>> maxs1(n, ve<int>(m, 0));

  FOR(i, 0, n) {
    FOR(j, 0, m) {
      int x;
      scanf("%d", &x);
      a[i][j] = {x, i};
    }
  }
  sort(a.begin(), a.end(), COMP);

  for(int i = 0; i < m; i++) {
    int mn = 1000000000, mx = -1000000000;
    for(int row = n - 1; row >= 0; row--) {
      mn = min(mn, a[row][i].first);
      mx = max(mx, a[row][i].first);
      mins[row][i] = mn;
      maxs[row][i] = mx;
    }
  }

  for(int i = 0; i < m; i++) {
    int mn = 1000000000, mx = -1000000000;
    for(int row = 0; row < n; row++) {
      mn = min(mn, a[row][i].first);
      mx = max(mx, a[row][i].first);
      mins1[row][i] = mn;
      maxs1[row][i] = mx;
    }
  }

  string s = "";
  for(int i = 0; i < n; i++) {
    s += "B";
  }


  for(int i = 0; i < n - 1; i++) {
    int realRow = a[i][0].second;
    s[realRow] = 'R';
    ve<bool> right(m, false);
    int mx = -1000000000, mn = 1000000000;
    for(int j = m - 1; j >= 0; j--) {
      mx = max(mx, maxs1[i][j]);
      mn = min(mn, mins[i + 1][j]);
      if(mx < mn) {
        right[j] = true;
      } else {
        break;
      }
    }

    mx = -1000000000; mn = 1000000000;
    for(int j = 0; j < m - 1; j++) {
      mx = max(mx, maxs[i + 1][j]);
      mn = min(mn, mins1[i][j]);
      if(mx >= mn) {
        break;
      }
      if(right[j + 1]) {
        cout << "YES " << endl;
        cout << s << " " << j + 1 << endl;  
        return;
      }
    }
  }
  cout << "NO" << endl;

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
