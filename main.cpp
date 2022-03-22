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

//Some predefined templates
template <typename T>
ostream& operator <<(ostream& out, const vector<T>& a) {
  out << "["; bool first = true;
  for (auto v : a) { out << (first ? "" : ", "); out << v; first = 0;} 
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

int mod = 1000000007;

int main()
{

  return 0;
}

