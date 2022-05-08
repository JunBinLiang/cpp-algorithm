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
int mod = 1000000007;
ve<int> a = {0,0,3,3,3,3,3,4,3,4};
int dp[100000];
class Solution {
public:
    int countTexts(string s) {
        for(int i = 0; i < s.size(); i++) {
            dp[i] = -1;
        }
        return dfs(s, 0);
    }
    
    int dfs(string& s, int i) {
        if(i >= s.size()) {
            return 1;
        }
        
        if(dp[i] != -1) {
            return dp[i];
        }
        
        int t = a[s[i] - '0'];
        int res = 0;
        for(int j = 0; j < t; j++) {
            if(i + j < s.size() && s[i + j] == s[i]) {
                res += dfs(s, i + j + 1);
                res %= mod;
            } else {
                break;
            }
        }
        return dp[i] = res;
    }
};
