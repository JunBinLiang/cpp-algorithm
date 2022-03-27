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
#define W while
#define um unordered_map
#define us unordered_set
#define str string

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

bool COMP(ve<int>& a, ve<int>& b) {
  return false;
}


int MOD = 998244353;
int mod = 1000000007;


bool f1[2005];
bool f2[2005];
class Solution {
public:
    vector<vector<int>> findDifference(vector<int>& a, vector<int>& b) {
        ve<ve<int>> res(2);
        memset(f1, false, sizeof(f1));
        memset(f2, false, sizeof(f2));
        for(int i : a) f1[i + 1000] = true;
        for(int i : b) f2[i + 1000] = true;
        
        for(int i = 0; i < 2001; i++) {
            if(f1[i] && ! f2[i]) {
                res[0].pb(i - 1000);
            }
        }
        
        for(int i = 0; i < 2001; i++) {
            if(f2[i] && !f1[i]) {
                res[1].pb(i - 1000);
            }
        }
        
        return res;
    }
};
