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

class Compare
{
public:
    bool operator() (ve<int>& a, ve<int>& b)
    {
        return a[0] > b[0];
    }
};

namespace Fenwick {
  const int SIZE = 3000 + 100;
  int tree[SIZE];
  void init() {
    memset(tree, 0, sizeof(tree));
  }
  void update(int i, int val) {
    i++;
    while(i < SIZE){
      tree[i] += val;
      i += (i & -i);
    }
  }

  int pre(int i) {
    int sum = 0;
    while(i>0){
      sum += tree[i];
      i -= ( i & -i);
    }
    return sum;
  }
  int query(int i, int j) {
      return pre(j + 1) - pre(i);
  }
}

int r[3001][3001];
int l[3001][3001];
bool seen[3001][3001];
void solve() {
  int n, m;
  cin >> n >> m;
  ve<string> a(n);
  for(int i = 0; i < n; i++) {
    cin >> a[i];
  }

  for(int i = 0; i < n; i++) {
    int sum = 0;
    for(int j = m - 1; j >= 0; j--) {
      if(a[i][j] == 'z') sum ++;
      else sum = 0;
      r[i][j] = sum;
    }
  }

  for(int i = 0; i < n; i++) {
    int sum = 0;
    for(int j = 0; j < m; j++) {
      if(a[i][j] == 'z') sum ++;
      else sum = 0;
      l[i][j] = sum;
    }
  }

  Fenwick :: init();

  memset(seen, false, sizeof(seen));
  ll res = 0;
  for(int i = n - 1; i >= 0; i--) {
    for(int j = m - 1; j >= 0; j--) {
      if(seen[i][j]) continue;
      //do diagnal
      int row = i, col = j, sum = 0;
      priority_queue<ve<int>, ve<ve<int>>, Compare> pq;
      W(row >= 0 && col < m) {
        seen[row][col] = true;
        if(a[row][col] != 'z') {
          sum = 0;
          //clear
          W(pq.size() > 0) {
            ve<int> v = pq.top(); pq.pop();
            Fenwick :: update(v[1], -1);
          }
          
        } else {
          sum++;
          int mn = min(sum, l[row][col]);
          int extend = r[row][col] + col - 1;
          pq.push({extend, row});
          Fenwick :: update(row, 1);
          W(pq.size() > 0) {
            ve<int> v = pq.top();
            if(v[0] < col) {
              Fenwick :: update(v[1], -1);
              pq.pop();
            } else {
              break;
            }
          }
          int cnt = Fenwick :: query(row, row + mn - 1);
          res += cnt;
        }
        row--;
        col++;
      }
      //clear
      W(pq.size() > 0) {
        ve<int> v = pq.top(); pq.pop();
        Fenwick :: update(v[1], -1);
      }
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
