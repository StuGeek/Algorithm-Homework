# week9 索引数组

Description
        高兴同学在一家电话公司实习。电话公司有一个长长的用户信息列表，公司需要根据用户的姓名、电话和地址查询相关信息。公司老板请高兴同学帮忙设计一个便于实现这些查询的程序。高兴同学懂得，对于这种问题，分别为用户姓名、电话和地址设计三个索引数组（access array）是一个比较好的解决方案。姓名的索引数组是按照姓名排列时，用户在用户列表中位置的列表。例如，假如用户信息列表是包含姓名、电话和地址的列表［(Wang, 123456, address1), (Gao, 23456, address2), (Li, 55688, address3), (Hao, 56788, address4)］，那么姓名的索引数组是［1, 3, 2, 0] ，即按照用户姓名的字典序列出这些用户的在列表中的序号（序号从0开始），如，排第1位的是列表中“Gao”用户，下一位是"Hao"用户, 下一位是“Li“，最后一位是”Wang“用户。

      现在，请你根据用户列表，创建姓名的索引数组：

vector<int> accessArray(const vector<Customer> & table);

 这里假定用户信息是包含三个域的Customer的向量，函数返回第一个姓名域name的索引数组，其中Customer定义如下：

struct Customer {
  string name;
  string phone;
  string address;
};
Hint
 测试函数已经包含了vector, string和 Customer的定义，你只需要提交函数的实现。另外，对应姓名相同的客户在索引数组中的先后没有要求。