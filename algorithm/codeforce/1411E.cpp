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
  if(p1.first == p2.first) {
    return p1.second < p2.second;
  }
  return p1.first < p2.first;
}

void solve() {
  int n; ll T;
  string s;
  cin >> n >> T >> s;
  ve<int> a;
  for(int i = 0; i < s.size(); i++) {
    a.pb(1 << (s[i] - 'a'));
  }
  ll target = T - (a[n - 1] - a[n - 2]);
  if(target < 0) target = -target;

  int cnt[26];
  memset(cnt, 0, sizeof(cnt));
  ll total = 0;
  for(int i = 0; i < n - 2; i++) {
    cnt[s[i] - 'a']++;
    total += (a[i]);
  }

  if((total < target) || (total - target) % 2 != 0) {
    cout << "NO" << endl;
    return;
  }

  target = target + (total - target) / 2;
  for(int i = 25; i >= 0; i--) {
    int bit = (1 << i);
    W(cnt[i] > 0) {
      cnt[i]--;
      if(target >= bit) target -= bit;
    }
  } 

  if(target == 0) cout << "YES" << endl;
  else cout << "NO" << endl;




  
  if(sum == 0) {
    cout << "YES" << endl;
  } else {
    cout << "NO" << endl;
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
