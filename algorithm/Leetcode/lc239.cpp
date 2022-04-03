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

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& a, int k) {
        ve<int> res;
        list<ve<int>> mono;
        FOR(i, 0, a.size()) {
            W(mono.size() > 0 && a[i] >= mono.back()[0]) mono.pop_back();
            mono.pb({a[i], i});
            if(i + 1 < k) continue;
            W(mono.size() > 0 && i - mono.front()[1] >= k) mono.pop_front();
            res.pb(mono.front()[0]);
        }
        return res;
    }
};
