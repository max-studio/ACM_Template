## 区间操作

对于区间进行修改、查询等算法模板的整理

## 前缀和

```C++
const int N = 1e5 + 10;

// 前缀和数组，存储前缀和
int s[N];

// 构建前缀和数组，长度为 len
void build(int len) {
    for (int i = 1; i <= len; ++ i)
        s[i] += s[i - 1];
}

// 查询区间 [l, r] 的元素的和
int query(int l, int r) {
    return s[r] - s[l - 1];
}
```