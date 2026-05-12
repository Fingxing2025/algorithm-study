#include <iostream>
using namespace std;

// 1. 定义常量和全局数组
const int MAXN = 100005;     // 根据题目要求的最大 N 进行修改
long long A[MAXN];           // 存原数组数据
long long tree[MAXN * 4];    // 线段树数组（必须开 4 倍大小！）
long long mark[MAXN * 4];    // 懒标记数组（必须开 4 倍大小！）

// 2. 下传懒标记 (PushDown)
// 将节点 p 的懒标记传递给左右子节点
void push_down(int p, int l, int r) {
    if (mark[p] != 0) { // 如果有标记才下传
        int mid = (l + r) / 2;
        
        // 传递给左孩子 (p * 2)
        mark[p * 2] += mark[p];
        tree[p * 2] += mark[p] * (mid - l + 1); // 左子树的值增加: 标记 * 左子树元素个数
        
        // 传递给右孩子 (p * 2 + 1)
        mark[p * 2 + 1] += mark[p];
        tree[p * 2 + 1] += mark[p] * (r - mid); // 右子树的值增加: 标记 * 右子树元素个数
        
        // 清空当前节点的标记
        mark[p] = 0;
    }
}

// 3. 建树 (Build)
// 初始化线段树，用法: build(1, 1, n);
void build(int p, int l, int r) {
    if (l == r) {
        tree[p] = A[l]; // 到达叶子节点，赋值
        return;
    }
    int mid = (l + r) / 2;
    build(p * 2, l, mid);          // 递归建立左子树
    build(p * 2 + 1, mid + 1, r);  // 递归建立右子树
    
    // PushUp: 向上更新父节点的值
    tree[p] = tree[p * 2] + tree[p * 2 + 1]; 
}

// 4. 区间修改 (Update)
// 将区间 [ql, qr] 内的每个数加上 v
// 用法: update(1, 1, n, ql, qr, v);
void update(int p, int l, int r, int ql, int qr, long long v) {
    // 情况1：当前区间被查询区间完全包含
    if (ql <= l && r <= qr) {
        tree[p] += v * (r - l + 1); // 更新当前节点的值
        mark[p] += v;               // 打上懒标记
        return;
    }
    
    // 情况2：不能完全包含，必须切分，先下传标记！
    push_down(p, l, r);
    
    int mid = (l + r) / 2;
    // 如果左半边有交集，修改左半边
    if (ql <= mid) update(p * 2, l, mid, ql, qr, v);
    // 如果右半边有交集，修改右半边
    if (qr > mid)  update(p * 2 + 1, mid + 1, r, ql, qr, v);
    
    // PushUp: 子节点修改完了，更新父节点
    tree[p] = tree[p * 2] + tree[p * 2 + 1];
}

// 5. 区间查询 (Query)
// 查询区间 [ql, qr] 的和
// 用法: query(1, 1, n, ql, qr);
long long query(int p, int l, int r, int ql, int qr) {
    // 情况1：当前区间被查询区间完全包含
    if (ql <= l && r <= qr) {
        return tree[p];
    }
    
    // 情况2：不能完全包含，先下传标记！
    push_down(p, l, r);
    
    int mid = (l + r) / 2;
    long long sum = 0;
    // 如果左半边有交集，去左边查
    if (ql <= mid) sum += query(p * 2, l, mid, ql, qr);
    // 如果右半边有交集，去右边查
    if (qr > mid)  sum += query(p * 2 + 1, mid + 1, r, ql, qr);
    
    return sum;
}

// ================= 主函数 =================
int main() {
    // 优化 C++ 的输入输出速度（竞赛必备）
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m; // n 是数组长度，m 是操作次数
    // 假设题目输入格式为：先输入 n 和 m
    if (!(cin >> n >> m)) return 0; 

    // 读取原数组，强烈建议从下标 1 开始存！
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
    }

    // 1. 建树：当前节点编号为1，代表的区间是 [1, n]
    build(1, 1, n);

    // 2. 处理 m 次操作
    while (m--) {
        int op, x, y;
        long long k;
        cin >> op; // 读取操作类型
        
        if (op == 1) {
            // 操作 1：区间修改（例如将 [x, y] 每个数加上 k）
            cin >> x >> y >> k;
            update(1, 1, n, x, y, k);
        } 
        else if (op == 2) {
            // 操作 2：区间查询（例如查询 [x, y] 的和）
            cin >> x >> y;
            cout << query(1, 1, n, x, y) << "\n"; // 输出要换行
        }
    }

    return 0;
}