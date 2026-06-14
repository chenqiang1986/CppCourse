# Tree Traversal

Given tree, output its node ids using pre-order and post-order traversal.

## Input
First line, N an integer representing number of nodes.

Next N-1 lines, each line has two numbers that describe a parent-child relation. 
E.g. A B \
It means B is one child of A.

## Output
Two lines, the first line, contains N numbers, which is the pre-order traversal of the tree.
The second line contains the post-order traversal of the tree.

Note: for the children sharing the same parent, they need to be ordered by their ids. Smaller ID should go first.

## Example

### Input
4 \
1 2 \
1 3 \
2 4 \ 

### Output
1 2 4 3 \
4 2 3 1 
