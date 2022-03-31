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
#define str string

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
  return false;
}

int MOD = 998244353;
int mod = 1000000007;

int res[100000 + 10];
int flip[2000];
int rows[1001];
int mat[1001][1001];
bool is[100005];
int cur = 0;
int n, m, q;
void add(ve<int>& q, int index){
  int op = q[0];
  //cout <<q.size() << q << endl;
  if(op == 1) {
    int i = q[1], j = q[2];
    if((mat[i][j] + flip[i]) % 2 == 0) {
      mat[i][j]++;
      mat[i][j] %= 2;
      rows[i]++;
      cur++;
      is[index] = true;
    }
  }
  else if(op == 2) {
    int i = q[1], j = q[2];
    if((mat[i][j] + flip[i]) % 2 == 1) {
      mat[i][j]--;
      if(mat[i][j] < 0) mat[i][j] += 2;
      rows[i]--;
      cur--;
      is[index] = true;
    }
  }
  else if(op == 3) {
    int i = q[1];
    flip[q[1]]++;
    cur -= rows[i];
    rows[i] = m - rows[i];
    cur += rows[i];
    is[index] = true;
  }
}

void revert(ve<int>& q, int index) {
  if(!is[index]){
    return;
  }

  int op = q[0];
  if(op == 1) {
    int i = q[1], j = q[2];
    if((mat[i][j] + flip[i]) % 2 == 1) {
      mat[i][j]--;
      if(mat[i][j] < 0) mat[i][j] += 2;
      rows[i]--;
      cur--;
    }
  }
  else if(op == 2) {
    int i = q[1], j = q[2];
    if((mat[i][j] + flip[i]) % 2 == 0) {
      mat[i][j]++;
      mat[i][j] %= 2;
      rows[i]++;
      cur++;
    }
  }
  else if(op == 3) {
    int i = q[1];
    flip[q[1]]--;
    cur -= rows[i];
    rows[i] = m - rows[i];
    cur += rows[i];
  }
}

void dfs(ve<ve<int>> &graph, ve<ve<int>> &a, int pa, int root) {
  res[root] = cur;
  

  for(int &next : graph[root]) {
    ve<int>& q = a[next - 1];
    

    /*cout <<"before  " << root << " " <<  next << endl;
  FOR(i,0, n + 1) {
    cout << flip[i] << " ";
  }
  cout << endl;
  FOR(i, 0, n + 1) {
    FOR(j, 0, m + 1) {
      cout << mat[i][j] << " ";
    }cout << endl;
  }
  cout << endl;*/
    add(q, next);
    dfs(graph, a, root, next);
    revert(q, next);

     /* cout <<"after  " << root << " " <<  next << endl;
  FOR(i,0, n + 1) {
    cout << flip[i] << " ";
  }
  cout << endl;
  FOR(i, 0, n + 1) {
    FOR(j, 0, m + 1) {
      cout << mat[i][j] << " ";
    }cout << endl;
  }
  cout << endl;*/
  }
}

void solve() {
  scanf("%i", &n);
  scanf("%i", &m);
  scanf("%i", &q);
  memset(res, 0, sizeof(res));
  memset(flip, 0, sizeof(flip));
  memset(mat, 0, sizeof(mat));
  memset(rows, 0, sizeof(rows));
  memset(is, false, sizeof(is));
  ve<ve<int>> graph(q + 1);
  ve<ve<int>> a;
  
  FOR(i, 1, q + 1) {
    int op;
    scanf("%i", &op);
    int r, c;
    if(op == 1) {
      scanf("%i", &r); scanf("%i", &c);
      a.pb({op, r, c});
    }
    if(op == 2) {
      scanf("%i", &r); scanf("%i", &c);
      a.pb({op, r, c});
    }
    if(op == 3) {
      scanf("%i", &r);
      a.pb({op, r});
    }
    if(op == 4) {
      int k;
      scanf("%i", &k);
      a.pb({op});
      graph[k].pb(i);
    }

    if(i > 0 && op != 4) {
      graph[i - 1].pb(i);
    }
  }

  dfs(graph, a, -1, 0);

  for(int i = 1; i <= q; i++) {
    printf("%d\n", res[i]);
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
