#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<unordered_map>
#include<set>
#include<unordered_set>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;
using ll = long long;

#define pb push_back
#define f first
#define s second
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define RFOR(i, a, b) for (int i = a; i >= b; i--)
#define W while
#define um unordered_map
#define us unordered_set
#define be begin
#define en end

//Some predefined templates
template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
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
ostream& operator <<(ostream& out, const map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

template <typename U, typename T, class Cmp>
ostream& operator <<(ostream& out, const unordered_map<U, T, Cmp>& a) {
  out << "{"; bool first = true;
  for (auto& p : a) { out << (first ? "" : ", "); out << p.first << ":" << p.second; first = 0;} out << "}";
  return out;
}

unsigned long long seed = 131;
unsigned long long rands(){return seed = (seed << 15) + (seed << 8) + (seed >> 3);}

/*const int M = 60;
typedef array<int, M> num;
num operator ^(const num &a, const num &b){
    num c;
    for(int i = 0; i < M; i++) {
        c[i] = a[i] + b[i];
        if (c[i] >= 3) c[i] -= 3;
    }
    return c;
}*/

ll gcd(ll x, ll y) {
    return (y == 0 ? x : gcd(y, x % y));
}
ll lcm(ll x, ll y) {
    return x * y / gcd(x, y);
}

int to_int(string& s) {
  int res = 0;
  for(char c : s) {
    res = res * 10 + (c - '0');
  }
  return res;
}

string substring(string& s, int l, int r) {
  string res = "";
  for(int i = l; i <= r; i++) res += s[i];
  return res;
}

bool COMP(ve<int>& a, ve<int>& b) {
  return false;
}

struct Tuple {
  int a, b, c;
};

int mod = 1000000007;
ifstream fcin("test/input.txt");
ofstream fcout("test/output.txt");
int main()
{

  return 0;
}

