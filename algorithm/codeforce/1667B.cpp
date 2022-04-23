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

const int MAX = 500000 + 100;

struct Node {
  int l, r;
  int mx, mx2;
} tree[MAX * 4];

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  tree[id * 2 + 1] = {l, mid, -50000000, -50000000};
  tree[id * 2 + 2] = {mid + 1, r, -50000000, -50000000};
  build(id * 2 + 1);
  build(id * 2 + 2);
}

void update1(int id, int index, int val) { 
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    tree[id].mx = max(tree[id].mx, val);  
    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(index <= mid) {
    update1(left, index, val);
  } else {
    update1(right, index, val);
  }
  tree[id].mx = max(tree[left].mx, tree[right].mx);
}


void update2(int id, int index, int val) { 
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    tree[id].mx2 = max(tree[id].mx2, val);  
    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(index <= mid) {
    update2(left, index, val);
  } else {
    update2(right, index, val);
  }
  tree[id].mx2 = max(tree[left].mx2, tree[right].mx2);
}


int query1(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return tree[id].mx;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(e <= mid){
      return query1(left, s, e);
  } else if(s >= mid + 1) {
      return query1(right, s, e);
  } else {
    return max(query1(left, s, mid), query1(right, mid + 1, e));
  }
}

int query2(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return tree[id].mx2;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(e <= mid){
      return query2(left, s, e);
  } else if(s >= mid + 1) {
      return query2(right, s, e);
  } else {
    return max(query2(left, s, mid), query2(right, mid + 1, e));
  }
}



int n;
int a[500000+ 5];
ll Pre[500000 + 5];
int dp[500000 + 5];
um<ll, int> f;
int id = 1;
ll get(int l, int r) {
  if(l == 0) return Pre[r];
  return Pre[r] - Pre[l - 1];
}

void solve() {
  id = 1;
  scanf("%d", &n);
  ll sum = 0;
  ve<ll> b;
  for(int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    sum += a[i];
    Pre[i] = sum;
    b.pb(sum);
    dp[i] = -1000000;
  }

  sort(b.begin(), b.end());
  for(int i = 0; i < b.size(); i++) {
    int j = i;
    W(j < b.size() && b[j] == b[i]) {
      j++;
    }
    f[b[i]] = id++;
    i = j - 1;
  }

  tree[0] = {0, id + 1, -50000000, 50000000};
  build(0);

  um<int, int> ma;
  
  for(int i = 0; i < n; i++) {
    ll cur = Pre[i];
    if(cur > 0) {
      dp[i] = i + 1;
    } else if(cur == 0) {
      dp[i] = 0;
    } else {
      dp[i] = -(i + 1);
    }
    int index = f[cur];

    if(ma.find(index) != ma.end()) {
      dp[i] = max(dp[i], ma[index]);
    } 

    int less = query1(0, 0, index - 1);
    int big = query2(0, index + 1, id);
    dp[i] = max(dp[i], (i + 1) + less);
    dp[i] = max(dp[i], -(i + 1) + big);
    


    if(ma.find(index) != ma.end()) {
      ma[index] = max(ma[index], dp[i]);
    } else {
      ma[index] = dp[i];
    }


    update1(0, index, dp[i] - (i + 1));
    update2(0, index, dp[i] + (i + 1));
  }
  
  printf("%d\n", dp[n - 1]);
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
