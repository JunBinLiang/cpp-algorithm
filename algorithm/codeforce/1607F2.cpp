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
    bool operator() (ve<ll>& a, ve<ll>& b)
    {
        return a[0] > b[0];
    }
    //a[0] > b[0] : min
};*/


int n, m;
int dis[4000000 + 5];
int status[4000000 + 5];
int sta[4000000 + 5];
int color = 5;
int idx = 0;
ve<string> a;

int Next(int root) {
  int i = root / m, j = root % m;
   int r = i, c = j;
  if(a[i][j] == 'L') {
      c--;
  }
  if(a[i][j] == 'R') {
    c++;
  }
  if(a[i][j] == 'D') {
    r++;
  }
  if(a[i][j] == 'U') {
    r--;
  }

  if(r < 0 || r >= n || c < 0 || c >= m) {
    return -1;
  } else {
    return r * m + c;
  }
}

void dfs(int root) {
  int son = Next(root);
  if(son == -1) {
    dis[root] = 1;
    return;
  }

  if(dis[son] != 0) {
    dis[root] = 1 + dis[son];
  } else {
    if(status[son] == 0) {
      status[son] = 1;
      sta[idx++] = son;
      dfs(son);
      if(status[son] > 1) {
        if(status[root] != status[son]) {
            dis[root] = 1 + dis[son];
            idx--;
        }
        
      } else {
        dis[root] = 1 + dis[son];
        idx--;  
      }
    } else {
      //cycle
      int cnt = 0;
      int j = idx;
      W(sta[j - 1] != son) {
        cnt++;
        j--;
      }

      W(sta[idx - 1] != son) {
        int e = sta[idx - 1];
        dis[e] = cnt + 1;
        status[e] = color;
        idx--;
      }
      status[son] = color;
      dis[son] = cnt + 1;
      color++;
    }
  }
}


void solve() {
  scanf("%d%d", &n, &m);
  a.clear();
  for(int i = 0; i < n; i++) {
    string s;
    cin >> s;
    a.pb(s);
  }

  for(int i = 0; i < n * m; i++) {
    dis[i] = 0;
    status[i] = 0;
  }


  for(int i = 0; i < n * m; i++) {
    if(dis[i] == 0) {
      idx = 0;
      status[i] = 1;
      sta[idx++] = i;
      dfs(i);
    }
  }

  int res = -1, x = -1, y = -1;
  for(int i = 0; i < n * m; i++) {
    if(dis[i] > res) {
      res = dis[i];
      x = i / m;
      y = i % m;
    }
  }
  printf("%d %d %d \n", x + 1, y + 1, res);
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
