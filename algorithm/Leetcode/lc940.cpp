int dp[3000];
int last[26];
int mod = 1000000000 + 7;
class Solution {
public:
    int distinctSubseqII(string s) {
        dp[0] = 2;
        memset(last, -1, sizeof(last));
        last[s[0] - 'a'] = 0;
        for(int i = 1; i < s.size(); i++) {
            dp[i] = dp[i - 1] * 2;
            dp[i] %= mod;
            if(last[s[i] - 'a'] != -1) {
                int index = last[s[i] - 'a'];
                if(index == 0) {
                    dp[i]--;
                } else {
                    dp[i] -= dp[index - 1];
                }
                dp[i] += mod;
                dp[i] %= mod;
            }
            last[s[i] - 'a'] = i;
        }
        
        int res = dp[s.size() - 1];
        res -= 1;
        res += mod;
        res %= mod;
        return res;
    }
};
