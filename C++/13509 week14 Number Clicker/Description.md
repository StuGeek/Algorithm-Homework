# week14 Number Clicker

## 题目描述

Allen is playing Number Clicker on his phone.
He starts with an integer $u$ on the screen. Every second, he can press one of $3$ buttons.

1: Turn $u \rightarrow u+1$ ($mod$ $p$).

2: Turn $u \rightarrow u+p-1$ ($mod$ $p$).

3: Turn $u \rightarrow u^{p-2}$ ($mod$ $p$).

Allen wants to press at most $200$ buttons and end up with $v$ on the screen. Help him!

## Input

The first line of the input contains $3$ positive integers: $u,v,p (0 \leq u, v \leq p-1, 3 \leq p \leq 10^6)$. $p$ is guaranteed to be prime.

## Output

Print a single integer $\ell$, the number of button presses.

We can show that the answer always exists.

## Examples

**Input**
```
1 3 5
```
**Output**
```
2
```
**Input**
```
3 2 5
```
**Output**
```
1
```

## Note

In the first example the integer on the screen changes as $1\rightarrow 2 \rightarrow 3$

In the second example the integer on the screen changes as $3 \rightarrow 2$.
