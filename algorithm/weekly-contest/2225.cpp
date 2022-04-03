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
    vector<vector<int>> findWinners(vector<vector<int>>& a) {
        ve<ve<int>> res(2);
        um<int, int> f;
        for(ve<int>& b : a) {
            for(int i : b) {
                f[i] = 0;
            }
        }
        
        for(ve<int>& b : a) {
            int lost = b[1];
            f[lost]++;
        }
        
        for(auto it = f.begin(); it != f.end(); it++) {
            int x = it -> first;
            int y = it -> se;
            if(y == 0) {
                res[0].pb(x);
            }
            if(y == 1) {
                res[1].pb(x);
            }
        }
        sort(res[0].begin(), res[0].end());
        sort(res[1].begin(), res[1].end());
        return res;
        
    }
};
