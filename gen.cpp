#include <iostream>
#include <vector>
#include <random>
#include <chrono>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n = 30;              // 数据规模，可自行修改
    int maxw = 60000;       // 点权范围，可自行修改

    std::cout << n << "\n";

    // 随机数引擎（C++17）
    std::mt19937_64 rng(
        std::chrono::steady_clock::now().time_since_epoch().count()
    );

    std::uniform_int_distribution<long long> distW(1, maxw);

    // 输出点权
    for (int i = 1; i <= n; i++) {
        std::cout << distW(rng);
        if (i != n) std::cout << " ";
    }
    std::cout << "\n";

    // 生成随机树：每个节点随机连到前面的某个节点
    for (int i = 2; i <= n; i++) {
        int p = rng() % (i - 1) + 1;
        std::cout << p << " " << i << "\n";
    }

    return 0;
}
