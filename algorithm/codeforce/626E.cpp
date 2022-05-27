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

string substring(string& s, int l, int r) {
  string res = "";
  for(int i = l; i <= r; i++) res += s[i];
  return res;
}

/*class Compare
{
public:
    bool operator() (ve<ll>& a, ve<ll>& b)
    {
        return a[0] > b[0];
    }
    //a[0] > b[0] : min
};*/

ll get(ve<ll>& a, int l, int r) {
  if(l > r) return 0;
  if(l == 0)return a[r];
  return a[r] - a[l - 1];
}

void solve() {
  int n;
  scanf("%d", &n);
  ve<int> a(n);
  FOR(i, 0, n) {
    scanf("%d", &a[i]);
  }
  sort(a.begin(), a.end());
  ve<ll> pre;
  ll sum = 0;
  for(int i : a) {
    sum += i;
    pre.pb(sum);
  }

  int index = -1, le = -1;
  double mx = -1000000000;


  for(int i = 0; i < n; i++) {
    int len = min(i, (n - i - 1));
    int l = 0, r = len;
    W(l <= r){
      int mid1 = l + (r - l )/ 3;
      int mid2 = l + (r - l) / 3 * 2;
      double total1 = get(pre, i - mid1 , i) + get(pre, n - mid1, n - 1); 
      double total2 = get(pre, i - mid2 , i) + get(pre, n - mid2, n - 1); 
      double aa = total1 / (mid1 * 2 + 1) - a[i];
      double bb = total2 / (mid2 * 2 + 1) - a[i];

      if(aa <= bb) {
        l = mid1 + 1;
      } else {
        r = mid2 - 1;
      } 
      if(aa > mx) {
        mx = aa;
        index = i;
        le = mid1;
      }
      if(bb > mx) {
        mx = bb;
        index = i;
        le = mid2;
      }
    }
  }
  

  cout << 1 + le * 2 << endl;
  ve<int> res;
  res.pb(a[index]);
  for(int i = 1; i <= le; i++) {
    res.pb(a[index - i]);
    res.pb(a[n - i]);
  }
  sort(res.begin(), res.end());
  for(int i : res) {
    cout << i << " ";
  }
  

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
