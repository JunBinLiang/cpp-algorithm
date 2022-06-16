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

char flip(char c) {
  if(c == 'W') return 'B';
  else return 'W';
}


bool is[200000 + 500];
void solve() {
  int n, k;
  cin >> n >> k;
  string s;
  cin >> s;
  int kk = k;
  memset(is, false, sizeof(is));
  int cnt = 0;
  for(int i = 0; i < n; i++) {
    int pre = (i - 1 + n) % n;
    int nxt = (i + 1) % n;
    if(s[i] != s[nxt] && s[i] != s[pre]) {
      is[i] = true;
      cnt++;
    } else {

    }
  }
  

  if(is[0] && is[n - 1]) {
    if(cnt == n) {
      for(int i = 0; i < n; i++) {
        if(k % 2 == 1) {
          s[i] = flip(s[i]);
        }
      }
    } else {
      ve<pair<int, int>> a;
      for(int i = 0; i < n; i++) {
        if(!is[i]) continue;
        int j = i;
        W(j < n && is[j]) {
          j++;
        }
        a.pb({i, j - 1});
        i = j - 1;
      }

      for(int i = 0; i < a.size(); i++) {
        int l = a[i].first, r = a[i].second;
        if(l == 0 || r == n - 1) continue;
        char x = s[l], y = s[r];
        if(x == 'W') x = 'B';
        else x = 'W';

        if(y == 'W') y = 'B';
        else y = 'W';

        int cnt = 0;
        W(l <= r && cnt < k) {
          cnt++;
          s[l] = x;
          s[r] = y;
          l++;
          r--;  
        }
        for(int j = l; j <= r; j++) {
          if(k % 2 == 1) {
            s[j] = flip(s[j]);
          }
        }
      }

      int l = -1 , r = -1;
      
      int total = 0;
      for(int i = 0; i < n; i++) {
        if(is[i]) l = i;
        else break;
      }
      for(int i = n - 1; i >= 0; i--) {
        if(is[i]) r = i;
        else break;
      }

      total = (l + 1) + (n - r);
      int add = 0;
      

      char xx = flip(s[l]); char yy = flip(s[r]);
      W(k > 0) {
        s[l] = xx;
        s[r] = yy;
        if(l == r) add++;
        else add += 2;
        l--;
        r++;
        l += n; l %= n;
        r %= n;
        k--;
        if(add >= total) break;
      }
      
      if(add < total) {
        W(true) {
          if(kk % 2 == 1) s[l] = flip(s[l]);
          if(l == r) break;
          l--;
          if(l < 0) l += n;
        }
      }

    }
    cout << s << endl;
    
  } else {
    ve<pair<int, int>> a;
    for(int i = 0; i < n; i++) {
      if(!is[i]) continue;
      int j = i;
      W(j < n && is[j]) {
        j++;
      }
      a.pb({i, j - 1});
      i = j - 1;
    }

    for(int i = 0; i < a.size(); i++) {
      int l = a[i].first, r = a[i].second;
      char x = s[l], y = s[r];
      if(x == 'W') x = 'B';
      else x = 'W';

      if(y == 'W') y = 'B';
      else y = 'W';
      
      int cnt = 0;
      W(l <= r && cnt < k) {
        cnt++;
        s[l] = x;
        s[r] = y;
        l++;
        r--;  
      }
      for(int j = l; j <= r; j++) {
        if(k % 2 == 1) {
          s[j] = flip(s[j]);
        }
      }
    }
    cout << s << endl;
  }



}

int main()
{

  int t = 1;
  //cin >> t;
  int x = 1;
  W (t--)
  {
    solve();
  }
  return 0;
}
