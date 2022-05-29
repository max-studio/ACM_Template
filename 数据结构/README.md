## 数据结构

涉及到数据结构的相关模板整理

### 树状数组

```C++
// 模板内相关数据
int w[N];		// 树状数组, 从 1 开始计数
int n;		// 长度

// 返回最小的为 1 的位
int lower(int x) {
    return x & -x;
}

// 在第 idx 位置加上 val
void add(int idx, int val) {
    for (int i = idx; i <= n; i += lower(i))
        w[i] += val;
}

// 查询 [1, idx] 的和
int query(int idx) {
    int ans = 0;
    for (int i = idx; i; i -= lower(i))
        ans += w[i];
   	return ans;
}
```

