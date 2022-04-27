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

/*class Compare
{
public:
    bool operator() (ve<int>& a, ve<int>& b)
    {
        return a[0] > b[0];
    }
};*/

 ll modInverse(ll a, ll m) {
    ll m0 = m;
    ll y = 0, x = 1;
    if (m == 1)
        return 0;
    while (a > 1) {
          // q is quotient
        ll q = a / m;
        ll t = m;
        // m is remainder now, process
        // same as Euclid's algo
        m = a % m;
        a = t;
        t = y;
        // Update x and y
        y = x - q * y;
        x = t;
    }
    // Make x positive
    if (x < 0)
        x += m0;
    return x;
}

int n;
int mod = 1000000007;
ll f[1000000 + 5];
ll inv[1000000 + 5];
void solve() {
  scanf("%d", &n);
  ve<int> a(n);
  FOR(i, 0, n) {
    scanf("%d", &a[i]);
  }
  sort(a.begin(), a.end());

  f[0] = 1;
  FOR(i, 1, 1000000 + 5) {
    f[i] = f[i - 1] * i;
    f[i] %= mod;
  }


  for (int i=0;i < 1000000 + 5;i++){
    inv[i] = modInverse(f[i], mod);
    inv[i] %= mod;
  }

  ll res = 0;
  for(int i = 0; i < n; i++) {
    int j = i;
    int cnt = 0;
    W(j < n && a[j] == a[i]) {
      cnt ++;
      j++;
    }
    
    if(j >= n) {
        break;
    }
    
    int right = n - (i + 1);
    ll x =  ((f[right] * f[n]) % mod * cnt) % mod;
    x *= inv[i];
    x %= mod;
    x *= inv[n - i];
    x %= mod;
    
    x *= a[i];
    x %= mod;
    x *= f[i];
    x %= mod;
    res += x;
    res %= mod;
    i = j - 1;
  }

  cout << res << endl;

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
