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


int L, n;
bool check1(ve<int>& a, int mid) {
  int pre = 0;
  for(int i = 0; i < a.size(); i++) {
    pre = max(a[i], pre + mid);
    if(i + 1 < a.size() && pre > a[i + 1]) {
      return false;
    }
  }
  return true; 
}

bool check2(ve<int>& a, int mid) {
  int pre = 0;
  for(int i = 0; i < a.size() - 1; i++) {
    if(pre + mid < a[i]) return false;
    pre = min(pre + mid, a[i + 1]);
  }

  if(pre + mid < L) {
    return false;
  }  
  return true;
}

void solve() {
  scanf("%d%d", &L, &n);
  ve<int> a(n);
  for(int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }

  int mn = -1, mx = 1;
  int l = 1, r = L;
  W(l <= r) {
    int mid = l + (r - l) / 2;
    if(check1(a, mid)) {
      mn = mid;
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }

  l = 1; r = L;
  W(l <= r) {
    int mid = l + (r - l) / 2;
    if(check2(a, mid)) {
      mx = mid;
      r = mid - 1;
    } else {  
      l = mid + 1;
    }
  }

  ve<int> res;
  res.pb(0);
  for(int i = 0; i < n - 1; i++) {
    int pre = res[i];
    res.pb(min(a[i + 1], pre + mx));
  }
  res.pb(L);


  for(int i = res.size() - 1; i >= 1; i--) {
    if(res[i] - res[i - 1] < mn) {
      res[i - 1] = res[i] - mn;
    }
  }
  

  for(int i = 1; i < res.size(); i++) {
    printf("%d %d \n", res[i - 1], res[i]);
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
