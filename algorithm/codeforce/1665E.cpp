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
    bool operator() (ve<int>& a, ve<int>& b)
    {
        return a[0] > b[0];
    }
};*/



int a[100000 + 5];
const int MAX = 100000 + 5;
struct Node {
  int l, r;
  int b[35];
  void init() {
    for(int i = 0; i < 35; i++) {
      b[i] = 2000000000;
    }
  }

  void add(int val) {
    for(int i = 0; i < 35; i++) {
      if(val < b[i]) {
        for(int j = 34; j > i; j--) {
          b[j] = b[j - 1];
        }
        b[i] = val;
        break;
      }
    }
  }
  ve<int> to() {
    ve<int> c(35);
    for(int i = 0; i < 35; i++) c[i] = b[i];
    return c;
  }
} tree[MAX * 4];

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    tree[id].b[0] = a[l];
    return;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  tree[left] = {l, mid};
  tree[right] = {mid + 1, r};
  tree[left].init();
  tree[right].init();
  build(left);
  build(right);
  for(int i = l; i <= r; i++) {
    tree[id].add(a[i]);
  }
  
}

ve<int> query(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  //cout << "query  " << id << " " << s << " " << e << " " << l << " " << r << endl;
  if(l == s && r == e){
    return tree[id].to();
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(e <= mid){
      return query(left, s, e);
  } else if(s >= mid + 1) {
      return query(right, s, e);
  } else {
    ve<int> b = query(left, s, mid);
    ve<int> c = query(right, mid + 1, e);
    for(int i = 0; i < (int)(b.size()); i++) c.pb(b[i]);
    sort(c.begin(), c.end());
    ve<int> res;
    for(int i = 0; i < (int)(c.size()) && res.size() < 35; i++) {
      res.pb(c[i]);
    }
    return res;
  }
}




void solve() {
  int n;  
  scanf("%d", &n);
  for(int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }


  tree[0] = {0, n - 1};
  tree[0].init();
  build(0);
  
  
  int m;
  scanf("%d", &m);
  W(m--) {
    int l, r;
    scanf("%d%d", &l, &r);
    l--;
    r--;
    ve<int> res = query(0, l, r);
    int mn = 2000000000;
    for(int i = 0; i < res.size(); i++) {
      for(int j = i + 1; j < res.size(); j++) {
        mn = min(mn, res[i] | res[j]);
      }
    }
    printf("%d\n", mn);
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
