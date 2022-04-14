using namespace std;
using ll = long long;
#define pb push_back
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define RFOR(i, a, b) for (int i = a; i >= b; i--)

int base = 26;
int mod = 1000000007;
ll Pow[600 + 5];
int Forward[5010];
int Backward[5010];


class Solution {
public:
    vector<vector<int>> palindromePairs(vector<string>& a) {
        ve<ve<int>> res;
        int mx = 0;
        FOR(i, 0, a.size()) {
            mx = max(mx, (int)(a[i].size()));
            ll h = 0;
            FOR(j, 0, a[i].size()) {
                h = h * base + a[i][j];
                h %= mod;
            }
            Forward[i] = h;
            
            h = 0;
            RFOR(j, a[i].size() - 1, 0) {
                h = h * base + a[i][j];
                h %= mod;
            }
            Backward[i] = h;
        }
        
        Pow[0] = 1;
        FOR(i, 1, mx + 1) {
            Pow[i] = Pow[i - 1] * base;
            Pow[i] %= mod;
        }
                
        
        FOR(i, 0, a.size()) {
            int n = a[i].size();
            FOR(j, 0, a.size()) {
                if(i == j) continue;
                int m = a[j].size();
                ll h1 = Forward[i] * Pow[m] + Forward[j];
                h1 %= mod;
                ll h2 = Backward[j] * Pow[n] + Backward[i];
                h2 %= mod;
                if(h1 == h2) {
                    res.pb({i, j});
                }
            }
        }
        
        return res;
    }
};
