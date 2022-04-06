#define pb push_back
#define f first
#define se second
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define W while
#define RFOR(i, a, b) for (int i = a; i >= b; i--)
#define um unordered_map
#define us unordered_set
#define be begin
#define en end


class Solution {
public:
    int kIncreasing(vector<int>& a, int k) {
        int res = 0;
        FOR(i, 0, k) {
            int j = i;
            ve<int> b;
            W(j < a.size()) {
                b.pb(a[j]);
                j += k;
            }
            res += LIS(b);
        }
        return res;
    }
    
    int LIS(ve<int>& a) {
        int n = a.size();
        ve<int> dp(n + 1, 1000000);
        int res = 0;
        FOR(i, 0, n) {
            int l = 1, r = dp.size() - 1;
            int pos = -1;
            W(l <= r) {
                int mid = l + (r - l) / 2;
                if(a[i] < dp[mid]) {
                    pos = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            dp[pos] = a[i];
            res = max(res, pos);
        }
        
        return n - res;
    }
};
