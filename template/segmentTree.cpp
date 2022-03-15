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
using namespace std;
using ll = long long;

#define pb push_back
#define f first
#define se second
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define RFOR(i, a, b) for (int i = a; i >= b; i--)

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

int MOD = 998244353;
int mod = 1000000007;
int INF = INT_MAX;
const int MAX = 150020;


struct Node {
  int l, r;
  int setTo = 0, flip = 0, sum = 0;
} tree[MAX * 8];

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  tree[id * 2 + 1] = {l, mid, -1, 0, 0};
  tree[id * 2 + 2] = {mid + 1, r, -1, 0, 0};
  build(id * 2 + 1);
  build(id * 2 + 2);
}

void update(int id, int s, int e, int val, int flip) {
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e) {
    if(flip == 1) {
      if(tree[id].setTo == -1) {
        tree[id].flip++;
        tree[id].flip%= 2;
        tree[id].sum = (r - l + 1) - tree[id].sum;
      } 
      else if(tree[id].setTo == 0) {
        tree[id].setTo = 1;
        tree[id].sum = (r - l + 1);
      } else {
        tree[id].setTo = 0;
        tree[id].sum = 0;
      }

    } else {
      tree[id].setTo = val;
      tree[id].flip = 0;
      if(val == 0) {
        tree[id].sum = 0;
      } else {
        tree[id].sum = r - l + 1;
      }
    }
    return;
  }


  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  
  //push down
  if(tree[id].setTo != -1) {
    update(left, tree[left].l, tree[left].r, tree[id].setTo, 0);
    update(right, tree[right].l, tree[right].r, tree[id].setTo, 0);
    tree[id].setTo = -1;
  }
  if(tree[id].flip != 0) {
    update(left, tree[left].l, tree[left].r, 0, tree[id].flip);
    update(right, tree[right].l, tree[right].r, 0, tree[id].flip);
    tree[id].flip = 0;
  }


  if(e <= mid) {
    update(left, s, e, val, flip);
  } else if(s >= mid + 1) {
    update(right, s, e, val, flip);
  } else {
    update(left, s, mid, val, flip);
    update(right, mid + 1, e, val, flip);
  }
  tree[id].sum = tree[left].sum + tree[right].sum;
}

int query(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    return l;
  }
  
  int left = id * 2 + 1, right = id * 2 + 2;
  int mid = l + (r - l) / 2;
  //check tag
  if(tree[id].sum == (r - l + 1)) {
    return -1;
  }

  //push down
  if(tree[id].setTo != -1) {
    update(left, tree[left].l, tree[left].r, tree[id].setTo, 0);
    update(right, tree[right].l, tree[right].r, tree[id].setTo, 0);
    tree[id].setTo = -1;
  }
  if(tree[id].flip != 0) {
    update(left, tree[left].l, tree[left].r, 0, tree[id].flip);
    update(right, tree[right].l, tree[right].r, 0, tree[id].flip);
    tree[id].flip = 0;
  }


  int s1 = mid - l + 1;
  int s2 = (r - l + 1) - s1;
  if(tree[left].sum < s1) {
    return query(id * 2 + 1);
  } else {
    return query(id * 2 + 2);
  }

}


unordered_map<ll, int> f;
unordered_map<int, ll> g;
void solve() {
  int n;
  cin >> n;
  ve<ve<ll>> Q;
  ve<ll> a;
  FOR(i, 0, n) {
    ll op, l, r;
    cin >> op >> l >> r;
    Q.pb({op, l, r});
    a.pb(l); a.pb(r);
    a.pb(r + 1);
  }
  a.pb(1);
  a.pb(2);
  
  // discrete values
  ll mx = -1;
  sort(a.begin(), a.end());
  int id = 0;
  FOR(i, 0, a.size()) {
    if(i > 0 && a[i] == a[i - 1]) {
    } else {
      f[a[i]] = id;
      g[id] = a[i];
      id++;
    }
    mx = max(mx, a[i]);
  }


  tree[0] = {0, id, -1, 0, 0};
  build(0);


  for(ve<ll>& q : Q) {
    ll op = q[0], l = q[1], r = q[2];
    int ll = f[l], rr = f[r]; 
    if(op == 1) {//add
      update(0, ll, rr, 1, 0);
    } else if(op == 2) {//delete
      update(0, ll, rr, 0, 0);
    } else { //flip
      update(0, ll, rr, -1, 1);
    }

    int index = query(0);
    if(index == -1 || index >= id) {// all are setted
      cout << mx + 1 << endl;
    } else {
      cout << g[index] << endl;
    }
  }
}

int main()
{
  int t = 1;
  //cin >> t;
  while (t--)
  {
    solve();
  }
  return 0;
}
