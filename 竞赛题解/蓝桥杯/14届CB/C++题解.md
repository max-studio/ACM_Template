[TOC]

## A: 日期统计

**题目思路:**

直接暴力 8 重 for 循环，因为年份是确定的，所以可以减少一些无效的枚举，时间可控。用 map 存一下出现的日期，最后输出 map 的长度即可。答案：235。

**Code:**
```C++
#include <iostream>
#include <map>
#include <vector>

using namespace std;

vector<int> nums = {5, 6, 8, 6, 9, 1, 6, 1, 2, 4, 9, 1, 9, 8, 2, 3, 6, 4, 7, 7, 5, 9, 5, 0, 3, 8, 7, 5, 8, 1, 5, 8, 6, 1, 8, 3, 0, 3, 7, 9, 2, 7, 0, 5, 8, 8, 5, 7, 0, 9, 9, 1, 9, 4, 4, 6, 8, 6, 3, 3, 8, 5, 1, 6, 3, 4, 6, 7, 0, 7, 8, 2, 7, 6, 8, 9, 5, 6, 5, 6, 1, 4, 0, 1, 0, 0, 9, 4, 8, 0, 9, 1, 2, 8, 5, 0, 2, 5, 3, 3};
int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main() {
    int n = nums.size();
    map<int, bool> q;
    for (int y1 = 0; y1 < n; ++ y1) {
        if (nums[y1] != 2)
            continue;
        for (int y2 = y1 + 1; y2 < n; ++ y2) {
            if (nums[y2] != 0)
                continue;
            for (int y3 = y2 + 1; y3 < n; ++ y3) {
                if (nums[y3] != 2)
                    continue;
                for (int y4 = y3 + 1; y4 < n; ++ y4) {
                    if (nums[y4] != 3)
                        continue;
                    for (int m1 = y4 + 1; m1 < n; ++ m1) {
                        if (nums[m1] > 1)
                            continue;
                        for (int m2 = m1 + 1; m2 < n; ++ m2) {
                            for (int d1 = m2 + 1; d1 < n; ++ d1) {
                                for (int d2 = d1 + 1; d2 < n; ++ d2) {
                                    int year = nums[y1] * 1000 + nums[y2] * 100 + nums[y3] * 10 + nums[y4];
                                    int month = nums[m1] * 10 + nums[m2];
                                    int day = nums[d1] * 10 + nums[d2];
                                    if (year != 2023)
                                        continue;
                                    if (month < 1 || month > 12)
                                        continue;
                                    if (day < 1 || day > days[month])
                                        continue;
                                    q[year * 10000 + month * 100 + day] = true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    cout << q.size();
    return 0;
}
```

## B: 01 串的熵
待补

## C: 冶炼金属
**题目思路:**

二分枚举最大最小值即可。判断枚举的值是否可以满足要求。

**Code:**

```C++
#include <iostream>

using namespace std;

const int N = 1e4 + 10;

int n;
int a[N], b[N];

bool checkMin(int x) {
    for (int i = 1; i <= n; ++ i) {
        // 如果还可以再冶炼一个特殊金属，则不符合条件
        if (1ll * (b[i] + 1) * x <= a[i])
            return false;
    }
    return true;
}

bool checkMax(int x) {
    for (int i = 1; i <= n; ++ i) {
        // 如果无法冶炼出 a[i] 个特殊金属，不符合条件
        if (1ll * b[i] * x > a[i])
            return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n;
    for (int i = 1; i <= n; ++ i)
        cin >> a[i] >> b[i];
    int minV, maxV;
    // 二分最小值
    int l = 1, r = 1e9;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (checkMin(mid))
            r = mid;
        else 
            l = mid + 1;
    }
    minV = l;
    // 二分最大值
    l = 1, r = 1e9;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (checkMax(mid))
            l = mid;
        else 
            r = mid - 1;
    }
    maxV = l;
    cout << minV << " " << maxV;
    return 0;
}
```

## D: 飞机降落
待补

## E: 接龙数列
**题目思路:**

简单 dp，用 `f[i]` 表示当前以 `i` 结尾的情况下，需要删除多少个数字。最后取最小值即可。

**Code:**

```C++
#include <iostream>
#include <cstring>

using namespace std;

int n, x;
int f[11];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    // 初始化
    memset(f, 0x3f3f3f3f, sizeof f);
    cin >> n;
    for (int i = 1; i <= n; ++ i) {
        cin >> x;
        // 获取结尾的数字
        int e = x % 10;
        // 处理出开始的数字，存在 x 中
        while (x >= 10)
            x /= 10;
        // 如果是第一个数字，则无需考虑与上一个数字接龙
        if (i == 1) {
            f[e] = 0;
            continue;
        }
        // 当前数字不删除，接龙
        f[e] = f[x];
        // 当前数字删除，处理以其他数字结尾的情况
        for (int j = 0; j <= 9; ++ j)
            if (j != e)
                f[j] ++;
    }
    // 取删除最少的情况
    int ans = f[0];
    for (int i = 1; i <= 9; ++ i)
        ans = min(ans, f[i]);
    cout << ans;
    return 0;
}
```

## F: 岛屿个数
待补

## G: 子串简写
**题目思路:**

翻译一下题目，就是对于任意 `s[i] == c2` 并且 $i \leq k$ 的情况下， $[1, i - k + 1]$ 中有多少个 c1。
那么显然是一个非常简单的前缀和操作，板子题。

**Code:**

```C++
#include <iostream>
#include <cstring>

using namespace std;

const int N = 5e5 + 10;

int n, k;
char c1, c2;
string s;
int f[N];

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> k >> s >> c1 >> c2;
    n = s.size();
    // 构造前缀和数组
    for (int i = 0; i < n; ++ i) 
        f[i + 1] = f[i] + (s[i] == c1);
    long long ans = 0;
    // 计算结果
    for (int i = k; i <= n; ++ i) 
        if (s[i - 1] == c2) 
            ans += f[i - k + 1];
    cout << ans;
    return 0;
}
```

## H: 整数删除
**题目思路:**

因为数据比较大，每次只找最小的值，所以我们可以使用堆排序来做。每一次操作中，找到最小的值，删除这个值，将其左右的数加上这个值，重新排序。

我们需要解决的问题：

1. 在有的数被删除的情况下，如何快速找到该数的左右两个数。
**解决方案：**使用两个数组，`l[i]` 记录左边的数的下标，`r[i]` 记录右边的数的下标
2. 如何快速在堆中找到其左右两个数，并排序。
**解决方案：**使用一个 `idx[i]` 数组记录第 i 个数在堆中的位置
3. 如何快速通过找到堆顶元素在数组中的下标。
**解决方案：**堆中只存下标，排序时按照该下标对应的值进行排序

**Code:**

```C++
#include <iostream>
#include <cstring>

using namespace std;
const int N = 5e5 + 10;

int n, k;
// 存储数组
long long a[N];
// l 和 r 记录左右数字的下标，idx 记录在堆中的位置
int l[N], r[N], idx[N];
// 小顶堆，排序用
int h[N];

// 构建堆时，将 u 位置的元素和其子节点比较，小的元素在上层。e 为堆的元素个数
void up(int u, int e) {
    // 取左右子节点下标
    int left = u << 1, right = (u << 1) | 1;
    // v 为三个节点中，最小的节点的位置
    int v = u;
    // 如果左子节点存在（下标不大于 e），判断是否小于 v 位置的元素，如果小于，更新 v
    if (left <= e && (a[h[left]] < a[h[v]] || (a[h[left]] == a[h[v]] && h[left] < h[v])))
        v = left;
    // 判断右子节点，更新 v
    if (right <= e && (a[h[right]] < a[h[v]] || (a[h[right]] == a[h[v]] && h[right] < h[v])))
        v = right;
    // 如果 v != u，说明需要交换
    if (v != u) {
        swap(h[v], h[u]);
        // 更新数组元素在堆中的位置
        idx[h[v]] = v;
        idx[h[u]] = u;
    }
}

void down(int u, int e) {
    // 保持堆有序，判断 u 位置元素是否需要向下移动
    int left = u << 1, right = (u << 1) | 1;
    int v = u;
    if (left <= e && (a[h[left]] < a[h[v]] || (a[h[left]] == a[h[v]] && h[left] < h[v]))) {
        v = left;
    }
    if (right <= e && (a[h[right]] < a[h[v]] || (a[h[right]] == a[h[v]] && h[right] < h[v])))
        v = right;
    // 如果需要向下移动，则更新 idx 数组，并持续向下判断
    if (v != u) {
        swap(h[u], h[v]);
        idx[h[v]] = v;
        idx[h[u]] = u;
        // 判断是否还需要向下移动
        down(v, e);
    }
}

// 基于堆中的元素，构建小顶堆
void build(int s, int e) {
    for (int i = (e >> 1); i; -- i)
        up(i, e);
}

int main()  {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);
    cin >> n >> k;
    // 初始化元素
    for (int i = 1; i <= n; ++ i) {
        cin >> a[i];
        l[i] = i - 1;
        r[i] = i + 1;
        h[i] = idx[i] = i;
    }
    build(1, n);
    // 每次操作后，堆中的元素个数减少 1，用 e 记录
    int e = n;
    for (int i = 1; i <= k; ++ i) {
        // 每次小顶堆的堆顶为最小的元素
        int u = h[1], left = l[u], right = r[u];
        // 左右位置的数加上被删除的数
        a[left] += a[u];
        a[right] += a[u];
        // 更新左右两个数的 l 和 r 数组
        r[left] = right;
        l[right] = left;
        // 删除当前这个数，计为 -1
        a[u] = -1;
        // 删除堆顶元素，并更新堆的长度
        swap(h[1], h[e]);
        e --;
        // 保持堆的有序
        // 因为左右两个数都变大了，所以需要向下移动
        down(idx[left], e);
        down(idx[right], e);
        // 将堆顶元素向下移动
        down(1, e);
    }
    for (int i = 1; i <= n; ++ i) {
        // 如果为 -1，说明该元素被删除了，不输出
        if (a[i] == -1)
            continue;
        cout << a[i] << " ";
    }
    return 0;
}
```

## I: 景区导游

待补

## J: 砍树

待补