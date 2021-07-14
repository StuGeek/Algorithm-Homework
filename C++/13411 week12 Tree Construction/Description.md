# week12 Tree Construction

During the programming classes Vasya was assigned a difficult problem. However, he doesn't know how to code and was unable to find the solution in the Internet, so he asks you to help.

You are given a sequence a, consisting of n distinct integers, that is used to construct the binary search tree. Below is the formal description of the construction process.

First element a1 becomes the root of the tree.
Elements a2, a3, ..., an are added one by one. To add element ai one needs to traverse the tree starting from the root and using the following rules:
The pointer to the current node is set to the root.
If ai is greater than the value in the current node, then its right child becomes the current node. Otherwise, the left child of the current node becomes the new current node.
If at some point there is no required child, the new node is created, it is assigned value ai and becomes the corresponding child of the current node.

### Input
The first line of the input contains a single integer n (2 ≤ n ≤ 100 000) — the length of the sequence a.

The second line contains n distinct integers ai (1 ≤ ai ≤ 10^9) — the sequence a itself.

### Output
Output n - 1 integers. For all i > 1 print the value written in the node that is the parent of the node with value ai in it.

### Examples
**input**
```
3

1 2 3
```
**output**
```
1 2
```
**input**
```
5

4 2 3 1 6
```
**output**
```
4 2 2 4
```
### Note
Picture below represents the tree obtained in the first sample.

![](http://codeforces.com/predownloaded/f2/f3/f2f3bf8a19408d1f82699a41b787e56a6452dd81.png)

Picture below represents the tree obtained in the second sample.

![](http://codeforces.com/predownloaded/f5/bd/f5bdbb65dc9bd752e030a47d4808c15b1b19aae1.png)
