# week8 Substring

Dr lee cuts a string S into N pieces,s\[1\],…,s\[N\].   
Now, Dr lee gives you these N sub-strings: s\[1\],…s\[N\]. There might be several possibilities that the string S could be. For example, if Dr. lee gives you three sub-strings {“a”,“ab”,”ac”}, the string S could be “aabac”,”aacab”,”abaac”,…
Your task is to output the lexicographically smallest S.

**输入格式**
The first line of the input is a positive integer T. T is the number of the test cases followed.
The first line of each test case is a positive integer N (1 <=N<= 8 ) which represents the number of sub-strings. After that, N lines followed. The i-th line is the i-th sub-string s\[i\]. Assume that the length of each sub-string is positive and less than 100.

**输出格式**
The output of each test is the lexicographically smallest S. No redundant spaces are needed.

**样例输入**
1
3
a
ab
ac

**样例输出**
aabac
