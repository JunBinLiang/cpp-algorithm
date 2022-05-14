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

bool COMP(ve<int>& p1, ve<int>& p2) {
  return p1[0] < p2[0];
}

int get(ve<int>&a, int l, int r){
    if(l == 0) return a[r];
    return a[r] - a[l - 1];
}

class Solution {
public:
    int maximumWhiteTiles(vector<vector<int>>& a, int len) {
        int res = 0;
        sort(a.begin(), a.end(), COMP);
        ve<int> pre;
        int sum = 0;
        for(int i = 0; i < a.size(); i++) {
            sum += (a[i][1] - a[i][0] + 1);
            pre.pb(sum);
        }

        
        for(int i = 0; i < a.size(); i++) {
            int l = i, r = a.size() - 1;
            int pos = -1;
            int to = a[i][0] + len - 1;
            W(l <= r) {
                int mid = l + (r - l) / 2;
                if(to >= a[mid][0]) {
                    pos = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
                
            }
            
            int total = get(pre, i, pos);
            //cout << total << endl;
            if(to <= a[pos][1])total -= (a[pos][1] - to);
            //cout <<to << " " << pos << " " << total <<endl;
            res = max(res, total);
        }
        
        return res;
    }
};
