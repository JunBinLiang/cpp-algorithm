class Solution {
public:
    vector<int> canSeePersonsCount(vector<int>& a) {
        int n = a.size();
        vector<int> res(n);
        vector<int> sta;
        for(int i = n - 1; i >= 0; i--) {
            int cnt = 0;
            while(sta.size() > 0 && a[i] >= a[sta.back()]) {
                cnt++;
                sta.pop_back();
            }
            
            if(sta.size() > 0) cnt++;
            res[i] = cnt;
            
            sta.push_back(i);
        }
        return res;
    }
};
