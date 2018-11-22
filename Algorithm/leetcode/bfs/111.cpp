/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

class Solution {
public:
    int minDepth(TreeNode* root) {
        queue<TreeNode*> q;
        int result = 0;
        
        // return 0 for NULL root
        if (root == NULL) return 0;
        
        root -> val = 1;  // fix the val into the depth of the node
        q.push(root);  // push the root
        while (!q.empty()) {
            root = q.front();
            q.pop();
            
            if (root -> left == NULL && root -> right == NULL) {
                // find the minest depth
                return root -> val;
            }
            if (root -> left != NULL) {
                root -> left -> val = root -> val + 1;
                q.push(root -> left);
            }
            if (root -> right != NULL) {
                root -> right -> val = root -> val + 1;
                q.push(root -> right);
            }
        }
    }
};
