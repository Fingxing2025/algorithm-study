#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int length, zero_count = 0, first_column_cursor = 0;
	cin >> length;
	// 这里在按 BWT 的 LF-mapping 思想重建原串。
	// last_column[i] 只含 0/1，last_to_first 记录“最后一列 -> 第一列”的对应关系。
	vector<int> last_column(length), last_to_first(length), rebuild_order(length);
	for (int i = 0; i < length; ++i)
	{
		cin >> last_column[i];
		// 先统计有多少个 0；
		// 因为把最后一列稳定排序后，所有 0 会排在前面，1 会排在后面。
		zero_count += (last_column[i] == 0);
	}
	// 先把最后一列中的所有 0 对应位置按出现顺序放进 invf，
	// 等价于构造“排序后第一列”的前半段。
	for (int i = 0; i < length; ++i)
		if (last_column[i] == 0)
			last_to_first[first_column_cursor++] = i;
	// 再把所有 1 放进去，构成第一列的后半段。
	for (int i = 0; i < length; ++i)
		if (last_column[i] == 1)
			last_to_first[first_column_cursor++] = i;
	int current_last_column_pos = 0;
	// 从 BWT 的首行开始，反复做 LF-mapping：
	// “当前最后一列的位置 -> 对应第一列的位置”。
	// rebuild_order[i] 记录恢复原串时，第 i 步应该取最后一列中的哪一个字符。
	for (int i = length - 1; i >= 0; --i)
	{
		// 当前 current_last_column_pos 表示“这一轮回溯时所在的最后一列位置”。
		// 把它记进 rebuild_order[i] 后，再跳到与之对应的第一列位置，准备下一轮回溯。
		rebuild_order[i] = current_last_column_pos;
		current_last_column_pos = last_to_first[current_last_column_pos];
	}
	// 按 rebuild_order 逆序恢复字符。
	// rebuild_order[0] 对应的是恢复出的第一个字符，它落在第一列前 zero_count 个位置时就是 0，否则是 1。
	string decoded = rebuild_order[0] + 1 <= zero_count ? "0" : "1";
	int decoded_zero_count = (decoded[0] == '0');
	for (int i = 0; i < length - 1; ++i)
	{
		// last_column[rebuild_order[i]] 就是当前应接到答案前面的那个字符。
		string current_token(1, last_column[rebuild_order[i]] + '0');
		// 这个模板的输出格式本身就在字符间加空格，所以这里补一个空格再拼接。
		current_token += " ";
		decoded_zero_count += (current_token[0] == '0');
		// 因为 rebuild_order 是从后往前回溯出来的，所以这里要不断往字符串前面拼。
		decoded = current_token + decoded;
	}
	// 最后再校验一次 0 的数量，数量对不上说明输入本身不合法或无法还原。
	if (decoded_zero_count == zero_count)
		cout << decoded;
	else
		cout << "-1";
}
