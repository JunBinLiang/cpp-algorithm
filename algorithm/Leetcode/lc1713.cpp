#define pb push_back
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define W while
#define um unordered_map

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
    int minOperations(vector<int>& a, vector<int>& b) {
        int res = 0;
        um<int, int> f;
        FOR(i, 0, a.size()) {
            f[a[i]] = i;
        }
        
        for(int i = 0; i < b.size(); i++) {
            if(f.find(b[i]) != f.end()) {
                b[i] = f[b[i]];
            } else {
                b[i] = -1;
            }
        }
        
        ve<int> dp(a.size() + 1, 1000000);
        for(int i = 0; i < b.size(); i++) {
            if(b[i] == -1) continue;
            int l = 1, r = dp.size() - 1;
            int pos = -1;
            W(l <= r) {
                int mid = l + (r - l) / 2;
                if(b[i] <= dp[mid]) {
                    pos = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            res = max(res, pos);
            dp[pos] = b[i];
        }
        return a.size() - res;
    }
};
