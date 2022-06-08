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

class Compare
{
public:
    bool operator() (pair<int, int>& a, pair<int, int>& b)
    {
        return a.first > b.first;
    }
    //a[0] > b[0] : min
};

struct Seg {
  int c, l, r, i;
};

bool COMP(const Seg& a, const Seg& b) {
  return a.l < b.l;
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


void solve() {
  int n;
  scanf("%d", &n);
  ve<int> nums(n);
  ve<Seg> a;
  for(int i = 0; i < n; i++) {
    int c, l , r;
    scanf("%d%d%d", &c, &l, &r);
    nums[i] = i;
    a.pb({c, l, r, i});
  }

  sort(a.begin(), a.end(), COMP);
  priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq1; //blue
  priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> pq2; // red

  /*for(int i = 0; i < a.size(); i++) {
      cout << a[i].c << " " << a[i].l << "  " << a[i].r << endl;
  }*/

  for(int i = 0; i < a.size(); i++) {
    int j = i;
    ve<int> b;
    W(j < a.size() && a[j].c == a[i].c) {
      b.pb(j);
      j++;
    }
    
    if(a[i].c == 0) { //blue
      ve<pair<int, int>> c;
      W(pq2.size() > 1) {
        pair<int, int> p = pq2.top(); pq2.pop();
        c.pb(p);
      }

      if(c.size() > 0) {
        pair<int, int> p = pq2.top();
        for(pair<int, int>& p1 : c) {
          if(p1.first < a[b[0]].l) continue;
          int r1 = find(nums, p.second);
          int r2 = find(nums, p1.second);
          merge(nums, r1, r2);
        }
      }
      if(pq2.size() > 0) {
        pair<int, int> p = pq2.top();
        for(int j = 0; j < b.size(); j++) {
          if(p.first >= a[b[j]].l) {
            int r1 = find(nums, a[b[0]].i);
            int r2 = find(nums, a[b[j]].i);
            merge(nums, r1, r2);
          } else {
            break;
          }
        } 
        if(p.first >= a[b[0]].l) {
            int r1 = find(nums, a[b[0]].i);
            int r2 = find(nums, p.second);
            merge(nums, r1, r2);
        }
      }
      
      for(int& idx : b) {
        pq1.push({a[idx].r, a[idx].i});
      }

    } else { //red
      ve<pair<int, int>> c;
      W(pq1.size() > 1) {
        pair<int, int> p = pq1.top(); pq1.pop();
        c.pb(p);
      }

      if(c.size() > 0) {
        pair<int, int> p = pq1.top();
        for(pair<int, int>& p1 : c) {
          if(p1.first < a[b[0]].l) continue;
          int r1 = find(nums, p.second);
          int r2 = find(nums, p1.second);
          merge(nums, r1, r2);
        }
      }
      if(pq1.size() > 0) {
        pair<int, int> p = pq1.top();
        for(int j = 0; j < b.size(); j++) {
          if(p.first >= a[b[j]].l) {
            int r1 = find(nums, a[b[0]].i);
            int r2 = find(nums, a[b[j]].i);
            merge(nums, r1, r2);
          } else {
            break;
          }
        } 
        
        if(p.first >= a[b[0]].l) {
            int r1 = find(nums, a[b[0]].i);
            int r2 = find(nums, p.second);
            merge(nums, r1, r2);
        }
      }

      for(int& idx : b) {
        pq2.push({a[idx].r, a[idx].i});
      }
    }
    i = j - 1;
  }

  set<int> se;
  for(int i = 0; i < n; i++) {
    int r = find(nums, i);
    se.insert(r);
  }
  printf("%d\n", se.size());
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
