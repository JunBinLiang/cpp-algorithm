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
    bool operator() (pair<int, int>& a, pair<int, int>& b)
    {
        return a.first > b.first;
    }
    //a[0] > b[0] : min
};*/

bool COMP(const pair<int, int>&p1, const pair<int, int>&p2) {
  return p1.second < p2.second;
}

bool same(ve<int>& a, ve<int>& b) {
  for(int i = 0; i < a.size(); i++) {
    if(a[i] != b[i]) {
      return false;
    }
  }
  return true;
}

void solve() {
  int n;
  scanf("%d", &n);
  ve<int> a(n);
  ve<int> b(n);
  for(int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    b[i] = a[i];
  }
  sort(b.begin(), b.end());

  ve<int> res;
  for(int i = 0; i < n; i++) {
    if(a[i] == b[i]) continue;
    int idx = -1;
    for(int j = i + 1; j < n; j++) {
      if(a[j] == b[i]) {
        idx = j;
        break;
      }
    }
    
    //cout << i << " " << idx <<" " << a << endl;

    while(idx - i >= 2) {
      res.pb(idx - 2);
      int x = a[idx], y = a[idx - 1], z = a[idx - 2];
      a[idx - 2] = x;
      a[idx - 1] = z;
      a[idx] = y;
      idx -= 2;
      
     // cout << a << endl;
    }

    if(idx != i) {
      if(idx + 1 < n && idx != -1) {
        res.pb(idx - 1);
        int x = a[idx - 1], y = a[idx], z = a[idx + 1];
        a[idx - 1] = z;
        a[idx] = x;
        a[idx + 1] = y;


        idx--;
        res.pb(idx);
        x = a[idx];
        y = a[idx + 1];
        z = a[idx + 2];
        a[idx] = z;
        a[idx + 1] = x;
        a[idx + 2] = y;
      }
    }
  }
  
 // cout << a << endl;

  if(a[n - 1] < a[n - 2]) {
    int j = n - 3;
    while(j >= 0) {
      if(same(a, b)) break;
      res.pb(j);
      int x = a[j], y = a[j + 1], z = a[j + 2];
      a[j] = z;
      a[j + 1] = x;
      a[j + 2] = y;
      j--;
      //cout << a << endl;
    }
  }
  
  //cout << a << endl;

  if(!same(a, b) || res.size() > n * n) {
    printf("-1 \n");
    return;
  }


  printf("%d \n", res.size());
  for(int i : res) {
    printf("%d ", i + 1);
  }
  printf("\n");

  
}

int main()
{

  int t = 1;
  cin >> t;
  W (t--)
  {
    solve();
  }
  return 0;
}
