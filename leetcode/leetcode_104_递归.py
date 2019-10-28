# python2 递归解题思路 -- 深度优先搜索
class treeNode(object):
        def __init__(self, x):
                self.val = x;
                self.left = None
                self.right = None


class Solution:
        def maxDepth(self, root):
                if root is None:
                        return 0
                else:
                        left_hight = self.maxDepth(root.left)
                        right_hight = self.maxDepth(root.right)
                        return max(left_hight, right_hight) + 1
