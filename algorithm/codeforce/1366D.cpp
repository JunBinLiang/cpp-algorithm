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

int MOD = 998244353;
int mod = 998244353 ;



int res1[500000 + 100];
int res2[500000 + 100];
int p[10000001];
void solve() {
 
  memset(p, 0, sizeof(p));
  int MAX = 10000000;
  for(int i = 2; i <= MAX; i++) {
    if(p[i] != 0) continue;
    for(int j = i; j <= MAX; j += i) {
      if(p[j] == 0) p[j] = i;
    }
  }

  int n;
  scanf("%d", &n);
  FOR(i, 0, n) {
    int x;
    scanf("%d", &x);
    if(p[x] == x) {//prime
      res1[i] = res2[i] = -1;
    } else {
      int X = x;
      int p1 = p[x];
      W(x % p1 == 0) x /= p1;
      if(x == 1) {
        res1[i] = res2[i] = -1;
      } else {
        res1[i] = p1;
        res2[i] = x;
      }
    }
  }
  




  FOR(i, 0, n) {
    printf("%d ", res1[i]);
  }
  printf("\n");
  FOR(i, 0, n) {
    printf("%d ", res2[i]);
  }
  printf("\n");

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
