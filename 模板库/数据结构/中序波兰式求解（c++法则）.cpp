#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// 判断当前位置是否属于数字的一部分：
// 允许整数、小数，以及作为负号的 '-'.
bool Isdigit(string line, int i)
{
	// 这里的“数字字符”不只是 0~9，
	// 还要把“合法的一元负号”和小数点一起视作数字的一部分。
	// 例如 "-12.5" 在扫描时应该被整体识别成一个数，而不是 '-' 和数字分开处理。
	return isdigit(line[i]) || line[i] == '-' && (i == 0 || (i > 0 && line[i - 1] != ')' && !isdigit(line[i - 1]))) || line[i] == '.';
}
// 从左括号开始提取一整段匹配括号内部的表达式。
string match(string line, int &i)
{
	int cnt = 1;
	string ans;
	++i;
	while (i < line.size())
	{
		// 只有在“当前看到右括号，且括号层数正好回到 1”时，
		// 才说明最外层这对括号已经完整匹配结束。
		if (line[i] == ')' && cnt == 1)
			break;
		if (line[i] == '(')
			++cnt;
		else if (line[i] == ')')
			--cnt;
		// 只把最外层括号内部的内容收进 ans，不把包裹它的那对括号本身放进去。
		ans += line[i++];
	}
	return ans;
}
// 注意减法、除法的顺序：栈顶元素是右操作数。
double cal(double t1, double t2, char op)
{
	// 注意这里的参数顺序：
	// t1 是后弹出的“右操作数”，t2 是先弹出的“左操作数”。
	// 所以减法和除法必须写成 t2-t1、t2/t1。
	if (op == '+')
		return t1 + t2;
	if (op == '-')
		return t2 - t1;
	if (op == '*')
		return t1 * t2;
	if (op == '/')
		return t2 / t1;
}
// 先弹出两个数和一个运算符，完成一次栈顶计算。
void fstcal(stack<pair<double, bool>> &nums, stack<char> &ops)
{
	auto t1 = nums.top();
	nums.pop();
	auto t2 = nums.top();
	nums.pop();
	// 只要两个操作数里有一个是浮点数，这一步计算结果就必须继续按浮点数保留。
	bool f = t1.second || t2.second;
	char op = ops.top();
	ops.pop();
	double t = cal(t1.first, t2.first, op);
	// 若当前表达式一直都是整数运算，就把结果截成 long long 风格，
	// 保持和题目里“整数表达式按整数算”的规则一致。
	t = f ? t : (ll)t;
	nums.push({t, f});
}
// 把当前栈里能算的低优先级运算全部算完。
void calstack(stack<pair<double, bool>> &nums, stack<char> &ops)
{
	// 这里会把栈里现有的低优先级运算全部结清。
	// 它通常在遇到新的 + / - 时调用，因为 + 和 - 不能越过之前同级的运算。
	while (nums.size() >= 2 && !ops.empty())
	{
		fstcal(nums, ops);
	}
}
// 读出一个完整数字，并记录它是否是浮点数。
double getnum(string line, int &i, bool &f)
{
	string ans;
	while (Isdigit(line, i))
	{
		// 扫描到小数点时，说明这个数和后续涉及它的计算都要转成浮点语义。
		if (line[i] == '.')
			f = 1;
		ans.push_back(line[i++]);
	}
	// 外层 while 结束时 i 已经多走了一位，回退一格交给主循环统一 ++i。
	--i;
	return stod(ans);
}
// 递归求值：括号内部会再次调用 solve。
double solve(string line, bool &flag)
{
	// 先粗略扫一遍当前表达式里有没有小数点。
	// 这决定了最终输出时是按整数还是浮点数格式保留。
	for (int i = 0; i < line.size(); ++i)
		if (line[i] == '.')
		{
			flag = true;
			break;
		}
	int i = 0;
	stack<pair<double, bool>> nums;
	stack<char> ops;
	while (i < line.size())
	{
		if (line[i] == '-' && i + 1 < line.size() && line[i + 1] == '(' && (i == 0 || i > 0 && !isdigit(line[i - 1]) && line[i - 1] != ')'))
		{
			// 这一分支专门处理形如 "-(...)" 的一元负号。
			// 它不是减法，而是先把括号里的整体值算出来，再统一取反。
			++i;
			string m = match(line, i);
			bool f = false;
			double t = -solve(m, f);
			t = f ? t : (ll)t;
			nums.push({t, f});
			// 若前面堆着 * 或 /，说明当前这个整体值一出来就该立刻参与高优先级计算。
			if (!ops.empty() && (ops.top() == '*' || ops.top() == '/'))
				fstcal(nums, ops);
		}
		else if (Isdigit(line, i))
		{
			// 普通数字分支：读出一个完整数字并压入数栈。
			bool f = false;
			double t = getnum(line, i, f);
			nums.push({t, f});
			// 和上面同理，若前面等着乘除，就先把高优先级运算结掉。
			if (!ops.empty() && (ops.top() == '*' || ops.top() == '/'))
				fstcal(nums, ops);
		}
		else
		{
			if (line[i] == '(')
			{
				// 普通括号分支：先递归算出括号内部的值，再把它当成一个普通数字压栈。
				string m = match(line, i);
				bool f = false;
				double t = solve(m, f);
				t = f ? t : (ll)t;
				nums.push({t, f});
				if (!ops.empty() && (ops.top() == '*' || ops.top() == '/'))
					fstcal(nums, ops);
			}
			else if (line[i] == '+' || line[i] == '-')
			{
				// 遇到 + 或 - 时，说明之前栈里的同级运算优先级已经不低于当前运算，
				// 可以全部结算后再把当前运算符压栈。
				calstack(nums, ops);
				ops.push(line[i]);
			}
			else if (line[i] == '*' || line[i] == '/')
			{
				// * 和 / 先压栈，等右操作数读出来后再立刻结算。
				ops.push(line[i]);
			}
		}
		++i;
	}
	// 扫描完整个表达式后，把栈里还没做完的低优先级运算统一结算。
	calstack(nums, ops);
	return nums.top().first;
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	string line;
	getline(cin, line);
	bool flag = false;
	// solve 会递归处理整条中序表达式，并通过 flag 告诉主函数结果是否应按浮点输出。
	double ans = solve(line, flag);
	if (flag)
		cout << fixed << setprecision(3) << ans;
	else
		cout << fixed << setprecision(0) << (ll)ans;
}
