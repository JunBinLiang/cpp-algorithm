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

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */


int sums[100000 + 5];
ve<pair<int, int>> all[100000 + 5];
um<TreeNode*, int> f;
int cnts[100000 + 5];
int mergeCnt[100000 + 5];

int res = -1000000000;
int level = 0, cnt = 0;

int Abs(int a) {
    if(a < 0) return -a;
    return a;
}

int dfs(TreeNode* root, int dep) {
    
    if(root -> left && root -> right) {
        int index1 = dfs(root -> left, dep + 1);
        int index2 = dfs(root -> right, dep + 1);
        ve<pair<int, int>>& a = all[index1];
        ve<pair<int, int>>& b = all[index2];
        //merge
        int k = Abs(a.size() - b.size());
        if(a.size() < b.size()) {
            mergeCnt[index2] += mergeCnt[index1];
            for(int i = 0; i < a.size(); i++) {
                b[k + i].first += a[i].first;
                if(k + i - 1 >= 0) {
                    int dif = b[k + i - 1].first - b[k + i].first;
                    b[k + i].second = max(dif + sums[dep + (b.size() - (k + i))], b[k + i - 1].second);
                }
                if(k + i - 1 < 0) {
                    if(mergeCnt[index2] != cnts[level - 1]) {
                        int dif = b[k + i].first;
                        b[k + i].second = -dif + sums[dep + (b.size() - (k + i))];
                    } else {
                        b[k + i].second = -1000000000;
                    }
                }
            }
            int dif = b[b.size() -1].first - root -> val;
            b.pb({root -> val, max(dif + sums[dep], b[b.size() - 1].second)});
            return index2;
        } else {
            mergeCnt[index1] += mergeCnt[index2];
            for(int i = 0; i < b.size(); i++) {
                a[k + i].first += b[i].first;
                if(k + i - 1 >= 0) {
                    int dif = a[k + i - 1].first - a[k + i ].first;
                    a[k + i].second = max(dif + sums[dep + (a.size() - (k + i))], a[k + i - 1].second);
                }
                if(k + i - 1 < 0) {
                    if(mergeCnt[index1] != cnts[level - 1]) {
                        int dif = a[k + i].first;
                        a[k + i].second = -dif + sums[dep + (a.size() - (k + i))];
                    } else {
                        a[k + i].second = -1000000000;
                    }
                }
            }
            
            int dif = a[a.size() -1].first - root-> val;
            a.pb({root -> val, max(dif + sums[dep], a[a.size() - 1].second)});
            return index1;
        }
        
    } else if(root -> left) {
        int index = dfs(root -> left, dep + 1);
        ve<pair<int, int>>& a = all[index];
        int dif = a[a.size() - 1].first - root -> val;
        int can = sums[dep] + dif;
        int maxCan = max(can, a[a.size() -1].second);
        res = max(res, maxCan);
        a.pb({root -> val, maxCan});
        return index;
    } else if(root -> right ){
        int index = dfs(root -> right, dep + 1);
        ve<pair<int, int>>& a = all[index];
        int dif = a[a.size() - 1].first - root -> val;
        int can = sums[dep] + dif;
        int maxCan = max(can, a[a.size() -1].second);
        res = max(res, maxCan);
        a.pb({root -> val, maxCan});
        return index;
    } else {
        int index = f[root];
        if(cnts[dep] > 1) {
            res = max(res, sums[dep] - root -> val);
        }
        if(dep == level - 1)mergeCnt[index] = 1;
        all[index].pb({root -> val, -1000000000});
        return index;
    }
}




class Solution {
public:
    int getMaxLayerSum(TreeNode* root) {
        res = no(root);
        dfs(root, 0);     
        return res;
    }
    
    int no(TreeNode* root) {
        int ans = -1000000000;
        level = 0, cnt = 0;
        queue<TreeNode*> q;
        q.push(root);
        W(q.size() > 0) {
            int size = q.size();
            int sum = 0;
            cnts[level] = size;
            FOR(i, 0, size) {
                TreeNode* top = q.front(); q.pop();
                sum += top -> val;
                if(top -> left) q.push(top -> left);
                if(top -> right) q.push(top -> right);
                f[top] = cnt;
                mergeCnt[cnt] = 0;
                if(all[cnt].size() > 0) cnt[all].clear();
                cnt++;
            }
            ans = max(ans, sum);
            sums[level] = sum;
            level++;
        }
        return ans;
    }
};
