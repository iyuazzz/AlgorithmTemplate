/*
经典结论

一个序列（不含重复元素）中某个下标i 
包含i的所有子区间的最值个数等于i这个点在笛卡尔树上的深度(根深度为1)
大根堆笛卡尔树则表示最大值个数， 反之亦然
*/


//  (w1, w2) (i, a_i)
//  w1  ->  二叉搜索树 
//  w2  ->  堆
//  这里给出的是小跟堆
//  sta[1] is root
for (int i = 1; i <= n; ++ i) {
    while(top && arr[sta[top]] > arr[i]) {
        ls[i] = sta[top --];
    }
    fa[i] = sta[top];
    if(ls[i]) fa[ls[i]] = i;
    if(fa[i]) rs[fa[i]] = i;
    sta[++ top] = i;
}