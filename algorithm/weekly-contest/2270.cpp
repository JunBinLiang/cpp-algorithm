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
    int waysToSplitArray(vector<int>& a) {
        int res = 0;
        ll sum = 0;
        for(int i : a) sum += i;
        ll cur = 0;
        for(int i = 0; i < a.size() - 1; i++) {
            cur += a[i];
            sum -= a[i];
            if(cur >= sum) res++;
        }
        return res;
    }
};
