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
    int countDistinct(vector<int>& a, int k, int p) {
        int res = 0;
        unordered_set<string> set;
        for(int i = 0; i < a.size(); i++) {
            int cnt = 0;
            string s = "";
            for(int j = i; j < a.size(); j++) {
                if(a[j] % p == 0)cnt++;
                if(cnt > k) break;
                s += to_string(a[j]) + "|";
                set.insert(s);
                
            }
        }
    
        
        return set.size();
    }
};
