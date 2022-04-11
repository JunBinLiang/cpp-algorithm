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

const int MAX = 200000 + 100;


struct Node {
  int l, r;
  int mn;
} tree[MAX * 4];

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  tree[id * 2 + 1] = {l, mid, 500000};
  tree[id * 2 + 2] = {mid + 1, r, 500000};
  build(id * 2 + 1);
  build(id * 2 + 2);
}

void update(int id, int index, int val) { 
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    tree[id].mn = min(tree[id].mn, val); 
    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(index <= mid) {
    update(left, index, val);
  } else {
    update(right, index, val);
  }
  tree[id].mn = min(tree[left].mn, tree[right].mn);
}

int query(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return tree[id].mn;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(e <= mid){
      return query(left, s, e);
  } else if(s >= mid + 1) {
      return query(right, s, e);
  } else {
    return min(query(left, s, mid), query(right, mid + 1, e));
  }
}



int n, m;
void solve() {
  scanf("%d%d", &n, &m);
  set<int> se;
  for(int i = 0; i <= n + 1; i++) {
    se.insert(i);
  }

  tree[0] = {0, n + 1, 500000};
  build(0);

  FOR(i, 0, m) {
    int op;
    scanf("%d", &op);
    if(op == 0) {
      int l, r, x;
      scanf("%d%d%d", &l, &r, &x);
      if(x == 0) { // no any sick people
        auto it = se.lower_bound(l);
        ve<int> del;
        W(true) {
          int val = (*it);
          if(val > r) break;
          del.pb(val);
          it++;
        }
        for(int& k : del) {
          se.erase(k);
        }

      } else {//at least one
        update(0, l, r);
      }

    } else {
      int index;
      scanf("%d", &index);
      if(se.find(index) == se.end()) {
          printf("NO\n");
      } else {
        auto it = se.lower_bound(index);
        auto pr = prev(it, 1);
        it++;
        int l = (*pr) + 1, r = (*it) - 1;
        int mn = query(0, l, index);
        if(mn <= r) {
          printf("YES\n");
        } else {
          printf("N/A\n");
        }
      }
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
