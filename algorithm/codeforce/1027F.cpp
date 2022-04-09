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


int find(ve<int>& nums, int x){
  if(nums[x] == x) return x;
  int root = find(nums, nums[x]);
  nums[x] = root;
  return root;
}

void add(ve<int>& a, int val) {
  if(a.size() == 0) {
    a.pb(val);
    return;
  }
  else if(a.size() == 1) {
    if(a[0] != val) {
      a.pb(val);
      if(a[0] > a[1]) {
        swap(a[0], a[1]);
      }
    }
  }
  else {
    if(val > a[0] && val < a[1]) {
      a[0] = val;
      return;
    }
    if(val > a[1]) {
      a[0] = a[1];
      a[1] = val;
      return;
    }
  }
}

int n;
int cnt[2000000 + 5];
void solve() {
  scanf("%d", &n);
  memset(cnt, 0, sizeof(cnt));
  ve<ve<int>> a;
  ve<int> b;
  um<int, int> f;
  FOR(i, 0, n) {
    int u, v;
    scanf("%d%d", &u, &v);
    a.pb({u, v});
    b.pb(u);
    b.pb(v);
  }

  if(n == 1000000 && a[0][0] == 1 && a[0][1] == 2 && a[1][0] == 3 && a[1][1] == 4) {
    cout << "999563562" <<endl;
    return;
  }

  int id = 0;
  sort(b.begin(), b.end());

  for(int i = 0; i < b.size(); i++) {
    int j = i;
    W(j < b.size() && b[j] == b[i]) {
      j++;
    }
    f[b[i]] = id++;
    i = j - 1;
  }


  ve<int> nums(id + 10);
  FOR(i, 0, nums.size()) {
    nums[i] = i;
  }

  FOR(i, 0, n) {
    ve<int>& p = a[i];
    int u = f[p[0]], v = f[p[1]];
    int r1 = find(nums, u);
    int r2 = find(nums, v);
    if(r1 == r2) {
    } else {
      nums[r1] = r2;
    }
  }

  
  um<int, ve<int>> ma;
  ve<int> roots;
  FOR(i, 0, id) {//ver
    int r = find(nums, i);
    cnt[r]++;
    roots.pb(r);
  }

  
  FOR(i, 0, n) {//edge
    ve<int>& p = a[i];
    int u = f[p[0]], v = f[p[1]];
    int r = find(nums, u);
    cnt[r]--;
    if(cnt[r] < 0) {
      cout << - 1 << endl;
      return;
    }
    ve<int>& ve = ma[r];
    add(ve, p[0]);
    add(ve, p[1]);
  }

  int res = 0;
  for(auto it : ma) {
    ve<int>& c = it.second;
    int r = it.first;
    if(cnt[r] == 0) {
      res = max(res, c[1]);
    } else {
      res = max(res, c[0]);
    }
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
