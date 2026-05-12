#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll Mod = 998244353;
class MyBigInteger
{
private:
	string a;
	string b;
	char op;
	// 把字符串转成倒序数位数组，便于从低位到高位处理。
	vector<int> trans(const string &x)
	{
		vector<int> ans;
		for (int i = x.size() - 1; i >= 0; --i)
			ans.push_back(x[i] - '0');
		return ans;
	}
	// 比较两个非负高精度数的大小，返回 a >= b 是否成立。
	bool cmp(vector<int> &a, vector<int> &b)
	{
		if (a.size() != b.size())
			return a.size() > b.size();
		for (int i = a.size() - 1; i >= 0; --i)
			if (a[i] != b[i])
				return a[i] > b[i];
		return true;
	}
	// 把倒序数位数组还原成正常顺序的字符串。
	string invtrans(const vector<int> &c)
	{
		string s;
		for (int i = c.size() - 1; i >= 0; --i)
			s.push_back(c[i] + '0');
		return s;
	}
	// 高精度加法，同时兼容带符号的情况。
	string Plus(string a, string b)
	{
		if (a[0] != '-' && b[0] != '-')
		{
			vector<int> x = trans(a);
			vector<int> y = trans(b);
			vector<int> c;
			int t = 0;
			for (int i = 0; i < x.size() || i < y.size(); ++i)
			{
				// t 先带着上一位的进位进入当前位，再把两数当前位加上。
				if (i < x.size())
					t += x[i];
				if (i < y.size())
					t += y[i];
				// 当前位保留个位，十位及以上留给下一轮作为进位。
				c.push_back(t % 10);
				t /= 10;
			}
			if (t)
				c.push_back(1);
			return invtrans(c);
		}
		// (-a)+b 等价于 b-a。
		else if (a[0] == '-' && b[0] != '-')
			return Minus(b, a.substr(1));
		// a+(-b) 等价于 a-b。
		else if (a[0] != '-' && b[0] == '-')
			return Minus(a, b.substr(1));
		// (-a)+(-b) 等价于 -(a+b)。
		else
			return "-" + Plus(a.substr(1), b.substr(1));
	}
	// 高精度减法，同时兼容带符号的情况。
	string Minus(string a, string b)
	{
		if (a[0] != '-' && b[0] != '-')
		{
			vector<int> x = trans(a);
			vector<int> y = trans(b);
			bool flag = cmp(x, y);
			// 为了统一处理，先保证 x >= y；
			// 若原本 a < b，最后再把负号补回去。
			if (!flag)
				swap(x, y);
			vector<int> c;
			int t = 0;
			for (int i = 0; i < x.size(); ++i)
			{
				// t 在这里表示“上一位是否向当前位借了 1”。
				t = x[i] - t;
				if (i < y.size())
					t -= y[i];
				// (t+10)%10 能统一处理当前位够减和不够减两种情况。
				c.push_back((t + 10) % 10);
				// 若不够减，则下一位还要继续借 1。
				if (t < 0)
					t = 1;
				else
					t = 0;
			}
			while (c.size() > 1 && c.back() == 0)
				c.pop_back();
			// 若结果本身就是 0，就不要保留负号。
			if (c.size() == 1 && c[0] == 0)
				flag = true;
			return flag ? invtrans(c) : "-" + invtrans(c);
		}
		// a-(-b) 等价于 a+b。
		else if (a[0] != '-' && b[0] == '-')
			return Plus(a, b.substr(1));
		// (-a)-b 等价于 -(a+b)。
		else if (a[0] == '-' && b[0] != '-')
			return "-" + Plus(a.substr(1), b);
		// (-a)-(-b) 等价于 b-a。
		else
			return Minus(b.substr(1), a.substr(1));
	}
	// 高精度乘法：按竖式乘法模拟。
	string Times(string a, string b)
	{
		bool flag = false;
		if (a[0] == '-')
		{
			a = a.substr(1);
			flag = !flag;
		}
		if (b[0] == '-')
		{
			b = b.substr(1);
			flag = !flag;
		}
		vector<int> x = trans(a);
		vector<int> y = trans(b);
		vector<int> c(x.size() + y.size() + 1);
		for (int i = 0; i < x.size(); ++i)
			for (int j = 0; j < y.size(); ++j)
				// 第 i 位与第 j 位相乘，会累计到结果的第 i+j 位。
				c[i + j] += x[i] * y[j];
		int t = 0;
		for (int i = 0; i < c.size(); ++i)
		{
			// 把这一位累计的值和前面传下来的进位一起结算。
			t += c[i];
			c[i] = t % 10;
			t /= 10;
		}
		while (c.size() > 1 && c.back() == 0)
			c.pop_back();
		if (c.size() == 1 && c[0] == 0)
			flag = false;
		return flag ? "-" + invtrans(c) : invtrans(c);
	}
	// 高精度除法：朴素做法，适合模板复习，不适合特别大的数据范围。
	string Div(string a, string b)
	{
		bool flag = false;
		if (a[0] == '-')
		{
			a = a.substr(1);
			flag = !flag;
		}
		if (b[0] == '-')
		{
			b = b.substr(1);
			flag = !flag;
		}
		if (b == "0" || b == "")
			return "0";
		vector<int> x = trans(a);
		vector<int> y = trans(b);
		// 若被除数还比除数小，商直接为 0。
		if (!cmp(x, y))
			return "0";
		vector<int> c;
		int extra = x.size() - y.size();
		// 先把除数补零到和被除数同长度，后面再逐位右移试商。
		y.insert(y.begin(), extra, 0);
		for (int i = 0; i <= extra; ++i)
		{
			int q = 0;
			// 当前位商的定义，就是“对齐后的除数还能从被除数里减去几次”。
			while (cmp(x, y))
			{
				string str_x = invtrans(x);
				string str_y = invtrans(y);
				string res = Minus(str_x, str_y);
				x = trans(res);
				q++;
			}
			c.push_back(q);
			if (!y.empty())
				// 去掉最低位对齐补的 0，相当于把除数整体右移一位。
				y.erase(y.begin());
		}
		reverse(c.begin(), c.end());
		while (c.size() > 1 && c.back() == 0)
			c.pop_back();
		if (c.size() == 1 && c[0] == 0)
			flag = false;
		return flag ? "-" + invtrans(c) : invtrans(c);
	}

public:
	MyBigInteger(string &x, string &y, char &p) : a(x), b(y), op(p) {};
	// 根据运算符分发到对应运算。
	string cal()
	{
		// 这里就是一个统一调度层：根据运算符把请求分发给对应函数。
		if (op == '+')
			return Plus(a, b);
		if (op == '-')
			return Minus(a, b);
		if (op == '*')
			return Times(a, b);
		if (op == '/')
			return Div(a, b);
	}
};
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	string a, b;
	char op;
	cin >> a >> b >> op;
	MyBigInteger t(a, b, op);
	cout << t.cal();
}
