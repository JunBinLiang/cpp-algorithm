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
    int maximumProduct(vector<int>& a, int k) {
        priority_queue<int> q;
        ll res = 1;
        for(int i : a) {
            q.push(-i);
        }
        W(k--) {
            int top = q.top(); q.pop();
            top--;
            q.push(top);
        }
        
        
        W(q.size()) {
            int top = q.top(); q.pop();
            res *= (-top);
            res %= 1000000007;
        }
        
        return (int)(res);
    }
};
