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


struct Tuple {
  int l, r, idx;
};

bool COMP(pair<int, int>& p1, pair<int, int>& p2) {
  return p1.second < p2.second;
}

int a[2][200000 + 5];
ve<int> graph[1000000 + 5];
ve<pair<int, int>> g[200000 + 5];
bool seen[1000000 + 5];
ve<int> res;
int n;

void dfs(ve<int>& b, int pa, int root) {
  seen[root] = true;
  int num = root;
  if(num % 2 == 1) num--;
  num /= 2;
  int r = num / n;
  int c = num % n;
  if(root % 2 == 0) { //up
    if(r != 0) { //swap
      b.pb(c);
    }
  } else { //down
    if(r != 1) { //swap
      b.pb(c);
    }
  }
  
  
  for(int nxt : graph[root]) {
    if(nxt == pa || seen[nxt]) continue;
    dfs(b, root, nxt);
  }
}

void solve() {
  
  scanf("%d", &n);
  res.clear();
  for(int i = 1; i <= 4 * n + 50; i++) {
    graph[i].clear();
    seen[i] = false;
  }
  for(int i = 0; i <= n; i++) {
    g[i].clear();
  }

  for(int i = 0; i < n; i++) {
    scanf("%d", &a[0][i]);
    g[a[0][i]].pb({0, i});
  }
  for(int i = 0; i < n; i++) {
    scanf("%d", &a[1][i]);
    g[a[1][i]].pb({1, i + n});
  }

  for(int i = 1; i <= n; i++) {
    if(g[i].size() != 2) {
      printf("-1 \n");
      return;
    }
  }

  for(int i = 0; i < n; i++) {
    if(a[0][i] == a[1][i]) continue;

    int id1 = i, id2 = i + n;
    int x = a[0][i], y = a[1][i];    
    for(int j = 0; j < 2; j++) {
      if(g[x][j].second == id1) continue;
      int id3 = g[x][j].second;
      graph[id1 * 2].pb(id3 * 2 + 1); //top -> bottom
      graph[id1 * 2 + 1].pb(id3 * 2); //bottom -> top
    }

    for(int j = 0; j < 2; j++) {
      if(g[y][j].second == id2) continue;
      int id3 = g[y][j].second;
      graph[id2 * 2].pb(id3 * 2 + 1); //top -> bottom
      graph[id2 * 2 + 1].pb(id3 * 2); //bottom -> top
    }  

    graph[id1 * 2].pb(id2 * 2 + 1);
    graph[id2 * 2 + 1].pb(id1 * 2);
    
    graph[id2 * 2].pb(id1 * 2 + 1);
    graph[id1 * 2 + 1].pb(id2 * 2);
    
  }
  
  for(int i = 0; i < n; i++) {
    if(a[0][i] == a[1][i]) continue;
    int id = i;
    if(!seen[id * 2 + 0]) {
    ve<int> b, c;
    dfs(b, -1, id * 2);
    dfs(c, -1, id * 2 + 1);
    sort(b.begin(), b.end());
    sort(c.begin(), c.end());
    if(b.size() > c.size()) {
          swap(b, c);
    }
    for(int j = 0; j < b.size(); j += 2) {
        res.pb(b[j]);
      }
    }
  }

  printf("%d \n", (int)(res.size()));
  for(int i : res) {
    printf("%d ", i + 1);
  }
  printf("\n");
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
