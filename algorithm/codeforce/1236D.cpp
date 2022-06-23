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

int find1(ve<int>& a, int t, int cut) {
  int l = 0, r = a.size() -1;
  int pos = -1;
  //cout << a << endl;
  W(l <= r) {
    int mid = l + (r - l) / 2;
    //cout << " " << l << " " << r << " " << mid << " " << a[mid] << " " << cut << endl;
    if(a[mid] > cut) {
      r = mid - 1;
      continue;
    }
    if(a[mid] >= t) {
      pos = mid;
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  if(pos == -1) {
    if(cut > t) return cut + 1;
    return -2;
  }
  return a[pos];
}

int find2(ve<int>& a, int t, int cut) {
  int l = 0,  r = a.size() - 1;
  int pos = -1;
  //cout << a <<" " << cut << endl;
  W(l <= r) {
    int mid = l + (r - l) / 2;
    if(a[mid] < cut) {
      l = mid + 1;
      continue;
    }
    if(a[mid] <= t) {
      pos = mid;
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
 // cout << pos << endl;
  if(pos == -1) {
    if(cut < t) return cut - 1;
    return -2;
  }
  return a[pos];
}

ve<ve<int>> dir = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
ve<int> rows[100000 + 5];
ve<int> cols[100000 + 5];
void solve() {
  int n, m, k;
  ll res = 0;
  int d = 0;
  scanf("%d%d%d", &n, &m, &k);

  for(int i = 0; i < n; i++) {
    rows[i].pb(-1);
    rows[i].pb(m);
  }

  for(int i = 0; i < m; i++) {
    cols[i].pb(-1);
    cols[i].pb(n);
  }

  for(int i = 0; i < k; i++) {
    int r, c;
    scanf("%d%d", &r, &c);
    r--; c--;
    rows[r].pb(c);
    cols[c].pb(r);
    if(r == 0 && c == 1) d++;
  }
  
  if(m == 1) d = 1;

  for(int i = 0; i < n; i++) {
    sort(rows[i].begin(), rows[i].end());
  }

  for(int i = 0; i < m; i++) {
    sort(cols[i].begin(), cols[i].end());
  }


  
  int r = 0, c = 0;
  int mnr = -1, mxr = n, mnc = -1, mxc = m;
 // cout << r + 1 << " " << c + 1 <<  endl;

  res++;
  W(true) {
    int add = 0;
    if(d == 0) {
      int to = find1(rows[r], c, mxc);
      if(to == -2) break;
      add = (to - c - 1);
      res += add;
      c = to - 1;
      mnr = r + 1;
    }
    else if(d == 1) {
      int to = find1(cols[c], r, mxr);
      if(to == -2) break;
      add = (to - r - 1);
      res += add;
      r = to - 1;
      mxc = c - 1;

    } else if(d == 2) {
        int to = find2(rows[r], c, mnc);
        if(to == -2) break;
        add = (c - to - 1);
        res += add;
        c = to + 1;
        mxr = r - 1;
    } else {
      int to = find2(cols[c], r, mnr);
      if(to == -2) break;
      add = (r - to - 1);
      res += add;
      r = to + 1;
      mnc = c + 1;
    }
   // cout  << "  "<< r + 1 << " " << c + 1 <<" " << add << endl;
    //cout << mnr << " " << mxr << "      " << mnc << " " << mxc << endl;
    //cout << endl;
    d++;
    d %= 4;
    if(add == 0) break;
  }

  if(res + k == (n + 0ll) * (m + 0ll)) {
    cout << "YES" << endl;
  } else {
    cout << "NO" << endl;
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
