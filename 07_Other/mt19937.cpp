#include <bits/stdc++.h>
 // 随机数种子  生成数字为非负数
unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 rand_num(seed);	 // 大随机数
cout << rand_num() << endl;

std::uniform_int_distribution<long long> dist(0, 1000000000);  // 给定范围
cout << dist(rand_num) << endl;