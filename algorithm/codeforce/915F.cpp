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
#define f first
#define se second
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define W while
#define RFOR(i, a, b) for (int i = a; i >= b; i--)
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

int MOD = 998244353;
int mod = 998244353;

int find(ve<int>& nums, int x){
  if(nums[x] == x) return x;
  int root = find(nums, nums[x]);
  nums[x] = root;
  return root;
}


int b[1000000 + 100];
ll getMax(ve<ve<int>>& graph, ve<ve<int>>& a) {
  ll res = 0;
  int n = a.size();
  ve<int> nums(n);
  ve<ll> cnt(n, 1);
  FOR(i, 0, n) {
    nums[i] = i;
  }

  FOR(i, 0, n) {
    int u = a[i][1];
    ll sum = 0;
    for(int& v : graph[u]) {
      if(b[v] <= b[u]) {
        int r1 = find(nums, u);
        int r2 = find(nums, v);
        if(r1 != r2) {
          nums[r2] = r1;
          sum += (a[i][0] + 0ll) * (cnt[r1] * cnt[r2]);
          cnt[r1] += cnt[r2];
        }
      }
    }  
    res += sum;
  } 
  return res;
}

ll getMin(ve<ve<int>>& graph, ve<ve<int>>& a) {
  reverse(a.begin(), a.end());
  ll res = 0;
  int n = a.size();
  ve<int> nums(n);
  ve<ll> cnt(n, 1);
  FOR(i, 0, n) {
    nums[i] = i;
  }
  FOR(i, 0, n) {
    int u = a[i][1];
    ll sum = 0;
    for(int& v : graph[u]) {
      if(b[v] >= b[u]) {
        int r1 = find(nums, u);
        int r2 = find(nums, v);
        if(r1 != r2) {
          nums[r2] = r1;
          sum += (a[i][0] + 0ll) * (cnt[r1] * cnt[r2]);
          cnt[r1] += cnt[r2];
        }
      }
    }  
    res += sum;  
  }
  return res;
}
void solve() {
  int n;
  scanf("%d", &n);
  ve<ve<int>> a;
  ve<ve<int>> graph(n);
  FOR(i, 0, n) {
    int x;
    scanf("%d", &x);
    a.pb({x, i});
    b[i] = x;
  }
  sort(a.begin(), a.end(), COMP);

  FOR(i, 0, n - 1) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--;
    v--;
    graph[u].pb(v);
    graph[v].pb(u);
  }

  ll res = getMax(graph, a) - getMin(graph, a);
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
