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
  return a[2] < b[2];
}

int MOD = 998244353;
int mod = 998244353;

int res[250];
bool seen[205];
bool check(ve<ve<int>>&a, int x, int y) {
  res[0] = x;
  res[1] = y;
  int index = 2;

  W(index <= a.size()) {
    bool find = false;
    FOR(i, 0, a.size()) {
      if(seen[i]) continue;
      ve<int>& b = a[i];
      set<int> se(b.begin(), b.end());
      for(int j = index - 1; j >= 0; j--) {
        if(se.find(res[j]) == se.end()) {
          break;
        } else {
          se.erase(res[j]);
        }
      }


      if(se.size() == 1) {
        find = true;
        int x = *(se.begin());
        res[index++] = x;
        seen[i] = true;
        break;
      } else {
        continue;
      }
    }

    if(!find) {
      return false;
    }
  }

  return true;
}

void solve(int t) {
  int n;
  scanf("%d", &n);
  
  ve<ve<int>> a;
  FOR(i, 0, n - 1) {
    int m;
    scanf("%d", &m);
    ve<int> b(m);
    FOR(j, 0, m) {
      scanf("%d", &b[j]);
    }
    a.pb(b);
    //cout<<"read " <<  b << endl;
  }

  FOR(i, 0, a.size()) {
    ve<int>& b = a[i];
    if(b.size() != 2) continue;
    //possible start
    memset(seen, false, sizeof(seen));
    seen[i] = true;
    bool g1 = check(a, b[0], b[1]);
    if(g1)break;
    memset(seen, false, sizeof(seen));
    seen[i] = true;
    bool g2 = check(a, b[1], b[0]);
    if(g2)break;
  }



  FOR(i, 0, n) {
    printf("%d ", res[i]);
  }
  printf("\n");
}


int main()
{
  int t = 1;
  cin >> t;
  int cnt = 1;
  W (t--)
  {
    solve(cnt);
    cnt++;
  }
  return 0;
}
