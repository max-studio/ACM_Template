/* 
 * 例题：前缀和
 * 例题链接：https://www.acwing.com/problem/content/797/
 */

#include <iostream>

using namespace std;

const int N = 1e5 + 10;

int n, m;
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

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);		// 输入输出取消同步流，提高速度
    cin >> n >> m;
    for (int i = 1; i <= n; ++ i)
        cin >> s[i];
    // 构建前缀和数组
    build(n);
    for (int i = 1; i <= m; ++ i) {
        int l, r;
        cin >> l >> r;
        // 查询区间值并输出
        cout << query(l, r) << '\n';
    }
    return 0;
}