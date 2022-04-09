#define pb push_back
#define ve vector
#define FOR(i, a, b) for (int i = a; i < b; ++i)
#define RFOR(i, a, b) for (int i = a; i >= b; i--)

int nums[2000];
int find(int x){
  if(nums[x] == x) return x;
  int root = find(nums[x]);
  nums[x] = root;
  return root;
}


class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges) {
        FOR(i, 0, 1001) {
            nums[i] = i;
        }
        for(ve<int>& edge : edges) {
            int r1 = find(edge[0]);
            int r2 = find(edge[1]);
            if(r1 == r2) {
                return edge;
            } else {
                nums[r1] = r2;
            }
        }
        return {};
    }
};
