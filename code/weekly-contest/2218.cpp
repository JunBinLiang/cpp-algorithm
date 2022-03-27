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


int f[2005][2005];
int Next[2005];
class Solution {
public:
    int maxValueOfCoins(vector<vector<int>>& piles, int k) {
        ve<int> a;
        int sum = 0, j = 0;
        for(ve<int>& pile : piles) {
            sum += pile.size();
            for(int i : pile) {
                a.pb(i);
                Next[j++] = sum;
            }
        }
        FOR(x, 0, a.size() + 1) {
            FOR(y, 0, k + 1) {
                f[x][y] = -1;
            }
        }
        return dfs(a, 0, k);
    }
    
    int dfs(ve<int>& a, int i, int k) {
        if(i >= a.size()) {
            return 0;
        }
        if(k == 0) {
            return 0;
        }
        if(f[i][k] != -1) {
            return f[i][k];
        }
        
        int res = 0;
        res = max(res, a[i] + dfs(a, i + 1, k - 1));
        res = max(res, dfs(a, Next[i], k));
        return f[i][k] = res;
    }
};
