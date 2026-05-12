#include <iostream>
#include <string>
#include <algorithm> // 包含 reverse, sort, count
#include <cctype>    // 包含 toupper, tolower
using namespace std;

// 这个文件是 string 常用操作速查表，适合复习时快速翻阅。
// ==========================================
// 模块 1：字符串基础与修改操作
// ==========================================
void test_basic_and_modify()
{
    cout << "--- 1. 基础与修改 ---" << endl;
    string s = "Hello";

    // 基础信息
    cout << "原串: " << s << "，长度: " << s.size() << endl;

    // 拼接操作 (最常用 +=)
    s += " C++";      // "Hello C++"
    s.push_back('!'); // "Hello C++!"
    cout << "拼接后: " << s << endl;

    // 尾部删除
    s.pop_back(); // "Hello C++"
    cout << "删去尾字符: " << s << endl;

    // 插入与区间删除 (注意：参数是起始下标和长度)
    s.insert(6, "Awesome "); // 在下标6处插入："Hello Awesome C++"
    cout << "插入后: " << s << endl;

    s.erase(6, 8);                   // 从下标6开始，删除8个字符
    cout << "删除后: " << s << endl; // 变回 "Hello C++"
}

// ==========================================
// 模块 2：截取与查找 (?? 考试最高频)
// ==========================================
// substr 和 find 是竞赛里最常用的两个字符串接口。
void test_substr_and_find()
{
    cout << "\n--- 2. 截取与查找 ---" << endl;
    string s = "abcdebc";

    // 截取: substr(起始下标, 长度)
    string sub1 = s.substr(1, 3); // 从下标1开始截3个字符 -> "bcd"
    string sub2 = s.substr(3);    // 从下标3开始一直到末尾 -> "debc"
    cout << "截取子串1: " << sub1 << " | 截取子串2: " << sub2 << endl;

    // 查找: find(目标)
    size_t pos1 = s.find("bc");    // 第一次出现 "bc" 的位置 -> 1
    size_t pos2 = s.find("bc", 2); // 从下标2开始往后找 "bc" -> 5
    cout << "第一次找到 'bc' 的下标: " << pos1 << endl;
    cout << "跳过前面，再次找到 'bc' 的下标: " << pos2 << endl;

    // 判断找不到的情况 (必须用 string::npos)
    if (s.find("xyz") == string::npos)
    {
        cout << "查找 'xyz' 的结果: 未找到 (string::npos)!" << endl;
    }
}

// ==========================================
// 模块 3：类型互相转换 (高精度/模拟题神技)
// ==========================================
// to_string / stoi / stoll / stod 是字符串与数值互转的常用接口。
void test_conversions()
{
    cout << "\n--- 3. 字符串与数字转换 (含 stod) ---" << endl;

    // 1. 数字转字符串 (整数和浮点数都可以用 to_string)
    int num = 9876;
    double pi = 3.14159;
    string s_num = to_string(num);
    string s_pi = to_string(pi);
    cout << "整数转字符串: " << s_num << endl;
    cout << "浮点转字符串: " << s_pi << " (注意: to_string 默认保留6位小数)" << endl;

    // 2. 字符串转数字 (stoi, stoll, stod)
    string s_int = "1024";
    string s_ll = "123456789012345";
    string s_double = "2.71828";

    int a = stoi(s_int);       // string to int
    long long b = stoll(s_ll); // string to long long
    double c = stod(s_double); // string to double (?? 新增)

    cout << "字符串转整数 (stoi): " << a + 1 << " (验证加法)" << endl;
    cout << "字符串转超大整数 (stoll): " << b << endl;
    cout << "字符串转浮点数 (stod): " << c * 2 << " (验证乘法)" << endl;
}

// ==========================================
// 模块 4：搭配算法与大小写转换
// ==========================================
// reverse / sort / count 等算法都能直接作用在 string 上。
void test_algorithm()
{
    cout << "\n--- 4. 算法与大小写 ---" << endl;
    string s = "abABaba";

    // 统计某个字符的出现次数
    int cnt = count(s.begin(), s.end(), 'a');
    cout << "'a' 出现的次数: " << cnt << endl;

    // 反转字符串 (回文题必备)
    reverse(s.begin(), s.end());
    cout << "反转后: " << s << endl;

    // 字符串排序 (按字典序)
    sort(s.begin(), s.end());
    cout << "排序后: " << s << endl;

    // 遍历修改：全部转大写字母
    string test_case = "Code_123!";
    for (int i = 0; i < test_case.size(); i++)
    {
        if (test_case[i] >= 'a' && test_case[i] <= 'z')
        {
            test_case[i] -= 32;
        }
    }
    cout << "全部转大写后: " << test_case << endl;
}

// ==========================================
// 模块 5：输入流避坑指南 (仅作演示)
// ==========================================
void test_io_trap()
{
    /*
    cout << "\n--- 5. 致命输入流陷阱演示 ---" << endl;
    int n;
    cin >> n;
    cin.ignore(); // 核心：吃掉回车！
    string s;
    getline(cin, s);
    */
}

int main()
{
    test_basic_and_modify();
    test_substr_and_find();
    test_conversions();
    test_algorithm();
    test_io_trap();

    return 0;
}
