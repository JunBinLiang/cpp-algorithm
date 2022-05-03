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
  return p1.first < p2.first;
}

namespace Fenwick {
  const int SIZE = 200000 + 100;
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


int n, m;
int res[200000 + 5];
void solve() {
  scanf("%d", &n);
  ve<pair<int, int>> a;
  for(int i = 0; i < n; i++) {
    int x;
    scanf("%d", &x);
    a.pb({x, i});
  }
  memset(res, 0, sizeof(res));
  
  ve<ve<int>> g(n);
  for(int k = 1; k <= n - 1; k++) {
    int root = 0;
    for(int j = 1; j < n; j += k) {
      g[root].pb(j);
      root++;
    }
  }


  Fenwick :: init();
  sort(a.begin(), a.end(), COMP);
  for(int i = 0; i < a.size(); i++) {
    int j = i;
    W(j < a.size() && a[j].first == a[i].first) {
      pair<int, int>& p = a[j];
      int index = p.second;
      for(int k = 1; k <= n - 1; k++) {
        if(k > g[index].size()) break;
        int l = g[index][k - 1], r = min(n - 1, l + k - 1);
        int sum = Fenwick :: query(l, r);
        res[k] += sum;
      }
      j++;
    }


    j = i;
    W(j < a.size() && a[j].first == a[i].first) {
      pair<int, int>& p = a[j];
      int index = p.second;
      Fenwick :: update(index, 1);
      j++;
    }
    i = j - 1;
  }
  
  for(int k = 1; k <= n - 1; k++) {
    printf("%d ", res[k]);
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
