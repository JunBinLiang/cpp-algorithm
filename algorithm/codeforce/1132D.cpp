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

bool COMP(ve<int>& a, ve<int>& b) {
  return a[0] < b[0];
}



int n, k;
ll a[200000 + 5];
int b[200000 + 5];

struct Node {
    ll first, x;
    int index;
};

class Compare
{
public:
    bool operator() (Node& a, Node& b)
    {
        return a.first > b.first;
    }
    //a[0] > b[0] : min
};


bool check(ll& mid) {
  priority_queue<Node, ve<Node>, Compare> pq;
  for(int i = 0; i < n; i++) {
    //find first day it will be negative
    ll first = a[i] / b[i] + 1;
    if(first >= k) continue;
    pq.push({first, a[i], i});
  }

  for(int i = 1; i < k && pq.size() > 0; i++) {
    Node pa = pq.top(); pq.pop();
    if(pa.first < i) return false;
    ll& x = pa.x;
    x += mid;
    pa.first = x / b[pa.index] + 1;
    if(pa.first <= i) return false;
    if(pa.first >= k) continue;
    pq.push(pa);
  }
  
  if(pq.size() > 0) {
      Node pa = pq.top(); pq.pop();
      if(pa.first < k) return false;
  }
  return true;
}

void solve() {
  scanf("%d%d", &n, &k);
  for(int i = 0; i < n; i++) {
    scanf("%lld", &a[i]);
  }
  
  for(int i = 0; i < n; i++) {
    scanf("%d", &b[i]);
  }

  ll l = 0, r = 2000000000000ll;
  ll res = -1;
  W(l <= r) {
    ll mid = l + (r - l) / 2;
    if(check(mid)) {
      res = mid;
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  printf("%lld", res);

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
