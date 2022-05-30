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

bool COMP(const ve<int>& a, const ve<int>& b) {
  return a[0] < b[0];
}

int n, m, L, s, t;
ll dis[1500];
ll dis1[1500];
int pa[1500][2];
ll INF = 100000000000ll;
int to = 1;
ve<ve<ll>> edges;

void dij(ve<ve<ve<int>>>& graph) {
  for(int i = 0; i < n + 5; i++) {
    dis[i] = INF;
  }
  queue<pair<int, ll>> q;
  q.push({s, 0});
  dis[s] = 0;
  W(q.size() > 0) {
    pair<int, ll> p = q.front(); q.pop();
    if(dis[p.first] != p.second) continue;
    for(ve<int>& a : graph[p.first]) {
      int& nxt = a[0], w = a[1];
      if(!w) continue;
      if(p.second + w < dis[nxt]) {
        dis[nxt] = p.second + w;
        q.push({nxt, dis[nxt]});
      }
    }
  }
}

void dij1(ve<ve<ve<int>>>& graph) {
  for(int i = 0; i < n + 5; i++) {
    dis1[i] = INF;
    pa[i][0] = -1;
    pa[i][1] = -1;
  }

  queue<pair<int, ll>> q;
  q.push({s, 0});
  dis1[s] = 0;
  W(q.size() > 0) {
    pair<int, ll> p = q.front(); q.pop();
    if(dis1[p.first] != p.second) continue;
    for(ve<int>& a : graph[p.first]) {
      int& nxt = a[0];
      ll w = edges[a[2]][2];
      if(!w) w = to;
      if(p.second + w < dis1[nxt]) {
        dis1[nxt] = p.second + w;
        q.push({nxt, dis1[nxt]});
        pa[nxt][0] = p.first;
        pa[nxt][1] = a[2];
      }
    }
  }
}



void solve() {
  scanf("%d%d%d%d%d", &n, &m, &L, &s, &t);
  ve<ve<ve<int>>> graph(n);
  set<int> se;
  for(int i = 0; i < m; i++) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    graph[u].pb({v, w, i});
    graph[v].pb({u, w, i});
    edges.pb({u, v, w});
    if(w == 0) se.insert(i);
  }


  dij(graph);
  if(dis[t] < L) {
    cout << "NO" << endl;
    return;
  }
  dij1(graph);
  if(dis1[t] > L) {
    cout << "NO" << endl;
    return;
  }
  

  while(true) {
    int cur = t;
    int need = ((L) - (int)(dis1[t]));
    set<int> has;
    W(cur != s) {
      int u = pa[cur][0], idx = pa[cur][1];
      if(edges[idx][2] == 0) {
        has.insert(idx);  
        if(need) {
          edges[idx][2] += need + 1;
          need = 0;
        } else {
          
        }
      }
      cur = u;
    } 

    ve<int> era;
    for(auto index : se) {
      if(has.find(index) == has.end()) {
        edges[index][2] = INF;
        era.pb(index);
      }
    }
    
    for(int index : era) {
        se.erase(index);
    }

    dij1(graph);
    if(dis1[t] == L) break; 
  }

  

  
  printf("YES \n");
  for(ve<ll>& edge : edges) {
    if(edge[2] == 0) edge[2] = 1;
    printf("%lld %lld %lld \n", edge[0], edge[1], edge[2]);
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
