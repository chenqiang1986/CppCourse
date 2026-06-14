# Binary Tree Traversal

Given a binary tree, output its node ids using pre-order, in-order and post-order traversal.

## Input
First line, N an integer representing number of nodes.

Next N lines, each line contains 3 integers, say A  B  C, it means
B is the left child of A, and C is the right child of A.

If B==-1, it means A has no left child.
If C==-1, it means A has no right child.

## Output
Three lines, the first line, contains N numbers, which is the pre-order traversal of the tree.
The second line contains the in-order traversal of the tree.
The third line contains the post-order traversal of the tree.

## Example

### Input
4
1 2 3
2 0 4
3 0 0
4 0 0

### Output
1 2 4 3
2 4 1 3
4 2 3 1
