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
  return p1.first > p2.first;
}



void solve() {
  int n;
  cin >> n;
  ve<int> a(n);  
  for(int i = 0; i < n; i++) {
    cin >> a[i];
  }
  int x, y;
  cin >> x >> y;
  sort(a.begin(), a.end());


  ve<int> b;
  for(int i = 0; i < a.size(); i++) {
    int j = i;
    W(j < n && a[j] == a[i]) {
      j++;
    }
    i = j - 1;
    b.pb(a[i]);
  }

  sort(b.begin(), b.end());
  int res = 0;
  W(x > y) {
    int minTo = x - 1;
    for(int i = 0; i < b.size(); i++) {
      if(x % b[i] != 0) {
        int m = x % b[i];
        if(x - m >= y) minTo = min(minTo, x - m);
      }
    }
    while(b.size() > 0 && (x - x % b[b.size() - 1]) < y)b.pop_back();
    x = minTo;
    res++;
  }
  cout << res << endl;

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
