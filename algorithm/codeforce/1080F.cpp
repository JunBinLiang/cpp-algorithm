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
const int MAX = 2000000 + 10;
int ids[300000 + 5];
int vals[100000 + 5];
struct Node {
  int l, r;
  int lid, rid;
  int mx;
} tree[MAX * 4];

int idx = 0;

void build(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    return;
  }
  int mid = l + (r - l) / 2;
  int idx1 = idx;
  int idx2 = idx + 1;
  idx += 2;
  tree[id].lid = idx1;
  tree[id].rid = idx2;
  tree[idx1] = {l, mid, -1, -1, -1};
  tree[idx2] = {mid + 1, r,-1, -1, -1};
  build(idx1);
  build(idx2);
}

void update(int preId, int curId, int index, int val) {
  int l = tree[curId].l, r = tree[curId].r;
  if(l == r) {
    vals[l] = max(vals[l], val);
    tree[curId].mx = vals[l];
    return;
  }
  int mid = l + (r - l) / 2;
  if (index <= mid) {//update left
    tree[curId].rid = tree[preId].rid;
    tree[idx] = {tree[tree[preId].lid].l, tree[tree[preId].lid].r, -1, -1, -1};
    tree[curId].lid = idx;
    idx++;
    update(tree[preId].lid, tree[curId].lid, index, val);
  } else {//update right
    tree[curId].lid = tree[preId].lid;    
    tree[idx] = {tree[tree[preId].rid].l, tree[tree[preId].rid].r, -1, -1, -1};
    tree[curId].rid = idx;
    idx++;
    update(tree[preId].rid, tree[curId].rid, index, val);
  }
  tree[curId].mx = min(tree[tree[curId].lid].mx, tree[tree[curId].rid].mx);
}

int query(int id, int s, int e) {
  int l = tree[id].l, r = tree[id].r;
  if(l == s && r == e){
    return tree[id].mx;
  }
  int mid = l + (r - l) / 2;
  int left = tree[id].lid, right = tree[id].rid;
  if(e <= mid){
      return query(left, s, e);
  } else if(s >= mid + 1) {
      return query(right, s, e);
  } else {
    return min(query(left, s, mid), query(right, mid + 1, e));
  }
}

void print(int id) {
  int l = tree[id].l, r = tree[id].r;
  if(l == r) {
    cout << l << " " << r << " " << tree[id].mx << endl;
    return;
  }
  cout << l << " " << r << " " << tree[id].mx << endl;
  print(tree[id].lid);
  print(tree[id].rid);
}


struct Tuple {
  int l, r, idx;
};

bool COMP(Tuple& t1, Tuple& t2) {
  if(t1.r == t2.r) {
    return t1.l < t2.l;
  }
  return t1.r < t2.r;
}

bool COMP2(Tuple& t1, Tuple& t2) {
  return t1.l < t2.l;
}

void NO() {
  printf("no \n");
  cout.flush();
}

void YES() {
  printf("yes \n");
  cout.flush();
}




void solve() {
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  memset(vals, -1, sizeof(vals));
  ve<Tuple> a;
  for(int i = 0; i < k; i++) {
    int l, r, p;
    scanf("%d%d%d", &l, &r, &p);
    p--;
    a.pb({l, r, p});
  }
  sort(a.begin(), a.end(), COMP);

  tree[0] = {0, n - 1, -1, -1, -1};
  ids[0] = idx;
  idx++;
  build(0);

  for(int i = 0; i < a.size(); i++) {
    ids[i + 1] = idx;
    tree[idx] = {0, n - 1, -1, -1, -1};
    idx++;
    update(ids[i], ids[i + 1], a[i].idx, a[i].l);
  }

  
  //cout << endl;
  /*print(ids[0]); 
  cout << endl;
  print(ids[1]);
  cout << endl;
  print(ids[2]);
  cout << endl;
  print(ids[3]);
  cout << endl;*/

  for(int i = 0; i < m; i++) {
    int left, right, x, y;
    scanf("%d%d%d%d", &left, &right, &x, &y);
    left--; right--;
    //each sets[a] - sets[b] 
    // x <= l <= r <= y
    int l = 0, r = a.size() - 1;
    int pos = -1;
    W(l <= r) {
      int mid = l + (r - l) / 2;
      if(a[mid].r <= y) {
        pos = mid;
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    
    if(pos == -1) {
      NO();
      continue;
    }

    int mx = query(ids[pos + 1], left, right);
    if(mx >= x) {
      YES();
    } else {
      NO();
    }
  }
}

//y : 999999806
//pos : 299999
//260313323 274269275 67647      12376
//26059 616369294     67647      74664

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


/*
5 1 3
1 3 1
2 3 1
2 4 2
1 2 2 3
*/
