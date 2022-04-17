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
int res = 1;
class Solution {
public:
    int longestPath(vector<int>& a, string s) {
        res = 1;
        int n = a.size();
        ve<ve<int>> g(n);
        for(int i = 0; i < a.size(); i++) {
            if(a[i] != -1) {
                g[a[i]].pb(i), g[i].pb(a[i]);
            }
        } 
        dfs(s, g, -1, 0);
        return res;
    }
    
    int dfs(string& s, ve<ve<int>>& g, int p, int root ) {
        int mx = 0;
        for(int nxt : g[root]) {
            if(p == nxt) continue;
            int cnt = dfs(s, g, root, nxt);
            if(s[root] == s[nxt]) continue;
            res = max(res, 1 + cnt + mx);
            mx = max(mx, cnt);
        }
        return mx + 1;
    }
};
