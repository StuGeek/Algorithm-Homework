# week9 账号密码查询

问题：请用哈希表存储客户的账户和密码（使用md5加密）信息，然后检查用户输入的账户和密码是否正确。

输入：第一行是一个正整数n(<=100,000)，表示客户数目，然后是每个客户的信息。每个客户信息的第一行是账号，第二行是用md5加密的密码。账号和密码都是字符串。

账户信息之后是用户登录信息。第一行是登录用户数目m(<=10,000), 然后是m个用户输入的账户（第一行）和密码（第二行）。假设用户名只含字母。

输出：检查每个用户（共m个登录用户）的登录信息，如果正确，则输出账户及“OK”字样，否则输出账户及“Invalid user name or password”字样。

输入样例：
```
3
BANDEAU
85f2af9b5c5cd2df0cb940712deb6b67
CONTORTEDNESS
5c56e2d40077593101afb551614deaa4
SUTURES
50fdb856ee30e2a471ffd0d720f32292
3
BANDEAU
^o=fq^*q
UPSTIRS
AYbdy8!z
CONTORTEDNESS
12345678
```

输出样例：
```
BANDEAU:OK
UPSTIRS:Invalid user name or password
CONTORTEDNESS:Invalid user name or password
```

注意：你需要使用给定的函数md5, 输入是密码明文字符串，输出是加密的字符串。
你只需要在自己的代码中#include "md5.h"即可使用函数md5. 


