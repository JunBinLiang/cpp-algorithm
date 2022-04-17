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

int add(string& s) {
    int res = 0;
    for(int i = 0; i < s.size(); i++) {
        res += s[i] - '0';
    }
    return res;
}

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


class Solution {
public:
    string digitSum(string s, int k) {
        W(s.size() > k) {
            int cnt = 0;
            int add = 0;
            ve<int> a;
            FOR(i, 0, s.size()) {
                cnt++;
                add += (s[i] - '0');
                if(cnt == k) {
                    a.pb(add);
                    cnt = 0;
                    add = 0;
                }
            }
            if(cnt != 0) a.pb(add);
    
            string ss = "";
            for(int i : a) {
                ss += to_string(i);
            }
            s = ss;
        }
        return s;
    }
};
