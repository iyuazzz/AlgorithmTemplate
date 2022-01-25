快速枚举子集
```cpp
for (int S0 = S; S0; S0 = S & (S0 - 1))
```
枚举S0为S子集  会含有S 不含0
