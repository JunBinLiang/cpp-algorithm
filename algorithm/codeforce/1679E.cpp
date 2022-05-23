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
    bool operator() (ve<ll>& a, ve<ll>& b)
    {
        return a[0] > b[0];
    }
    //a[0] > b[0] : min
};*/



int mod = 998244353;
ll Pow[18][1100];
ll dp[18][(1 << 18)];
void solve() {
  int n;
  cin >> n;
  string s;
  cin >> s;
  int tot = 0;
  for(char& c : s) {
      if(c == '?')tot++;
  }

  for(int i = 0; i < 18; i++) {
    Pow[i][0] = 1;
    for(int j = 1; j < 1010; j++) {
      Pow[i][j] = Pow[i][j - 1] * i;
      Pow[i][j] %= mod;
    }
  }

  memset(dp, 0, sizeof(dp));

  for(int i = 0; i < n; i++) {
    int l = i, r = i;
    int bit = 0;
    int cnt = 0;
    int all = tot;
    W(l >= 0 && r < n) {
      if(s[l] == '?' && s[r] == '?') {
        cnt++;
        all -= 2;
        if(l == r) all++;
      }
      else if(s[l] == '?') {
        bit = bit | (1 << (s[r] - 'a'));
        all--;
      }
      else if(s[r] == '?'){
        bit = bit | (1 << (s[l] - 'a'));
        all--;
      }
      else {
        if(s[l] != s[r]) break;
      }
      
      int bitcnt = 0;
      for(int j = 0; j < 18; j++) {
          if(bit & (1 << j))bitcnt++;
      }
     // cout <<"a " << l <<" " << r << "   " << bitcnt << " " << cnt << " " << bit << "  " << all <<endl;
      for(int j = bitcnt; j < 18; j++) {
        dp[j][bit] += Pow[j][cnt + all];
        dp[j][bit] %= mod;
      }
      l--; r++;
    }
  }

  for(int i = 0; i < n; i++) {
    int l = i, r = i + 1;
    int bit = 0;
    int cnt = 0;
    int all = tot;
    W(l >= 0 && r < n) {
      if(s[l] == '?' && s[r] == '?') {
        cnt++;
        all -= 2;
        if(l == r) all++;
      }
      else if(s[l] == '?') {
        bit = bit | (1 << (s[r] - 'a'));
        all--;
      }
      else if(s[r] == '?'){
        bit = bit | (1 << (s[l] - 'a'));
        all--;
      }
      else {
        if(s[l] != s[r]) break;
      }
      
      int bitcnt = 0;
      for(int j = 0; j < 18; j++) {
          if(bit & (1 << j))bitcnt++;
      }
     // cout <<"b " << l <<" " << r << "   " << bitcnt << " " << cnt << " " << bit << "  " << all <<endl;
      for(int j = bitcnt; j < 18; j++) {
        dp[j][bit] += Pow[j][cnt + all];
        dp[j][bit] %= mod;
      }
      l--; r++;
    }
  }
  


  //https://codeforces.com/blog/entry/45223
  for(int i = 0; i < 18; i++) {
    ll sum = 0;
    for(int j = 0; j < 18; j++) {
        for(int state = 0; state < (1 << 18); state++ ) {
            if(state & (1 << j)) {
                dp[i][state] += dp[i][state ^ (1<<j)];
                dp[i][state] %= mod;
            }
        
        }
    }
    
      
    
  }
  //cout << dp[2][0] << endl;
  //cout << dp[2][1] << endl;
  //cout << dp[2][2] << endl;
  //cout << dp[2][3] << endl;

  int m;
  cin >> m;
  for(int i = 0; i < m; i++) {
    string t;
    cin >> t;
    int bit = 0, len = 0;
    for(char& c : t) {
      bit |= (1 << (c - 'a'));
    }

    for(int j = 0; j < 18; j++) {
      if(bit & (1 << j)) {
        len++;
      }
    }
    printf("%d \n", dp[len][bit]);
    
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
