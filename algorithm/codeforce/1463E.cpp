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
    bool operator() (pair<int, int>& a, pair<int, int>& b)
    {
        return a.first > b.first;
    }
    //a[0] > b[0] : min
};*/

bool COMP(const pair<int, int>&p1, const pair<int, int>&p2) {
  return p1.second < p2.second;
}

int find(ve<int>& nums, int x){
  if(nums[x] == x) return x;
  int root = find(nums, nums[x]);
  nums[x] = root;
  return root;
}

void merge(ve<int>&nums, int r1, int r2) {
  nums[r1] = r2;
}

bool seen[300000 + 5];
int in[300000 + 5];
int Next[300000 + 5];
void solve() {
  int n, k;
  scanf("%d%d", &n, &k);
  ve<int> a;
  ve<int> nums(n);
  ve<ve<int>> graph(n);
  ve<int> order;
  ve<int> res;

  memset(in, 0, sizeof(in));
  memset(seen, false, sizeof(seen));
  memset(Next, -1, sizeof(Next));
  
  for(int i = 0; i < n; i++) {
    nums[i] = i;
    int x;
    scanf("%d", &x);
    x--;
    a.pb(x);
  }

  for(int i = 0; i < k; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--;
    v--;
    int r1 = find(nums, u);
    int r2 = find(nums, v);
    if(r1 != r2) {
      merge(nums, r2, r1);
    }
    Next[u] = v;
  }

  int root = -1;
  for(int i = 0; i < n; i++) {
    if(a[i] == -1) {
      root = i;
      continue;
    }
    int r1 = find(nums, a[i]);
    int r2 = find(nums, i);
    if(r1 == r2) continue;
    graph[r1].pb(r2);
    in[r2]++;
  }

  root = find(nums, root);
  queue<int> q;
  q.push(root);
  W(q.size()) {
    int top = q.front(); q.pop();
    seen[top] = true;
    order.pb(top);
    for(int& nxt : graph[top]) {
      if(seen[nxt]) {
        printf("%d ", 0);
        return;
      }
      in[nxt]--;
      if(in[nxt] == 0) {
        q.push(nxt);
      }
    }
  }

  for(int i = 0; i < order.size(); i++) {
    int now = order[i];
    for(int j = now; j != -1; j = Next[j]) {
      res.pb(j);
      if(res.size() > n) {
        printf("%d", 0);
        return;
      }
    }
  }

  if(res.size() != n) {
    cout << 0 << endl;
    return;
  }

  ve<int>pos(n);
  for(int i = 0; i < n; i++) {
    pos[res[i]] = i;
  }

  for(int i = 0; i < n; i++) {
    if(a[i] != -1) {
      int u = a[i], v = i;
      if(pos[u] > pos[v]) {
        printf("0");
        return;
      }
    }
  }


  for(int i : res) {
    printf("%d ", i + 1);
  }

}

int main()
{

  int t = 1;
  //cin >> t;
  int x = 1;
  W (t--)
  {
    solve();
  }
  return 0;
}
