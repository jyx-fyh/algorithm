
// 动态规划求解并输出所有LCS
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

struct Info {
    vector<int> coins;
    vector<int> zhangs;

    Info(const vector<int>& c, const vector<int>& z) : coins(c), zhangs(z) {}
};

Info getInfo(const vector<int>& arr) {
    unordered_map<int, int> counts;
    for (int value : arr) {
        if (counts.find(value) == counts.end()) {
            counts[value] = 1;
        } else {
            counts[value]++;
        }
    }

    int N = counts.size();
    vector<int> coins(N);
    vector<int> zhangs(N);
    int index = 0;
    for (const auto& entry : counts) {
        coins[index] = entry.first;
        zhangs[index++] = entry.second;
    }

    return Info(coins, zhangs);
}

int process(const vector<int>& coins, const vector<int>& zhangs, int index, int rest) {
    if (index == coins.size()) {
        return rest == 0 ? 1 : 0;
    }

    int ways = 0;
    for (int zhang = 0; zhang * coins[index] <= rest && zhang <= zhangs[index]; zhang++) {
        ways += process(coins, zhangs, index + 1, rest - (zhang * coins[index]));
    }

    return ways;
}
int coinsWay(const vector<int>& arr, int aim) {
    if (arr.empty() || aim < 0) {
        return 0;
    }

    Info info = getInfo(arr);
    return process(info.coins, info.zhangs, 0, aim);
}



int main() {
    vector<int> arr = {1,2,1,1,2,1,2,2,3,3,3,3,4,5,5,5,6,6,7,7,8,9};
    int aim = 20;
    cout << coinsWay(arr, aim) << endl;
    return 0;
}