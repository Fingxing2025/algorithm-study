#include <bits/stdc++.h>
using namespace std;
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	vector<int> v = {10, 20, 30, 40, 50};
	int target = 25; // 外部变量

	// [&](...) 表示按引用捕获外部变量，因此比较函数里可以直接使用 target。
	// 这里的排序规则不是按数值本身从小到大，而是按“离 target 的距离”从近到远。
	// 也就是说，比较函数返回 true 的条件是：a 比 b 更应该排在前面。
	sort(v.begin(), v.end(), [&](int a, int b)
		 { return abs(a - target) < abs(b - target); });
	// 排序后，离 25 越近的数会越靠前。
}
