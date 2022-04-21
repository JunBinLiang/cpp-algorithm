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




int n, m;
int a[100000 + 5];
ve<int> luck = {4,7,44,47,74,77,444,447,474,477,744,747,774,777,4444,4447,
4474,4477,4744,4747,4774,4777,7444,7447,7474,7477,7744,7747,7774,7777};


const int MAX = 100000;
const int MIN = -10000000;
int lu;
struct Node {
  int l, r;
  int setTo = 0, mx = MIN;
  int cnt = 0;
} tree[MAX * 4];

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    if(a[l] <= lu)tree[id].mx = a[l];
    if(a[l] == lu) {
      tree[id].cnt = 1;
    }
    return;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  tree[left] = {l, mid, 0, MAX, 0};
  tree[right] = {mid + 1, r, 0, MAX, 0};
  build(left);
  build(right);
  tree[id].cnt = tree[left].cnt + tree[right].cnt;
  tree[id].mx = max(tree[left].mx, tree[right].mx);
}


void update(int id, int s, int e, int val) { 
  int l = tree[id].l, r = tree[id].r;
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  
  if(l == r) {
    tree[id].mx += val;
    if(tree[id].mx == lu) {
      tree[id].cnt = 1;
    } else {
      tree[id].cnt = 0;
      if(tree[id].mx > lu) {
        tree[id].mx = MIN;
      }
    }
    return;
  }

  if(l == s && r == e) {
    tree[id].setTo += val;
    tree[id].mx += val;
    if(tree[id].mx < lu) {
      
    } else {
      update(left, tree[left].l, tree[left].r, tree[id].setTo);
      update(right, tree[right].l, tree[right].r, tree[id].setTo);
      tree[id].setTo = 0;
      tree[id].mx = max(tree[left].mx, tree[right].mx);
      tree[id].cnt = tree[left].cnt + tree[right].cnt;
    }
    return;
  }


  if(tree[id].setTo != 0) {
    update(left, tree[left].l, tree[left].r, tree[id].setTo);
    update(right, tree[right].l, tree[right].r, tree[id].setTo);
    tree[id].setTo = 0;
  }

  if(e <= mid) {
    update(left, s, e, val);
  } else if(s >= mid + 1) {
    update(right, s, e, val);
  } else {
    update(left, s, mid, val);
    update(right, mid + 1, e, val);
  }
  tree[id].mx = max(tree[left].mx, tree[right].mx);
  tree[id].cnt = tree[left].cnt + tree[right].cnt;
}

ll query(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return tree[id].cnt;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(tree[id].setTo != 0) {
    update(left, tree[left].l, tree[left].r, tree[id].setTo);
    update(right, tree[right].l, tree[right].r, tree[id].setTo);
    tree[id].setTo = 0;
  }

  if(e <= mid){
      return query(left, s, e);
  } else if(s >= mid + 1) {
      return query(right, s, e);
  } else {
    return (query(left, s, mid) + query(right, mid + 1, e));
  }
}



void solve() {
  scanf("%d%d", &n, &m);
  FOR(i, 0, n) {
    scanf("%d", &a[i]);
  }

  ve<ve<int>> Q;
  int cnt = 0;
  W(m--) {
    string s;
    cin >> s;
    int l, r;
    scanf("%d%d", &l, &r);
    l--; r--;
    if(s == "add") {
      int d;
      scanf("%d", &d);
      Q.pb({l, r, d});
    } else {
      Q.pb({l, r});
      cnt++;
    }
  }

  ve<int> res(cnt);
  for(int i = 0; i < luck.size(); i++) {
    lu = luck[i];
    tree[0] = {0, n - 1, 0, MAX, 0};
    build(0);    
    int index = 0;

    for(int j = 0; j < Q.size(); j++) {
      ve<int>& q = Q[j];
      if(q.size() == 3) {
        update(0, q[0], q[1], q[2]);
      } else {
        int cnt = query(0, q[0], q[1]);
        res[index] += cnt; 
        index ++;
      }
    }
  }



  //print answer
  for(int i : res) {
    printf("%d\n", i);
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
