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

const int MAX = 200000 + 100;

struct Node {
  int l, r;
  int mx;
} tree[MAX * 4];

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  tree[id * 2 + 1] = {l, mid, -1};
  tree[id * 2 + 2] = {mid + 1, r, -1};
  build(id * 2 + 1);
  build(id * 2 + 2);
}

void update(int id, int index, int val) { 
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    tree[id].mx = val;  
    return;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(index <= mid) {
    update(left, index, val);
  } else {
    update(right, index, val);
  }
  tree[id].mx = max(tree[left].mx, tree[right].mx);
}

int query(int id, int s, int e) {
  if(s > e) return -1;
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return tree[id].mx;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(e <= mid){
      return query(left, s, e);
  } else if(s >= mid + 1) {
      return query(right, s, e);
  } else {
    return max(query(left, s, mid), query(right, mid + 1, e));
  }
}


namespace Fenwick {
  const int SIZE = 200000 + 100;
  ll tree[SIZE];
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

  ll pre(int i) {
    ll sum = 0;
    while(i>0){
      sum += tree[i];
      i -= ( i & -i);
    }
    return sum;
  }
  ll query(int i, int j) {
      return pre(j + 1) - pre(i);
  }
}

int a[200000 + 5];
void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  Fenwick :: init();
  for(int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    Fenwick :: update(i, a[i]);
  }


  



  for(int i = 0; i < m; i++) {
    int index, val;
    scanf("%d%d", &index, &val);
    index--;
    int old = a[index];
    a[index] = val;
    int add = a[index] - old;
    
    Fenwick :: update(index, add);
    ll sum = Fenwick :: query(0, index);
    
    if(a[0] == 0) {
        printf("%d \n", 1);
        continue;
    }
    
    if(index == 0) {
        if(sum == 0) {
            printf("%d \n", 1);
            continue;
        }
    } else {
        ll pre = Fenwick :: query(0, index - 1);
        if(pre * 2 == sum) {
            printf("%d \n", index + 1);
            continue;
        }
    }
    int res = -1;
    index = 0;
    sum = a[0];
    W(true) {
    int l = index + 1, r = n - 1;
    int pos = -1;
    ll s1 = -1;
    W(l <= r) {
      int mid = l + (r - l) / 2;
      ll otherSum = Fenwick :: query(0, mid);
      if(otherSum >= 2 * sum) {
        s1 = otherSum;
        pos = mid;
        r = mid - 1;
      } else {
        l = mid + 1;
      }
    }
    if(pos == -1) {
      break;
    }

    if(s1 == sum) {
      res = pos + 1;
      break;
    }

    ll pre = Fenwick :: query(0, pos - 1);
    if(pre * 2 == s1) {
      res = pos + 1;
      break;
    }

    sum = s1;
    index = pos;
  }
  printf("%d \n", res);
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
