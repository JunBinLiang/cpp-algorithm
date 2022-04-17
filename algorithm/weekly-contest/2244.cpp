class Solution {
public:
    int minimumRounds(vector<int>& a) {
        int res = 0;
        sort(a.begin(), a.end());
        for(int i = 0; i < a.size(); i++) {
            int cnt = 0;
            int j = i;
            while(j < a.size() && a[j] == a[i]) {
                j++;
                cnt++;
            }
            
            if(cnt == 1) {
                return -1;
            }
            
            if(cnt % 3 == 0) {
                res += cnt / 3;
            } else {
                int mod = cnt % 3;
                int have = cnt / 3;
                if(mod == 2) {
                    res += have;
                    res += 1;
                } else {
                    res += (have - 1);
                    res += 2;
                }
                
            }
            i = j - 1;
        }
        
        return res;
    }
};
