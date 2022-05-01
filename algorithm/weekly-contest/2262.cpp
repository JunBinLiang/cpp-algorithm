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
int cnt[26];
ll most(string& s, int k) {
    ll res = 0;
    for(int i = 0; i < 26; i++) cnt[i] = 0;
    int size = 0;
    for(int i = 0, j = 0; i < s.size(); i++) {
        cnt[s[i] - 'a']++;
        if(cnt[s[i] - 'a'] == 1) size++;
        W(size > k) {
            cnt[s[j] - 'a']--;
            if(cnt[s[j] - 'a'] == 0) size--;
            j++;
        }
        res += (i - j) + 1;
    }
    return res;
}

ll cal(string& s, int k) {
    return most(s, k) - most(s, k - 1);
}

class Solution {
public:
    long long appealSum(string s) {
        ll res = 0;
        for(int i = 1; i <= 26; i++) {
            ll x = cal(s, i);
            res += (x * i);
        }
        return res;
    }
};
