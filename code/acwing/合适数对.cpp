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

int h(int n, int k) {
  int res = 1;
  for(int i = 2; i <= n / i; i++) {
    if(n % i == 0) {
      int a = 0;
      while(n % i == 0) n /= i, a++;
      a %= k;
      while(a > 0) {
        a--;
        res *= i;
      }
    }
  }
  
  if(n > 1) {
    res *= n;
  }
  return res;
}

int f[100000 + 5];
void solve(ve<int>& a, int k) {
  const int LIMIT = 100000;
  int n = a.size();
  ll res = 0;
  memset(f, 0, sizeof(f));
  FOR(i, 0, n) {
    int num = a[i];
    ll need = 1;
    bool flag = true;
    for(int j = 2; j <= num / j && flag; j++) {
      if(num % j == 0) {
        int t = 0;
        while(num % j == 0) num /= j, t++;
        t %= k;
        if(k - t != 0) {
          FOR(index, 0, (k - t) % k) {
            need *= j;
            if(need > LIMIT) {
              flag = false;
              break;
            }
          }  
        }
      }
    }
    
    if(num > 1) {
      FOR(index, 0, (k - 1) % k) {
          need *= num;
          if(need > LIMIT) {
            flag = false;
            break;
          }
      } 
    }
    

    if(flag) {
      res += f[need];
    }
    f[h(a[i], k)]++;
  }
  cout << res << endl;
}




int main()
{
  int t = 1;
  //cin >> t;
  W (t--)
  {
    int n, k;
    scanf("%i", &n);
    scanf("%i", &k);
    ve<int> a(n);
    FOR(i, 0, n) {
      scanf("%i", &a[i]);
    }
    solve(a, k);
  }
  return 0;
}
