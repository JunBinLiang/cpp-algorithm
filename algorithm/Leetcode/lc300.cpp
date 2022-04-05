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
    int lengthOfLIS(vector<int>& a) {
        int n = a.size();
        ve<int> dp(n + 1, 100000);
        int res = 0;
        FOR(i, 0, n) {
            int l = 1, r = n;
            int pos = -1;
            W(l <= r) {
                int mid = l + (r - l) / 2;
                if(a[i] <= dp[mid]) {
                    pos = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            res = max(res, pos);
            dp[pos] = a[i];
        }
        return res;
    }
};
