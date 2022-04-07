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

bool is[200000 + 5];
class Solution {
public:
    int countDifferentSubsequenceGCDs(vector<int>& a) {
        memset(is, false, sizeof(is));
        int mx = 0;
        for(int &i : a) {
            is[i] = true;
            mx = max(mx, i);
        }
                
        int n = a.size();
        int res = 0;
        FOR(i, 1, mx + 1) {
            int g = -1;
            for(int j = i; j <= mx && g != i; j += i) {
                if(is[j]) {
                    if(g == -1) {
                        g = j;
                    } else {
                        g = __gcd(g, j);
                    }
                }
            }
            if(g == i) res++;
        }
        return res;
    }
};
