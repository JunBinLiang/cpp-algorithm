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

/*class Compare
{
public:
    bool operator() (ve<ll>& a, ve<ll>& b)
    {
        return a[0] > b[0];
    }
    //a[0] > b[0] : min
};*/


bool COMP(pair<int, int>& p1, pair<int, int>& p2) {
  return p1.second < p2.second;
}

set<int> sets[200000 + 10];
int cnt[200000 + 10];
int sizes[200000 + 10];
void solve() {
  int n, k;
  scanf("%d%d", &n, &k);
  int res = 0;
  for(int i = 0; i < n; i++) {
    sets[i].clear();
    cnt[i] = 0;
  }

  for(int i = 0; i < n - 1; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--;
    v--;
    sets[u].insert(v);
    sets[v].insert(u);
  }

  for(int i = 0; i < n; i++) {
    sizes[i] = sets[i].size();
  }

  queue<int> q;
  for(int i = 0; i < n; i++) {
    if(sets[i].size() == 1) {
      q.push(i);
    }
  }
  //cout << sizes[2] << endl;

  W(q.size() > 0) {
    int root = q.front(); q.pop();
    if(cnt[root] != sizes[root] - 1) continue;
    int pa = *(sets[root].begin());
    sets[pa].erase(root);
    cnt[pa]++;
    if(cnt[pa] == sizes[pa] - 1) { //become leafs
      if(cnt[pa] % k == 0) {
        q.push(pa);
      }
    }
  }
  for(int i = 0; i < n; i++) {
    res += cnt[i] / k;
  }
  printf("%d \n", res);

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
