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

bool seen[101][101][110];
bool dp[101][101][110];
int n, m;
class Solution {
public:
    bool hasValidPath(vector<vector<char>>& a) {
        n = a.size();
        m = a[0].size();
        for(int i = 0; i < n; i ++) {
            for(int j = 0; j < m; j++) {
                for(int k = 0; k < 110; k++) {
                    dp[i][j][k] = false;
                    seen[i][j][k] = false;
                }
            }
        }
        return dfs(a, 0, 0, 0);
    }
    
    bool dfs(vector<vector<char>>& a, int r, int c, int open) {
        if(open > 105) {
            return false;
        }
        
        if(r == n - 1 && c == m - 1) {
            if(a[r][c] == '(') {
                open++;
            } else {
                open--;
            }
            
            if(open == 0) {
                return true;
            }
            return false;
        }
        
        if(seen[r][c][open]) {
            return dp[r][c][open];
        }
        
        
        bool res = false;
        if(a[r][c] == '(') {
            if(r + 1 < n) {
                res |= dfs(a, r + 1, c, open + 1);
            } 
            if(c + 1 < m) {
                res |= dfs(a, r, c + 1, open + 1);
            }
            
        } else {
            if(open > 0) {
                if(r + 1 < n) {
                    res |= dfs(a, r + 1, c, open - 1);
                } 
                if(c + 1 < m) {
                    res |= dfs(a, r, c + 1, open - 1);
                }
            }
        }
        seen[r][c][open] = true;
        return dp[r][c][open] = res;
    }
};
