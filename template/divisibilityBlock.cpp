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
#define RFOR(i, a, b) for (int i = a; i >= b; i--)

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

int MOD = 998244353;
int mod = 998244353;
int INF = INT_MAX;




int solve(int val) {
    int cnt = 0;
   for(int j = 1; j <= val; j++) {
      cnt++;
      if(j == val) break;
      int cnt = val / j;
      int mo = val % j;
      if(mo == 0) {
        cnt--;
        mo += j;
        int add = mo / cnt;
        if(mo % cnt == 0) {
          j += (add - 1);
        } else {
          j += add;
        }
      } else {
        int add = mo / cnt;
        if(mo % cnt == 0) {
          j += (add - 1);
        } else {
          j += add;
        }
    }
       
   }
    return cnt;
}



int main()
{
  int t = 1;
  //cin >> t;
  while (t--)
  {
   int x;
   cin >> x;
   cout << solve(x) << endl;
  }
  return 0;
}
