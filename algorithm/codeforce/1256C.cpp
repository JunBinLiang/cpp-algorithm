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

void fill(ve<int>& a, int l, int r, int to) {
  for(int i = l; i <= r; i++) a[i] = to;
}

int a[1001];
void solve() {
  int n, m, d;
  scanf("%d%d%d", &n, &m, &d);
  ve<int> res(n * 3);
  for(int i = 0; i < m; i++) {
    scanf("%d", &a[i]);
  }

  int x = 1;
  int j = 0;
  bool check = false;
  W(x <= n && j < m) {
    int l = x, r = x + d - 1; 
    if(r > n) {
        break;
    }
    fill(res, r, r + a[j] - 1, j + 1);
    x = r + a[j];
    j++;
  }
  

  if(x + d - 1 <= n) {
    printf("NO \n");
    return;
  }

  int pos = x;
  for(int i = j; i < m; i++) {
    fill(res, pos, pos + a[i] - 1, i + 1);
    pos += a[i];
  }
  
  //cout << res << endl;

  //shift
  int cnt = 0;
  for(int i = n + 1; i < res.size(); i++) {
    if(res[i] != 0) cnt++;
  }

  j = 1;
  for(int i = 0; i < cnt; i++) {
    W(res[j] != 0) j++;
    //shift
    for(int k = j; k < res.size() - 1; k++) {
      res[k] = res[k + 1];
    }
  }
  


  printf("YES \n");
  for(int i = 1; i <= n; i++) {
    printf("%d ", res[i]);
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
