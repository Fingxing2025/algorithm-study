#include <bits/stdc++.h>
using namespace std;

using i128 = __int128_t;
using u128 = __uint128_t;

// 把十进制字符串读成 __int128。
// 因为 cin 不支持直接读 __int128，所以要手动做“当前值 * 10 + 新数字”。
// 负数不直接取反到正数处理，而是先记录符号，最后再统一加回负号。
i128 read128()
{
	string text;
	cin >> text;
	int position = 0;
	bool is_negative = false;
	if (text[position] == '-' || text[position] == '+')
	{
		is_negative = text[position] == '-';
		++position;
	}
	u128 magnitude = 0;
	for (; position < static_cast<int>(text.size()); ++position)
		magnitude = magnitude * 10 + (text[position] - '0');
	if (!is_negative)
		return static_cast<i128>(magnitude);
	// 写成 - (magnitude - 1) - 1，能避开最小负数直接取反时的溢出问题。
	return -static_cast<i128>(magnitude - 1) - 1;
}

// 把 __int128 转成字符串。
// 若 value < 0，先取“绝对值的无符号幅值”，再从低位到高位依次拆数字。
// 最后翻转字符串，就得到正常的人类阅读顺序。
string toString128(i128 value)
{
	if (value == 0)
		return "0";
	bool is_negative = value < 0;
	u128 magnitude = is_negative ? static_cast<u128>(-(value + 1)) + 1 : static_cast<u128>(value);
	string digits;
	while (magnitude > 0)
	{
		digits.push_back(char('0' + magnitude % 10));
		magnitude /= 10;
	}
	if (is_negative)
		digits.push_back('-');
	reverse(digits.begin(), digits.end());
	return digits;
}

// 直接输出 __int128，比赛时可以像输出普通整数一样复用。
void print128(i128 value)
{
	cout << toString128(value);
}

/*
输入格式：
一行输入两个整数 a、b。

输入样例：
123456789012345678901234567 1000000000000

输出样例：
a = 123456789012345678901234567
b = 1000000000000
a + b = 123456789012346678901234567
a - b = 123456789012344678901234567
a * b = 123456789012345678901234567000000000000
a / b = 123456789012345
a % b = 678901234567
compare: a > b
*/

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	// 输入两个整数 a、b。
	// 这两个数可以超过 long long，但必须仍在 __int128 的表示范围内。
	i128 a = read128();
	i128 b = read128();

	// 先原样输出一遍，验证“读入 + 输出”这一套函数是正常工作的。
	cout << "a = ";
	print128(a);
	cout << '\n';
	cout << "b = ";
	print128(b);
	cout << '\n';

	// 下面演示 __int128 最常见的几类运算。
	// 其中乘法结果也必须落在 __int128 范围内，否则依然会溢出。
	cout << "a + b = ";
	print128(a + b);
	cout << '\n';

	cout << "a - b = ";
	print128(a - b);
	cout << '\n';

	cout << "a * b = ";
	print128(a * b);
	cout << '\n';

	// 除法和取模要先判断除数是否为 0。
	// 这是语义层面的必要判定，和是不是 __int128 无关。
	if (b != 0)
	{
		cout << "a / b = ";
		print128(a / b);
		cout << '\n';

		cout << "a % b = ";
		print128(a % b);
		cout << '\n';
	}
	else
	{
		cout << "a / b = undefined (division by zero)\n";
		cout << "a % b = undefined (mod by zero)\n";
	}

	// 比较运算和普通整数完全一致，可以直接写 <、>、==。
	cout << "compare: ";
	if (a < b)
		cout << "a < b\n";
	else if (a > b)
		cout << "a > b\n";
	else
		cout << "a == b\n";

	// 编译提醒：__int128 是 GCC / Clang 扩展，MSVC 不支持。
	// 常用编译命令：g++ -std=c++17 int128示例.cpp
	return 0;
}
