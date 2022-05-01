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
    int minimumCardPickup(vector<int>& a) {
        um<int, int> f;
        int res = 1000000000;
        FOR(i, 0, a.size()) {
            if(f.find(a[i]) != f.end()) {
                res = min(res, i - f[a[i]] + 1); 
            } 
            f[a[i]] = i;
        }
        return res > a.size() ? -1 : res;
    }
};
