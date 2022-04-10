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

int to_int(string &s)
{
  int res = 0;
  for (char c : s)
  {
    res = res * 10 + (c - '0');
  }
  return res;
}

class Solution {
public:
    int largestInteger(int num) {
        string s = to_string(num);
        ve<char> even, odd;
        FOR(i, 0, s.size()) {
            int d = s[i] - '0';
            if(d % 2 == 0) {
                even.pb(s[i]);
            } else {
                odd.pb(s[i]);
            }
        }
        
        sort(even.begin(), even.end());
        sort(odd.begin(), odd.end());
        
        string res = "";
        FOR(i, 0, s.size()) {
            int d = s[i] - '0';
            if(d % 2 == 0) {
                res += even[even.size() - 1];
                even.pop_back();
            } else {
                res += odd[odd.size() - 1];
                odd.pop_back();
            }
        }
        return to_int(res);
    }
};
