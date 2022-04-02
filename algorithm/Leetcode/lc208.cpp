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
  return false;
}

int MOD = 998244353;
int mod = 1000000007;

struct Node {
    int Next[26];
    void init() {
        memset(Next, -1, sizeof(Next));
    }
}tree[1000000];

int treeI = 0;
void add(string& s) {
    int root = 0;
    FOR(i, 0, s.size()) {
        int d = s[i] - 'a';
        if(tree[root].Next[d] == -1) {
            tree[root].Next[d] = treeI;
            tree[treeI] = {};
            tree[treeI].init();
            treeI++;
        } 
        root = tree[root].Next[d];
    }
}

bool find(string& s) {
    int root = 0;
    FOR(i, 0, s.size()) {
        int d = s[i] - 'a';
        if(tree[root].Next[d] == -1) {
            return false;
        }
        root = tree[root].Next[d];
    }
    return true;
}

class Trie {
public:
    set<string> se;
    Trie() {
        //clean the old tree
        FOR(i, 0, treeI + 1) {
            tree[i] = {};
        }
        treeI = 1;
        tree[0] = {};
        tree[0].init();
    }
    
    void insert(string s) {
        se.insert(s);
        add(s);
    }
    
    bool search(string word) {
        return se.find(word) != se.end();
    }
    
    bool startsWith(string prefix) {
        return find(prefix);
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
