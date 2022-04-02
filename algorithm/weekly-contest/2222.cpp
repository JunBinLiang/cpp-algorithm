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



int l[100000 + 10];
int r[100000 + 10];
class Solution {
public:
    // [0,1,0] [1,0 1]
    long long numberOfWays(string s) {
        int n = s.size();
        ll res = 0;
        int cnt = 0;
        FOR(i, 0, n) {
            if(s[i] == '0') {
                cnt++;
            }
            l[i] = cnt;
        }
        
        cnt = 0;
        for(int i = n - 1; i >= 0; i--) {
            if(s[i] == '0')cnt++;
            r[i] = cnt;
        }
        
        
        
        FOR(i, 1, n - 1) {
            if(s[i] == '1') {
                ll a = l[i - 1], b = r[i + 1];
                res += a * b;
            }
        }
        
        
        cnt = 0;
        FOR(i, 0, n) {
            if(s[i] == '1') {
                cnt++;
            }
            l[i] = cnt;
        }
        
        cnt = 0;
        for(int i = n - 1; i >= 0; i--) {
            if(s[i] == '1')cnt++;
            r[i] = cnt;
        }
        
        
        FOR(i, 1, n - 1) {
            if(s[i] == '0') {
                ll a = l[i - 1], b = r[i + 1];
                res += a * b;
            }
        }
        
        return res;
    }
    
    
    
};
