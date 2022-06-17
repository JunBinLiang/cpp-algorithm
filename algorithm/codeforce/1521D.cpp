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

struct Tuple{
  int a, b, c, d;
};

const int SIZE = 100000 + 5;
//const int SIZE = 50;
Tuple ans[SIZE];
int dp[SIZE][2];
int Nxt[SIZE];
int Nxt1[SIZE][2];
int in[SIZE];
int idx1 = 0, idx2 = 0;
int id = 1;
ve<pair<int, int>> leaves;
us<string> se;

int find(ve<int>& nums, int x){
  if(nums[x] == x) return x;
  int root = find(nums, nums[x]);
  nums[x] = root;
  return root;
}

void merge(ve<int>& nums, int r1, int r2) {
  if(r1 != r2) {
    nums[r1] = r2;
  }
}

int dfs(ve<ve<int>>& graph, int pa, int root, int state) {
  if(dp[root][state] != -1) {
    return dp[root][state];
  }

  if(graph[root].size() == 1 && pa != -1) {
    int res = 0;
    if(state == 0) res = 1;
    return dp[root][state] = res;
  }
  
  ve<pair<int, int>> a;
  int sum = 0;
  for(int& nxt : graph[root]) {
    if(nxt == pa) continue;
    dfs(graph, root, nxt, 0); // cut
    dfs(graph, root, nxt, 1); // go straight
    sum += dp[nxt][0];
    a.pb({nxt, dp[nxt][1] - dp[nxt][0] });
  }

  sort(a.begin(), a.end(), COMP);

  int res = 1000000000;
  if(state == 1) {
    for(int& nxt : graph[root]) {
      if(nxt == pa) continue;
      int lines = sum - dp[nxt][0] + dp[nxt][1];
      if(res > lines) {
        res = lines;
        Nxt[root] = nxt;
      }
    }
  } else {
    //2 one, all zero
    int sub = 0;
    for(int i = 0; i < a.size(); i++) {
      if(i >= 2) break;
      sub += a[i].second;
      int lines = 1 + sum + sub;
      if(res > lines) {
        res = lines;
        if(i == 0) {
          Nxt1[root][i] = a[i].first;
        } else {
          Nxt1[root][0] = a[0].first;
          Nxt1[root][1] = a[1].first;
        }
        
      }
    }
  }
  return dp[root][state] = res;
}


void dfs1(ve<ve<int>>&graph, int pa,int root, int state, int which) {
  if(state == 0) {
    for(int& nxt : graph[root]) {
      if(nxt == pa) continue;
      if(nxt == Nxt1[root][0] || nxt == Nxt1[root][1]) {
        dfs1(graph, root, nxt, 1, which);
      } else {
        ans[idx1++] = {root, nxt, -1, -1};
        id++;
        dfs1(graph, root, nxt, 0, id);
      }

    }
  } else {
    int x = Nxt[root];
    //not cut
    for(int& nxt : graph[root]) {
      if(pa == nxt) continue;
      if(nxt == x) {
        dfs1(graph, root, nxt, 1, which);
      } else {
        ans[idx1++] = {root, nxt, -1, -1};
        id++;
        dfs1(graph, root, nxt, 0, id);
      }
    }
  }
}

void solve() {
  int n;
  scanf("%d", &n);
  ve<ve<int>> graph(n);
  se.clear();
  ve<int> nums(n);

  for(int i = 0; i < n; i++) {
    dp[i][0] = -1;
    dp[i][1] = -1;
    Nxt[i] = -1;
    Nxt1[i][0] = -1;
    Nxt1[i][1] = -1;
    in[i] = 0;
    nums[i] = i;
  }

  ve<pair<int, int>> edges;
  for(int i = 0; i < n - 1; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--;
    v--;
    graph[u].pb(v);
    graph[v].pb(u);
    edges.pb({min(u,v), max(u,v)});
  }

  
  idx1 = 0;
  idx2 = 0;
  id = 1;
  dfs(graph, -1, 0, 0);
  dfs1(graph, -1, 0, 0, 0);
  sort(leaves.begin(), leaves.end(), COMP);
  

  for(int i = 0; i < idx1; i++) {
    int mn = min(ans[i].a, ans[i].b);
    int mx = max(ans[i].a, ans[i].b);
    string s = to_string(mn) + "|" + to_string(mx);
    se.insert(s);
  }

  for(pair<int, int>& edge : edges) {
    string s = to_string( edge.first) + "|" + to_string( edge.second);
    if(se.find(s) == se.end()) {
      int u = edge.first, v = edge.second;
      in[u]++;
      in[v]++;
      int r1 = find(nums, u);
      int r2 = find(nums, v);
      merge(nums, r1, r2);
    }
  }

  ve<pair<int, int>> leaves;
  for(int i = 0; i < n; i++) {
    if(in[i] <= 1) {
      int r = find(nums, i);
      leaves.pb({i, r});
    }
  }

  sort(leaves.begin(), leaves.end(), COMP);
  for(int i = 1; i < leaves.size(); i++) {
    if(leaves[i].second != leaves[i - 1].second) {
      ans[idx2].c = leaves[i].first;
      ans[idx2++].d = leaves[i - 1].first;
    }
  }


  printf("%d \n", idx1);
  for(int i = 0; i < idx1; i++) {
    printf("%d %d %d %d \n", ans[i].a + 1, ans[i].b + 1, ans[i].c + 1, ans[i].d + 1);
  }
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
