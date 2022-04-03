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

template <typename T>
ostream &operator<<(ostream &out, const vector<T> &a) {
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
ostream &operator<<(ostream &out, const unordered_set<T> &a) {
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
ostream &operator<<(ostream &out, const map<U, T, Cmp> &a) {
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
ostream &operator<<(ostream &out, const unordered_map<U, T, Cmp> &a) {
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


ll gcd(ll x, ll y) {
  return (y == 0 ? x : gcd(y, x % y));
}
ll lcm(ll x, ll y) {
  return x * y / gcd(x, y);
}

int to_int(string &s) {
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
int mod = 998244353;

class Solution {
public:
    int maximumCandies(vector<int>& a, ll k) {
        int n = a.size();
        ll res = 0;
        sort(a.begin(), a.end());
        ll l = 1, r = a[n - 1];
        W(l <= r) {
            ll mid = l + (r - l) / 2;
            ll cnt = 0;
            FOR(i, 0, n) {
                ll add = (a[i] + 0ll) / mid;
                cnt += add;
                if(cnt >= k) break;
            }
            if(cnt >= k) {
                res = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return (int)(res);
    }
};
