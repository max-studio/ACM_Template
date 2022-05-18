// 例题：树状数组 1
// 例题链接：https://www.luogu.com.cn/problem/P3374

#include <bits/stdc++.h>

using namespace std;

const int N = 5E5 + 10;

int n, m;
int w[N];
int op, x, y;

int lower(int x) {
	return x & -x;
}

void add(int idx, int val) {
	for (int i = idx; i <= n; i += lower(i))
		w[i] += val;
}

int query(int idx) {
	int ans = 0;
	for (int i = idx; i; i -= lower(i))
		ans += w[i];
	return ans;
}

int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr), cout.tie(nullptr);		// 输入输出取消同步流，提高速度
	cin >> n >> m;
	for (int i = 1; i <= n; ++ i) {
		cin >> x;
		add(i, x);		// 在第 i 个位置加上 x
	}
	while (m --) {		// 进行 m 次操作
		cin >> op >> x >> y;
		if (op == 1) 		// 在 x 处加上 y
			add(x, y);		// 添加
		else 
			cout << query(y) - query(x - 1) << '\n';		// 利用前缀和差值计算区间和
	}
	return 0;
}
