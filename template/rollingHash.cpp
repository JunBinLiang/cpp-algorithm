using ll = long long;
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define W while


int base = 26;
int mod = 1000000007;
ll Pow[100000 + 5];
ll Hash[100000 + 5];

class Solution {
public:
    long long sumScores(string s) {
        ll res = 0;
        int n = s.size();
        
        Pow[0] = 1;
        FOR(i, 1, n) {
            Pow[i] = Pow[i - 1] * base;
            Pow[i] %= mod;
        }
        
        ll h = 0;
        FOR(i, 0, n) {
            h = h * base + s[i];
            h %= mod;
            Hash[i] = h;
        }
        
        
        FOR(i, 0, n) {
            int l = 0, r = i;
            int pos = -1;
            W(l <= r) {
                int mid = l + (r - l) / 2;
                ll a = get(0, mid);
                ll b = get(n - 1 - i, n - 1 - i + mid);
                if(a == b) {
                    pos = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            res += (pos + 1);
        }
        return res;
    }
    
    ll get(int left, int right) {
        if(left == 0) {
            return Hash[right];
        }
        ll res = (Hash[right] - (Hash[left - 1] * Pow[right - left + 1] % mod) + mod) % mod;
        if(res < 0)res += mod;
        return res % mod;
    }
};
