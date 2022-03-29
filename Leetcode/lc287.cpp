#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define W while

class Solution {
public:
    int findDuplicate(vector<int>& a) {
        for(int &i : a) {
            i--;
        }
        FOR(i, 0, a.size()) {
            if(a[i] != i) {
                W(a[a[i]] != a[i]) {
                    int j = a[i];
                    swap(a[j], a[i]);
                }       
            }
        }
        FOR(i, 0, a.size()) {
            if(i != a[i]) {
                return a[i] + 1;
            }
        }
        return - 1;
    }
};
