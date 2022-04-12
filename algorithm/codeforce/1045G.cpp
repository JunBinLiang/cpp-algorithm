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

class Compare
{
public:
    bool operator() (ve<int>& a, ve<int>& b)
    {
        return a[0] > b[0];
    }
};



const int MAX = 520000;
struct Node {
  int l, r;
  int leftIdx = 0, rightIdx = 0;
  int sum;
} tree[MAX * 4];

int nodeIdx = 1;
void update(int id, int index, int val) { 
  int l = tree[id].l, r = tree[id].r;
  
  if(l == r) {
    tree[id].sum += val;
    return;
  }
  int mid = l + (r - l) / 2;
  if(index <= mid) {
    if(tree[id].leftIdx == 0) {
      tree[nodeIdx] = {l, mid, 0, 0, 0};
      tree[id].leftIdx = nodeIdx;
      nodeIdx++;
    }
    update(tree[id].leftIdx, index , val);
  } else {
    if(tree[id].rightIdx == 0) {
      tree[nodeIdx] = {mid + 1, r, 0, 0, 0};
      tree[id].rightIdx = nodeIdx;
      nodeIdx++;
    }
    update(tree[id].rightIdx, index , val);
  }

  tree[id].sum = 0;
  if(tree[id].leftIdx > 0) {
    tree[id].sum += tree[tree[id].leftIdx].sum;
  }
  if(tree[id].rightIdx > 0) {
    tree[id].sum += tree[tree[id].rightIdx].sum;
  }
}

int query(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  if(id == 0) {
    return 0;
  }
  if(l == s && r == e){
    return tree[id].sum;
  }
  int mid = l + (r - l) / 2;
  if(e <= mid){
      return query(tree[id].leftIdx, s, e);
  } else if(s >= mid + 1) {
      return query(tree[id].rightIdx, s, e);
  } else {
    return query(tree[id].leftIdx, s, mid) +  query(tree[id].rightIdx, mid + 1, e);
  }
}



int n, k;
um<int, int> f;
um<int, int > cnt;
um<int, int> kmap;
int id = 0;
void solve() {
  scanf("%d%d", &n, &k);
  ll res = 0;
  ve<ve<int>> a;
  ve<int> b;
  FOR(i, 0, n) {
    int x, r, q;
    scanf("%d%d%d", &x, &r, &q);
    a.pb({x, r, q});
    b.pb(x); b.pb(x + r); b.pb(x - r);
  } 
  sort(b.begin(), b.end());
  for(int i = 0; i < (int)(b.size()); i++) {
    int j = i;
    W(j < (int)(b.size()) && b[j] == b[i]) {
      j++;
    }
    f[b[i]] = id++;
    i = j - 1;
  }
  
  //cout << f << endl;

  sort(a.begin(), a.end(), COMP);
  priority_queue<ve<int>, ve<ve<int>>, Compare> pq;

  for(int i = 0; i < (int)(a.size()); i++) {
    int x = a[i][0], r = a[i][1], q = a[i][2];
    //remove invalid
    W(pq.size() > 0) { // can not see
      ve<int> c = pq.top();
      if(c[0] < x) {
        int index = f[c[1]];
        update(kmap[c[2]], index, -1);
        cnt[c[2]]--;
        pq.pop();
      } else {
        break;
      }
    }
    

    int l = f[x - r];
    int index = f[x];
    for(int j = q - k; j <= q + k; j++) {
      if(cnt[j] == 0) continue;
      int root = kmap[j];
      int sum = query(root, l, index);
      res += sum;
    }
    //add
    cnt[q]++;
    pq.push({x + r, x, q});
    if(kmap.find(q) == kmap.end()) {
      kmap[q] = nodeIdx;
      tree[nodeIdx] = {0, id + 1, 0, 0, 0};
      nodeIdx++;
    } 
    update(kmap[q], index, 1);
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
