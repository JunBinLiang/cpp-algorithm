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




const int MAX = 300000 + 100;


struct Node {
  int l, r;
  ll mn;
} tree[MAX * 4];

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  tree[id * 2 + 1] = {l, mid, 15000000000000000ll};
  tree[id * 2 + 2] = {mid + 1, r, 15000000000000000ll};
  build(id * 2 + 1);
  build(id * 2 + 2);
}

void update(int id, int index, ll val) { 
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    tree[id].mn = val; 
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

ll query(int id, int s, int e) {
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


ll a[MAX];
ll b[MAX];
ll D[MAX];
ll Pre[MAX];
ll mins[MAX];
void solve() {
  int n, k;
  ll res = 0;
  scanf("%d%d", &n, &k);
  FOR(i, 0, n) {
    scanf("%d", &a[i]);//dif
    scanf("%d", &b[i]);
    res = max(res, (ll)(k - b[i]));
    b[i] = k - b[i];
  }
  
  tree[0] = {0, n, 15000000000000000ll};
  build(0);
  FOR(i, 1, n) {
    D[i - 1] = a[i] - a[i - 1];
    D[i - 1] *= D[i - 1];
  }
  Pre[0] = 0;
  update(0, 0, Pre[0]);
  FOR(i, 1, n) {
    Pre[i] += Pre[i - 1];
    Pre[i] += b[i - 1];
    update(0, i, Pre[i]);
  }


  ve<pair<int, ll>> sta;
  sta.pb({-1, 1000000000000000000ll});
  map<ll, int> f;

  ll cur = 0;
  FOR(i, 0, n) {
    cur += b[i];
    if(f.size() > 0) {
      auto it = f.begin();
      res = max(res, cur - (it -> first));
    }
    
    W(sta.size() > 0) {
      pair<int, ll> pa = sta[sta.size() - 1];
      if(D[i] >= pa.se) {
        sta.pop_back();
        ll mn = mins[pa.first];
        f[mn]--;
        if(f[mn] == 0) f.erase(mn);
      } else {
        break;
      }
    }

    pair<int, ll> pa = sta[sta.size() - 1];
    sta.pb({i, D[i]});
    int l = pa.first + 1;
    ll mn = query(0, l, i);
    mn += D[i];
    mins[i] = mn;
    f[mn]++;
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
