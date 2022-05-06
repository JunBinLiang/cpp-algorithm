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

/*class Compare
{
public:
    bool operator() (ve<ll>& a, ve<ll>& b)
    {
        return a[0] > b[0];
    }
    //a[0] > b[0] : min
};*/


bool COMP(pair<int, int>& p1, pair<int, int>& p2) {
  return p1.second < p2.second;
}



//0 : no
//1 : yes
//? : no info

/*int find(ve<int>& nums, int x){
  if(nums[x] == x) return x;
  int root = find(nums, nums[x]);
  nums[x] = root;
  return root;
}*/








int n, m;
const int SIZE = 252;
int dp[SIZE][SIZE][SIZE][2];
int dfs(ve<int>& a, int i, int pre, int sum) {
  if(i >= a.size()) {
    if(sum == 0) return 0;
    return 1000000000;
  }

  int state = 0;
  if(sum < 0) state = 1;
  if(dp[i][pre][abs(sum)][state] != -1) {
    return dp[i][pre][abs(sum)][state];
  }
  
  int size = n - (i);
  int x = pre;
  int all = (x) * size;
  if(all > m) {
      return 1000000000;
  }

  
  int res = 1000000000;
  for(int cur = pre; cur <= m; cur++) {
    if(pre + cur > m) break;
    int need = a[i] - cur;
    need += sum;
    if(need >= 0) {
      res = min(res, need + dfs(a, i + 1, cur, need));
    } else {
      res = min(res, dfs(a, i + 1, cur, need));
    }

  }

  if(sum < 0) res += abs(sum);
  return dp[i][pre][abs(sum)][state] = res;
}

void solve() {
  scanf("%d%d", &n, &m);
  ve<int> a(n);
  for(int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  reverse(a.begin(), a.end());
  memset(dp, -1, sizeof(dp));
  int res = 1000000000;
  for(int i = 0; i <= m; i++) {
    int need = a[0] - i;
    if(need >= 0) { //give
      res = min(res, need + dfs(a, 1, i, need));
    } else { //get
      res = min(res, dfs(a, 1, i, need));
    }
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
