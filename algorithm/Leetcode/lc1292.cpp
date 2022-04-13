int dp[500][500];
class Solution {
public:
    int maxSideLength(vector<vector<int>>& a, int bound) {
        int n = a.size(), m = a[0].size();
        int l = 1, r = n;
        int res = 0;
        
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                dp[i][j] = a[i][j];
                if(i - 1 >= 0) dp[i][j] += dp[i - 1][j];
                if(j - 1 >= 0) dp[i][j] += dp[i][j - 1];
                if(i - 1 >= 0 && j - 1 >= 0) dp[i][j] -= dp[i - 1][j - 1];
            }
        }
        
        while(l <= r) {
            int mid = l + (r - l) / 2;
            if(check(a, mid, bound)) {
                res = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return res;
    }
    
    bool check(vector<vector<int>>& a, int mid, int bound) {
        int n = a.size(), m = a[0].size();
        for(int i = mid - 1; i < n; i++) {
            for(int j = mid - 1; j < m; j++) {
                int sum = dp[i][j];
                if(i - mid >= 0) sum -= dp[i - mid][j];
                if(j - mid >= 0) sum -= dp[i][j - mid];
                if(i - mid >= 0 && j - mid >= 0) sum += dp[i - mid][j - mid];
                if(sum <= bound) {
                    return true;
                }
            }
        }
        return false;
    }
};
