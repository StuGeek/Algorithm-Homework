# week15 哈夫曼树1

哈夫曼树编码

参考链接：<https://blog.csdn.net/qq_29519041/article/details/81428934>
<br>给定K个不同的字符和它们的频率，建立一棵哈夫曼树对字符进行编码，合并节点时频率小的在右边，频率相同时字符小的在右边。
<br>按照后序遍历的顺序输出字符。
<br>输入包含两部分，第一部分一个数字K表示有K个字符，第二部分有K行，每行两个数表示字符和它的频率</br>
<br>样例</br>
<br>输入
<br>7 
<br>A 5
<br>F 5
<br>C 7
<br>G 13
<br>E 34
<br>B 24
<br>D 17
<br>输出
<br>E
<br>D
<br>G
<br>B
<br>F
<br>A
<br>C