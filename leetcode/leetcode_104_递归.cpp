class Solution {
public:
    int maxDepth(TreeNode* root) {
        if(root == nullptr)
            return 0;
        TreeNode* ptr = root;
        TreeNode* left_ptr = ptr->left;
        TreeNode* right_ptr = ptr->right;
        int left_depth = maxDepth(left_ptr);
        int right_depth = maxDepth(right_ptr);
        if (left_depth > right_depth)
            return left_depth + 1;
        else
            return right_depth + 1;
    }
};
