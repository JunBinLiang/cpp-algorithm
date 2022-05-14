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

class Solution {
public:
    int largestVariance(string s) {
        ve<bool> seen(26);
        for(int i = 0; i < s.size(); i++) {
            seen[s[i] - 'a'] = true;
            s[i] -= 'a';
        }
        
        int res = 0;
        for(int i = 0; i < 26; i++) {
            if(!seen[i]) continue;
            for(int j = 0; j < 26; j++) {
                if(j == i || !seen[j]) continue;
                res = max(res, cal(s, i, j));
            }
        }
        return res;
    }
    
    int cal(string& a, int c1, int c2) {
        int total = 0;
        int res = 0;
        int sum = 0;
        int mn = 1000000, last = 1000000;
        for(int i = 0; i < a.size(); i++) {
            if(a[i] !=c1 && a[i] != c2) continue;
            if(a[i] == c1) sum--;
            else if(a[i] == c2) {
                sum++;
                total++;
            }

            if(sum != total) res = max(res, sum);
            res = max(res, sum - mn);
            mn = min(mn, last);
            last = sum;
        }
        //ensure at least one c1
        if(res == total) res--;
        return res;
    }
};
