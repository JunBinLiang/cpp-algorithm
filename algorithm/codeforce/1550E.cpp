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


int INF = 1000000000;

int get(ve<int>& a, int l, int r) {
  if(l == 0) return a[r];
  return a[r] - a[l - 1];
}

int find(ve<int>& a, int t) {
  int l = 0, r = a.size() - 1;
  int res = -1;
  W(l <= r) {
    int mid = l + (r - l) / 2;
    if(a[mid] > t) {
      res = mid;
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  if(res != -1) return a[res];
  return res;
}


bool check(string& s,ve<ve<int>>& pre, int mid, int k) {
  int n = s.size();
  int dp[(1 << k) + 10];
  for(int i = 0; i <= (1 << k) + 5; i++) {
    dp[i] = INF;
  }
  
  ve<ve<int>> a(26);
  for(int i = 0; i < k; i++) {
    for(int j = 0; j < s.size(); j++) {
      if(j + mid - 1 >= n) break;
      if(s[j] == '?' || (s[j] - 'a') == i) {
        int sum = get(pre[i], j, j + mid - 1);
        if(sum == mid) {
          a[i].pb(j);
        }
      }
    }
  }

  dp[0] = -1;
  for(int state = 1; state < (1 << k); state++) {
    for(int j = 0; j < k; j++) {
      if(state & (1 << j)) {
        int last = state ^ (1 << j);
        if(dp[last] == INF) continue;
        int nxt = find(a[j], dp[last]);
        if(nxt != -1) {
          dp[state] = min(dp[state], nxt + mid - 1);
        }
      }
    }
  }

  return dp[(1 << k) - 1] != INF;
}

void solve() {
  int n, k;
  cin >> n >> k;
  string s;
  cin >> s;
  ve<ve<int>> pre(26, ve<int>(n));
  for(int i = 0; i < 26; i++) {
    int sum = 0;
    for(int j = 0; j < s.size(); j++) {
      if(s[j] == '?' || (s[j] - 'a') == i) {
        sum++;
      }
      pre[i][j] = sum;
    }
  }

  set<char> se;
  int cnt = 0;
  for(int i = 0; i < s.size(); i++) {
    if(s[i] == '?') cnt++;
    else se.insert(s[i]);
  }

  if(se.size() + cnt < k) {
    printf("0 \n");
    return;
  }



  int l = 1, r = n, res = -1;
  W(l <= r) {
    int mid = l + (r - l) / 2;
    if(check(s, pre, mid, k)) {
      res = mid;
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  printf("%d \n", res);
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
