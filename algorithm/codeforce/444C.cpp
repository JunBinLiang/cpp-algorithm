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
struct Node {
  int l, r;
  ll val;
  bool has;
  ll sum, add;//prefix sum, current val
} tree[MAX * 4];

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    tree[id].val = l + 1;
    return;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  tree[left] = {l, mid, -1, false, 0, 0};
  tree[right] = {mid + 1, r, -1, false, 0, 0};
  build(left);
  build(right);
}

void update(int id, int s, int e, int val, int set) { 
  int l = tree[id].l, r = tree[id].r;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(l == s && r == e) {
    if(l == r) {
      if(tree[id].val == -1) {
          tree[id].val = val;
      } else {
          tree[id].add += abs(val - tree[id].val);
          tree[id].sum += abs(val - tree[id].val);
          if(set == 1) tree[id].val = val;
          else tree[id].val = -1;
      }
      
      return;
    }
    
    if(tree[id].val == -1) {
      if(set == 2) {
          tree[id].val = val;
          return;
      }    
        
      if(set == 1) {
          tree[id].val = val;
          set = 0;
      }
      update(left, tree[left].l, tree[left].r, val, set);
      update(right, tree[right].l, tree[right].r, val, set);
      tree[id].sum = tree[left].sum + tree[right].sum + tree[id].add * (r - l + 1ll);
    } else {
      tree[id].add += abs(val - tree[id].val);
      tree[id].sum = tree[left].sum + tree[right].sum + tree[id].add * (r - l + 1ll);
      if(set == 1) tree[id].val = val;
      else tree[id].val = -1;
    }
    return;
  }

  int mid = l + (r - l) / 2;
  //push down
  if(tree[id].val != -1) {
    update(left, tree[left].l, tree[left].r, tree[id].val, 2);
    update(right, tree[right].l, tree[right].r, tree[id].val, 2);
    tree[id].val = -1;
  }
  if(e <= mid) {
    update(left, s, e, val, set);
  } else if(s >= mid + 1) {
    update(right, s, e, val, set);
  } else {
    update(left, s, mid, val, set);
    update(right, mid + 1, e, val, set);
  }
  tree[id].sum = tree[left].sum + tree[right].sum + tree[id].add * (r - l + 1ll);
}

ll query(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return tree[id].sum;
  }
  int mid = l + (r - l) / 2;
  ll add = tree[id].add * (e - s + 1ll);
  int left = id * 2 + 1, right = id * 2 + 2;
  if(e <= mid){
      return  add + query(left, s, e);
  } else if(s >= mid + 1) {
      return  add + query(right, s, e);
  } else {
    return  add + (query(left, s, mid) + query(right, mid + 1, e));
  }
}

void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  tree[0] = {0, n - 1, -1, false, 0, 0};
  build(0);

  for(int i = 0; i < m; i++) {
    int ty;
    scanf("%d", &ty);
    if(ty == 1) {
      int l, r, x;
      scanf("%d%d%d", &l, &r, &x);
      l--; r--;
      update(0, l, r, x, 1);
    } else {
      int l, r;
      scanf("%d%d", &l, &r);
      l--; r--;
      ll res = query(0, l, r);
      printf("%lld\n", res);
    }
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

//3454000613532
