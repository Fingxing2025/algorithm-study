#include <bits/stdc++.h>
using namespace std;
int main()
{
	string s;
	while (cin >> s)
	{
		// 这里只是演示“把变量地址按字节解释后输出十六进制”。
		// 常用于观察不同类型在内存中的底层表示，以及机器的字节序。
		bool isdouble = false;
		// 只要字符串里出现小数点，就把它当成 double 处理；
		// 否则按 int 处理。
		for (int i = 0; i < s.size(); ++i)
			if (s[i] == '.')
			{
				isdouble = true;
				break;
			}
		if (isdouble)
		{
			double val = stod(s);
			// 把 double 的地址强转成 unsigned char*，
			// 这样就能按“一个字节一个字节”去读它在内存中的原始表示。
			unsigned char *by = (unsigned char *)(&val);
			for (int i = 0; i < sizeof(double); ++i)
				// setw(2)+setfill('0') 保证每个字节都以两位十六进制输出。
				cout << hex << setw(2) << setfill('0') << (int)(by[i]) << " ";
			cout << "\n";
		}
		else
		{
			int val = stoi(s);
			// int 分支和 double 分支做的是同一件事，只是读取的对象类型不同。
			unsigned char *by = (unsigned char *)(&val);
			for (int i = 0; i < sizeof(int); ++i)
				cout << hex << setw(2) << setfill('0') << (int)(by[i]) << " ";
			cout << "\n";
		}
	}
}
