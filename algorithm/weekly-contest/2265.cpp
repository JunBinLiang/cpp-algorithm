/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

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
int res = 0;
class Solution {
public:
    int averageOfSubtree(TreeNode* root) {
        res = 0;
        dfs(root);
        return res;
    }
    
    ve<int> dfs(TreeNode* root) {
        if(root == NULL) {
            return {0, 0};
        }
        ve<int> l = dfs(root -> left);
        ve<int> r = dfs(root -> right);
        int sum = l[0] + r[0] + root -> val;
        int size = l[1] + r[1] + 1;
        if(sum / size == root -> val) {
            res++;
        }
        return {sum, size};
    }
};
