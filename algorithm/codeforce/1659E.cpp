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

int find(ve<int>& nums, int x){
  if(nums[x] == x) return x;
  int root = find(nums, nums[x]);
  nums[x] = root;
  return root;
}

void merge(ve<int>&nums, int r1, int r2) {
  nums[r1] = r2;
}

bool is[100000 + 500];
bool good[31][100000 + 500];
void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  ve<ve<int>> nums(31, ve<int>(n, 0));
  ve<ve<int>> nums1(31, ve<int>(n, 0));
  for(int i = 0; i < 31; i++) {
    for(int j = 0; j < n; j++) {
      nums[i][j] = j;nums1[i][j] = j;
    }
  }
  
  for(int i = 0; i < m; i++) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    u--; v--;
    for(int j = 0; j < 31; j++) {
      if(w & (1 << j)) {
        int r1 = find(nums[j], u);
        int r2 = find(nums[j], v);
        if(r1 != r2) {
          merge(nums[j], r1, r2);
        }
      } else {

      }
    }
    
    if(w % 2 == 1) {
      for(int j = 1; j < 31; j++) {
        if(w & (1 << j)) {
          int r1 = find(nums1[j], u);
          int r2 = find(nums1[j], v);
          if(r1 != r2) {
            merge(nums1[j], r1, r2);
          }
        }
      }
    } else {
      is[u] = is[v] = true;
    }
  }
  
  for(int j = 1; j < 31; j++) {
    for(int i = 0; i < n; i++) {
      if(is[i]) {
        int r = find(nums1[j], i);
        good[j][r] = true;
      }
    }
  }
  

  //answer can only be 0 1 2
  int q;
  scanf("%d", &q);
  W(q--) {
    int u, v;
    scanf("%d%d", &u, &v);
    bool x = false;
    u--;
    v--;
    for(int j = 0; j < 31; j++) {
      int r1 = find(nums[j], u);
      int r2 = find(nums[j], v);
      if(r1 == r2) {
        x = true;
        break;
      }
    }
    
    if(x) {
      printf("%d\n", 0);
    } else {
      bool y = false;
      for(int j = 1; j < 31; j++) {
        int r1 = find(nums1[j], u);
        if(good[j][r1]) {
          y = true;
          break;
        }
      }
      if(y) {
        printf("%d\n", 1);
      } else {
        printf("%d\n", 2);
      }
    }
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
