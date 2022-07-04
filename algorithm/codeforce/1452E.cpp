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


struct Tuple {
  int l, r, idx;
};

bool COMP(pair<int, int>& p1, pair<int, int>& p2) {
  return p1.first < p2.first;
}

int over(int l1, int r1, int l2, int r2) {
  ve<pair<int, int>> a;
  a.pb({l1, r1}); a.pb({l2, r2});
  sort(a.begin(), a.end(), COMP);
  if(a[1].first > a[0].second) return 0;
  int x = a[1].first, y = min(a[0].second, a[1].second);
  return y - x  + 1;
}

int ans[2005];
int dp1[2005][2005];
int dp2[2005][2005];
int dis[2005][2005];
int maxs[2005];
void solve() {
  int n, m, k;
  int res = 0;
  scanf("%d%d%d", &n, &m, &k);
  ve<pair<int, int>> a;
  for(int i = 0; i < m; i++) {
    int l, r;
    scanf("%d%d", &l, &r);
    a.pb({l, r});
  }
  

  for(int i = 0; i < m; i++) {
    int mx = -1, index = -1;
    for(int j = 0; j <= n; j++) {
      if(j + k - 1 > n) break;
      int l = j, r = j + k - 1;
      dis[i][j] = over(l, r, a[i].first, a[i].second);
      if(dis[i][j] > mx) {
        mx = dis[i][j];
        index = j;
      }
    }
    maxs[i] = index;
  }
  
  /*for(int i = 0; i <= n; i++) {
      cout << dis[0][i] << " ";
  }cout << endl; cout << endl;*/
  
  for(int i = 0; i <= n; i++) {
    if(i + k - 1 > n) break;
    int l = i, r = i + k - 1;
    for(int j = 0; j < a.size(); j++) {
      pair<int, int>& p = a[j];
      int in = dis[j][i];
      ans[i] += in;
      if(in == 0) continue;
      int index = maxs[j];
      if(in <= dis[j][i + 1]) {
        dp1[i][i + 1] -= in;
        int l = index, r = n - 1;
        int pos = -1;
        W(l <= r) {
          int mid = l + (r - l) / 2;
          if(dis[j][mid] < in) {
            pos = mid;
            r = mid - 1;
          } else {
            l = mid + 1;
          }
        } 
        if(pos != -1) {
          dp1[i][pos] += in;
        }
      }
    }
    for(int j = i + 1; j <= n; j++) {
      dp1[i][j] += dp1[i][j - 1];  
    }
    res = max(res, ans[i]);
  }


  for(int i = n; i >= 1; i--) {
    if(i + k - 1 > n) continue;
    int l = i, r = i + k - 1;
    for(int j = 0; j < a.size(); j++) {
      pair<int, int>& p = a[j];
      int in = dis[j][i];
      if(in == 0) continue;
      //when start to shift
      int index = maxs[j];
      
      if(in < dis[j][i - 1]) {
        dp2[i][i - 1] -= in;
        int r = index, l = 0;
        int pos = -1;
        W(l <= r) {
          int mid = l + (r - l) / 2;
          if(dis[j][mid] <= in) {
            pos = mid;
            l = mid + 1;
          } else {
            r = mid - 1;
          }
        } 
        if(pos != -1) {
          dp2[i][pos] += in;
        }
      }
    }
    
    for(int j = i - 1; j >= 0; j--) {
      dp2[i][j] += dp2[i][j + 1];  
    }
  }




  for(int i = 0; i <= n; i++) {
    if(i + k - 1 > n) break;
    for(int j = i + 1; j <= n; j++) {
      if(j + k - 1 > n) break;
      res = max(res, ans[i] + ans[j] + dp1[i][j] + dp2[j][i]);
    }
  }
  printf("%d \n", res);
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
