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

int a[400000 + 5];
ve<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71,
                73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167,
                173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269,
                271, 277, 281, 283, 293};

int ma[301];
int mod = 1000000007;
const int MAX = 400000 + 5;

ll Pow(ll B,ll E){ll A=1;for(;E;E>>=1,B=B*B%mod)E&1?A=A*B%mod:0;return A;}
struct Node {
  int l, r;
  ll setTo = 0;
  ll val = 0;
} tree[MAX * 4];

struct Node1 {
  int l, r;
  ll val = 0;
  ll setTo = 1;
} tree1[MAX * 4];

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    int x = a[l];
    for(int i = 2; i <= x / i; i++) {
      if(x % i == 0) {
        tree[id].val |= (1ll << ma[i]);
        W(x % i == 0) x /= i;
      }
    }
    if(x > 1) {
      tree[id].val |= (1ll << ma[x]);
    }
    return;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  tree[left] = {l, mid, 0, 0};
  tree[right] = {mid + 1, r, 0, 0};
  build(left);
  build(right);
  tree[id].val = tree[left].val | tree[right].val;
}

void build1(int id) {
  int l = tree1[id].l, r = tree1[id].r;
  if(l == r) {
    tree1[id].val = a[l];
    return;
  }
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  tree1[left] = {l, mid, 0, 1};
  tree1[right] = {mid + 1, r, 0, 1};
  build1(left);
  build1(right);
  tree1[id].val = tree1[left].val * tree1[right].val;
  tree1[id].val %= mod;
}

void update(int id, int s, int e, ll val) { 
  int l = tree[id].l, r = tree[id].r;
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(l == s && r == e) {
    tree[id].val |= val;
    tree[id].setTo |= val;
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
  tree[id].val = tree[left].val | tree[right].val;
}


void update1(int id, int s, int e, ll val) { 
  int l = tree1[id].l, r = tree1[id].r;
  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(l == s && r == e) {
    tree1[id].val *= Pow(val, r - l + 1);
    tree1[id].setTo *= val;
    
    tree1[id].val %= mod;
    tree1[id].setTo %= mod;
    return;
  }


  if(tree1[id].setTo != 1) {
    update1(left, tree1[left].l, tree1[left].r, tree1[id].setTo);
    update1(right, tree1[right].l, tree1[right].r, tree1[id].setTo);
    tree1[id].setTo = 1;
  }

  if(e <= mid) {
    update1(left, s, e, val);
  } else if(s >= mid + 1) {
    update1(right, s, e, val);
  } else {
    update1(left, s, mid, val);
    update1(right, mid + 1, e, val);
  }
  tree1[id].val = tree1[left].val * tree1[right].val;
  tree1[id].val %= mod;
}

ll query(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return tree[id].val;
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
    return (query(left, s, mid) | query(right, mid + 1, e));
  }
}


ll query1(int id, int s, int e) {
  int l = tree1[id].l, r = tree1[id].r;
  if(l == s && r == e){
    return (tree1[id].val) % mod;
  }

  int mid = l + (r - l) / 2;
  int left = id * 2 + 1, right = id * 2 + 2;
  if(tree1[id].setTo != 1) {
    update1(left, tree1[left].l, tree1[left].r, tree1[id].setTo);
    update1(right, tree1[right].l, tree1[right].r, tree1[id].setTo);
    tree1[id].setTo = 1;
  }

  if(e <= mid){
      return query1(left, s, e);
  } else if(s >= mid + 1) {
      return query1(right, s, e);
  } else {
    return (query1(left, s, mid) * query1(right, mid + 1, e)) % mod;
  }
}

ll modInverse(ll a, ll m) {
    ll m0 = m;
    ll y = 0, x = 1;
    if (m == 1)
      return 0;
    while (a > 1) {
      // q is quotient
      ll q = a / m;
      ll t = m;
      // m is remainder now, process
      // same as Euclid's algo
      m = a % m;
      a = t;
      t = y;
      // Update x and y
      y = x - q * y;
      x = t;
    }
    // Make x positive
    if (x < 0)
        x += m0;
    return x;
}


void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  for(int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }

  for(int i = 0; i < primes.size(); i++) {
    ma[primes[i]] = i;
  }

  ll inv[405];
  inv[0] = inv[1]=1;
  for (int i=2;i < 400;i++){
      inv[i] = modInverse(i,mod);
  }
  
  
  
  tree[0] = {0, n - 1, 0, 0};
  build(0);
  tree1[0] = {0, n - 1, 0, 1};
  build1(0);
  
  W(m--) {
    string s;
    cin >> s;
    if(s[0] == 'M') {
      int l, r, x;
      scanf("%d%d%d", &l, &r, &x);
      l--;
      r--;
      ll bit = 0;
      update1(0, l, r, x);
      for(int i = 2; i <= x / i; i++) {
        if(x % i == 0) {
          bit |= (1 << ma[i]);
          W(x % i == 0) x /= i;
        }
      }
      if(x > 1) bit |= (1ll << ma[x]);
      update(0, l, r, bit);
    } else {
      int l, r;
      scanf("%d%d", &l, &r);
      l--;
      r--;
      ll res = query1(0, l, r);
      res %= mod;
      //cout << res << endl;
      ll bit = query(0, l, r);
      for(int i = 0; i < primes.size(); i++) {
        if((bit & (1ll << i)) == 0) continue;
        int p = primes[i];
        res = res * ((((p - 1)) % mod * ((inv[p])) % mod) % mod);
        res %= mod;
      }
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
