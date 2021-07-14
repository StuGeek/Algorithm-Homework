# week15  kmp

# Description
Write a function to check whether string s1 is a substring of string s2. The function returns the first index in s2 if there is a match. Otherwise, returns -1.

The function header is:
```C
int indexOf(const char *s1, const char *s2)
```
字符串字串匹配算法KMP简介：https://www.cnblogs.com/zzzdp/p/9416570.html

# Input

The inputs are 2 cstrings s1 and s2.

# Output

The output is the first index of s1 as the substring of s2. If s1 isn't the substring of s2, then returns -1.

# Sample Input 1
```
Abc
eAbc
```

# Sample Output 1
```
1
```

# Sample Input 2
```
aBd
a
```
# Sample Output 2
```
-1
```

# Hint
Don't submit the main() function.
