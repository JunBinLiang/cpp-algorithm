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

ve<ll> Pow = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};
ve<ll> cnt = {0, 9, 90, 900, 9000, 90000, 900000, 9000000, 90000000, 900000000};
ve<ve<ll>> a = {{}, {1, 9}, {10, 99}, {100,999}, {1000,9999}, {10000, 99999}, {100000, 999999}, {1000000, 9999999}, {10000000ll, 99999999ll}};

class Solution {
public:
    vector<long long> kthPalindrome(vector<int>& q, int k) {
        ve<ll> res;
        int half = (k + 1) / 2;
        cout << half << endl;
        FOR(i, 0, q.size()) {
            int len = q[i];
            ll first = a[half][0];
            ll last = a[half][1];
            ll total = (last - first) + 1;
            if(len > total) {
                res.pb(-1);
                continue;
            }
            
            ll num = first + len - 1;
            ll r = rev(num, k);
            num = num * Pow[k / 2] + r;
            res.pb(num);
            
        }
        return res;
    }
    
    ll rev(ll n, int k) {
        string s = to_string(n);
        if(k % 2 == 1) s.pop_back();
        reverse(s.begin(), s.end());
        ll res = 0;
        FOR(i, 0, s.size()) {
            res = res * 10 + s[i] - '0';
        }
        return res;
    }
};
