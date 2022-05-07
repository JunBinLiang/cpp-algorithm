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

const int MAX = 200000 + 100;

struct Node {
  int l, r;
  int mn;
} tree1[MAX * 4], tree2[MAX * 4];

void build(Node tree[], int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  tree[id * 2 + 1] = {l, mid, 1000000000};
  tree[id * 2 + 2] = {mid + 1, r, 1000000000};
  build(tree, id * 2 + 1);
  build(tree, id * 2 + 2);
}

void update(Node tree[], int id, int index, int val) { 
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    tree[id].mn = val;  
    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(index <= mid) {
    update(tree, left, index, val);
  } else {
    update(tree, right, index, val);
  }
  tree[id].mn = min(tree[left].mn, tree[right].mn);
}

int query(Node tree[], int id, int s, int e) {
  if(s > e) {
    return 1000000000;
  } 
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return tree[id].mn;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(e <= mid){
      return query(tree, left, s, e);
  } else if(s >= mid + 1) {
      return query(tree, right, s, e);
  } else {
    return min(query(tree, left, s, mid), query(tree, right, mid + 1, e));
  }
}




struct Query {
  int x, y;
  char c;
};

um<int, int> f1;
um<int, int> f2;
void solve() {
  int n, m;
  cin >> n >> m;
  ve<Query> a;
  ve<int> b;
  FOR(i, 0, m) {
    int x, y;
    char cc;
    cin >> x >> y >> cc;
    a.pb({x, y, cc});
    b.pb(x);
  }
  
  sort(b.begin(), b.end());
  for(int i = 0; i < b.size(); i++) {
    int x = b[i];
    f1[x] = i;
  }

  tree1[0] = {0, m + 1, 1000000000};
  tree2[0] = {0, m + 1, 1000000000};
  build(tree1, 0);
  build(tree2, 0);
  us<int> se;
 

  for(int i = 0; i < a.size(); i++) {
    int x = a[i].x, y = a[i].y;
    if(se.find(x) != se.end()) {
        printf("%d\n", 0);
        continue;
    }
    se.insert(x);
    int id1 = f1[x];
    int res = -1;
    char op = a[i].c;
    if(op == 'U') {
       int mn = query(tree2, 0, id1 + 1, m);
       if(mn > x) {
        res = 1;
        update(tree1, 0, id1, res);
        printf("%d\n", y - res + 1);
       } else {
         int l = id1 + 1, r = m;
         W(l <= r) {
           int mid = l + (r - l) / 2;
           int mnn = query(tree2, 0, id1 + 1, mid);
           if(mnn <= x) {
             res = mid;
             r = mid - 1;
           } else {
             l = mid + 1;
           }
         }
         res = b[res];
         int dif = res - x;
         printf("%d\n", dif);
         update(tree1, 0, id1, y - dif + 1);
       }
    } else {
      int mn = query(tree1, 0, 0, id1 - 1);
      if(mn > y) {
        res = 1;
        update(tree2, 0, id1, res);
      } else {
        int l = 0, r = id1 - 1;
        W(l <= r) {
          int mid = l + (r - l) / 2;
          int mnn = query(tree1, 0, mid, id1 - 1);
          if(mnn <= y) {
            res = mid;
            l = mid + 1;
          } else {
            r = mid - 1;
          }
        }
        res = b[res] + 1;
        update(tree2, 0, id1, res);
      }
      printf("%d\n", x - res + 1);
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
