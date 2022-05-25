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



ll pre[500000 + 5];
void solve() {
  int n;
  cin >> n;
  ve<int> a;
  for(int i = 1; i <= (n + 1) / 2; i++) {
    int x;
    cin >> x;
    a.pb(x);
  }
  int x; cin >> x;
  W(a.size() < n) {
    a.pb(x);
  }

  pre[0] = a[0];
  for(int i = 1; i < n; i++) {
    pre[i] = pre[i - 1] + a[i];
  }
  

  if(x > 0) {
    if(pre[n - 1] > 0) {
      cout << n << endl;
    } else {
      cout << -1 << endl;
    }
  } else {
    int mid = (n + 1) / 2;
    ve<int> b;
    for(int i = 0; i < n; i++) {
      b.pb(a[i] - x);
    }

    memset(pre, 0, sizeof(pre));

    pre[n - 1] = b[n - 1];
    for(int i = n - 2; i >= 0; i--) {
      pre[i] = pre[i + 1] + b[i];
    }

    ll mn = 1000000000000000000ll;
    ve<ll> mins;
    for(int i = 0; i < n; i++) {
      mn = min(mn, pre[i]);
      mins.pb(mn);
    }

    int res = -1;
    ll sum = (x + 0ll) * (n - (n + 1) / 2);
    for(int i = mid - 1; i >= 0; i--) {
      sum += a[i];
      if(sum > 0) {
        if(i == 0) {
          res = n;
          break;
        }
        ll mmn = mins[i - 1] - pre[i];
        if(sum + mmn > 0) {
          res = n - i;
        }
      }
    }
    cout << res << endl;


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
