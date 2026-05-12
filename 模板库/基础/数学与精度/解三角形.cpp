#include <bits/stdc++.h>
using namespace std;
const double PI = acos(-1.0);
// 浮点比较时给一个容错范围，避免精度误差带来的误判。
bool eq(double x, double y)
{
    return fabs(x - y) <= 1e-6 * max({1.0, x, y});
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (cin >> T)
    {
        while (T--)
        {
            vector<double> raw_values(6);
            // 输入按“边,角,边,角,边,角”的顺序给出。
            // 题目里用负数表示未知量，这里统一转成 -1 作为“未填写”的标记。
            for (int i = 0; i < 6; ++i)
            {
                cin >> raw_values[i];
                if (raw_values[i] < 0)
                    raw_values[i] = -1.0;
            }
            // sides 存三条边，angles 存三条边对应的对角，方便后面直接按“三元组”处理。
            vector<double> sides = {raw_values[0], raw_values[2], raw_values[4]};
            vector<double> angles = {raw_values[1], raw_values[3], raw_values[5]};
            try
            {
                int known_side_count = 0, known_angle_count = 0;
                // 统计当前已知了几条边、几个角。
                // 后面的分支逻辑完全依赖这两个计数来判断属于哪种解三角形情形。
                for (int i = 0; i < 3; ++i)
                {
                    if (sides[i] != -1)
                        known_side_count++;
                    if (angles[i] != -1)
                        known_angle_count++;
                }
                // 角已知至少两个时，可以先利用内角和补出第三角，
                // 再配合正弦定理把其他边求出来。
                if (known_angle_count >= 2)
                {
                    // 只知道角而完全不知道边时，三角形只确定形状不确定大小，无法唯一确定。
                    if (known_side_count < 1)
                        throw 1;
                    double known_angle_sum = 0;
                    int missing_angle_index = -1;
                    // 把已知角累加起来，并记录哪个角是缺失的。
                    for (int i = 0; i < 3; ++i)
                    {
                        if (angles[i] == -1)
                            missing_angle_index = i;
                        else
                            known_angle_sum += angles[i];
                    }
                    // 若只缺一个角，直接用内角和补出来。
                    if (missing_angle_index != -1)
                        angles[missing_angle_index] = PI - known_angle_sum;
                    // 三角形三个内角之和必须为 PI，否则输入本身矛盾。
                    known_angle_sum = angles[0] + angles[1] + angles[2];
                    if (!eq(known_angle_sum, PI))
                        throw 1;
                    // 每个内角都必须严格在 (0, PI) 内。
                    for (int i = 0; i < 3; ++i)
                        if (angles[i] <= 0 || angles[i] >= PI)
                            throw 1;
                    double sine_rule_ratio = 0;
                    // 任选一组“已知边 + 对角”，先把正弦定理里的公共比值 a/sin(A) 定下来。
                    for (int i = 0; i < 3; ++i)
                    {
                        if (sides[i] != -1)
                        {
                            sine_rule_ratio = sides[i] / sin(angles[i]);
                            break;
                        }
                    }
                    // 用同一个比例恢复其余边；
                    // 如果某条边原本已知，就顺便校验它是否与正弦定理一致。
                    for (int i = 0; i < 3; ++i)
                    {
                        double calculated_side = sine_rule_ratio * sin(angles[i]);
                        if (sides[i] == -1)
                            sides[i] = calculated_side;
                        if (!eq(sides[i], calculated_side))
                            throw 1;
                    }
                }
                else
                {
                    // 如果角信息不够，则总信息量至少要达到 3 个。
                    // 否则连三角形都无法唯一确定，直接判无效。
                    if (known_angle_count + known_side_count < 3)
                        throw 1;
                }
                // 两边一角时，需要区分已知角是不是夹角。
                if (known_side_count == 2 && known_angle_count == 1)
                {
                    int missing_side_index = -1, known_angle_index = 0;
                    // missing_side_index 表示未知边的下标；
                    // known_angle_index 表示唯一已知角的下标。
                    for (int side_index = 0; side_index < 3; ++side_index)
                        if (sides[side_index] == -1)
                            missing_side_index = side_index;
                    while (angles[known_angle_index] == -1)
                        known_angle_index++;
                    if (missing_side_index == known_angle_index)
                    {
                        // i == j 说明已知角正好夹在另外两条已知边之间，属于 SAS。
                        // 直接用余弦定理求第三边。
                        int left_side_index = (missing_side_index + 1) % 3;
                        int right_side_index = (missing_side_index + 2) % 3;
                        sides[missing_side_index] = sqrt(max(0.0, sides[left_side_index] * sides[left_side_index] + sides[right_side_index] * sides[right_side_index] - 2 * sides[left_side_index] * sides[right_side_index] * cos(angles[missing_side_index])));
                    }
                    else
                    {
                        // i != j 说明已知角不是夹角，属于 SSA。
                        // 这是最容易出现“无解 / 两解 / 一解”的分支。
                        // 这里的下标关系是：
                        // j 对应已知角，j 对边 sd[j] 也是已知；
                        // k 是与已知角相邻的另一条已知边；
                        // i 是待求的第三边。
                        int adjacent_known_side_index = 3 - missing_side_index - known_angle_index;
                        // height_from_known_angle = 已知边[k] * sin(已知角[j])，
                        // 它对应从已知角向对边作高时得到的“高”的长度。
                        double height_from_known_angle = sides[adjacent_known_side_index] * sin(angles[known_angle_index]);
                        if (eq(sides[known_angle_index], height_from_known_angle))
                        {
                            // 恰好等于高，说明构成直角三角形，解唯一。
                            sides[missing_side_index] = sqrt(max(0.0, sides[adjacent_known_side_index] * sides[adjacent_known_side_index] - sides[known_angle_index] * sides[known_angle_index]));
                        }
                        else if (sides[known_angle_index] < height_from_known_angle)
                            // 已知对边比高还短，连三角形都搭不出来。
                            throw 1;
                        else if (sides[known_angle_index] < sides[adjacent_known_side_index])
                            // 对边长介于高和邻边之间时，会出现经典的 SSA 两解情形。
                            throw 2;
                        else
                            // 只剩唯一解时，按几何关系求出第三边。
                            // 这里等价于先求投影，再补上剩余那一段。
                            sides[missing_side_index] = sides[adjacent_known_side_index] * cos(angles[known_angle_index]) + sqrt(max(0.0, sides[adjacent_known_side_index] * sides[adjacent_known_side_index] * (cos(angles[known_angle_index]) * cos(angles[known_angle_index]) - 1) + sides[known_angle_index] * sides[known_angle_index]));
                    }
                    // 进入这里后，三条边都已经凑齐，后面就能统一按 SSS 回推角。
                    known_side_count = 3;
                }
                // 三边已知后，使用余弦定理反推三个角。
                if (known_side_count == 3)
                {
                    double side_sum = sides[0] + sides[1] + sides[2];
                    // 先做三角形存在性判断：任意一边都必须小于另外两边之和。
                    for (int side_index = 0; side_index < 3; ++side_index)
                        if (sides[side_index] * 2 >= side_sum)
                            throw 1;
                    for (int i = 0; i < 3; ++i)
                    {
                        int j = (i + 1) % 3, k = (i + 2) % 3;
                        // 余弦定理：
                        // cos(A_i) = (b^2 + c^2 - a^2) / (2bc)
                        double cosine_value = (sides[j] * sides[j] + sides[k] * sides[k] - sides[i] * sides[i]) / (2 * sides[j] * sides[k]);
                        // 浮点误差可能把值抖到 [-1,1] 外一点点，先钳回合法范围再 acos。
                        if (cosine_value < -1.0)
                            cosine_value = -1.0;
                        if (cosine_value > 1.0)
                            cosine_value = 1.0;
                        double calculated_angle = acos(cosine_value);
                        // 如果这个角原本未知，就直接补上；
                        // 如果原本已知，就检查它是否和三边推出来的结果一致。
                        if (angles[i] == -1)
                            angles[i] = calculated_angle;
                        if (!eq(angles[i], calculated_angle))
                            throw 1;
                    }
                }
            }
            catch (int e)
            {
                // e == 1 表示输入矛盾或根本不能构成三角形；
                // e == 2 表示出现两组合法解，无法唯一确定。
                if (e == 1)
                    cout << "Invalid input.\n";
                else
                    cout << "More than one solution.\n";
                continue;
            }
            // 统一输出三组“边 + 对角”，保留 6 位小数。
            cout << fixed << setprecision(6) << sides[0] << " " << angles[0] << " " << sides[1] << " " << angles[1] << " " << sides[2] << " " << angles[2] << "\n";
        }
    }
    return 0;
}
