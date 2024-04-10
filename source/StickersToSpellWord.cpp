//
// Created by ButcherX on 23-11-23.
//
#include<chrono>
#include<string>
#include<vector>
#include<iostream>
#include<unordered_map>
#include<unordered_set>
#include<queue>
#include<algorithm>
using std::vector;
using std::priority_queue;
using std::string;
using std::unordered_map;

string minus(const string &sticker, string target)
{
    for (char c : sticker)
    {
        size_t pos = target.find(c);
        if (pos != string::npos)
            target.erase(pos, 1);
    }
    return target;
}
int process1(const vector<string> &stickers, string target, int index)
{
    if (target.empty())
        return 0;//找到一种选法
    if(index >= stickers.size())//不可置前
        return INT32_MAX; //说明此路径无法凑出target字符
    if(target == minus(stickers[index], target))//不可省略，否则栈溢出
        return process1(stickers, target, index + 1);
    int a = process1(stickers, target, index + 1);
    target = minus(stickers[index], target);
    int b = process1(stickers, target, index);
    return std::min(a, b == INT32_MAX ? INT32_MAX : b + 1);
}
int minStickerNum1(const vector<string> &stickers, string target)
{
    int ret = process1(stickers, target, 0);
    return ret == INT32_MAX ? -1 : ret;
}

///==========================================================================
//排序优化
int process2(const vector<string> &stickers, string target, int index)
{
    if (target.empty())
        return 0;//找到一种选法
    if(index >= stickers.size())//不可置前
        return INT32_MAX; //说明此路径无法凑出target字符
    if(target == minus(stickers[index], target))//不可省略，否则栈溢出
        return process2(stickers, target, index + 1);
    int a = process2(stickers, target, index + 1);
    target = minus(stickers[index], target);
    int b = process2(stickers, target, index);
    return std::min(a, b == INT32_MAX ? INT32_MAX : b + 1);
}

int containNum(const string &sticker, string target)
{
    int count = 0;
    for (char c : sticker)
    {
        size_t pos = target.find(c);
        if (pos != std::string::npos)
        {
            target.erase(pos, 1);
            count++;
        }
    }
    return count;
}

int minStickerNum2(vector<string> stickers, string target)
{
    std::sort(stickers.begin(), stickers.end(), [target](const string &a, const string &b){
        return containNum(a, target) > containNum(b, target);
    });
    int ret = process2(stickers, target, 0);
    return ret == INT32_MAX ? -1 : ret;
}
///===============================================================
//process2基础上的记忆化搜索
int process3(const vector<string> &stickers, string target, int index, unordered_map<string, int> &memo)
{
    if(memo.find(target+std::to_string(index)) != memo.end())
        return memo[target+std::to_string(index)];
    if (target.empty())
        return 0;//找到一种选法
    if(index >= stickers.size())//不可置前
        return INT32_MAX; //说明此路径无法凑出target字符
    if(target == minus(stickers[index], target))//不可省略，否则栈溢出
        return process3(stickers, target, index + 1, memo);
    int a = process3(stickers, target, index + 1, memo);
    string rest = minus(stickers[index], target);
    int b = process3(stickers, rest, index, memo);
    int min = std::min(a, b == INT32_MAX ? INT32_MAX : b + 1);
    memo.emplace(target + std::to_string(index), min);
    return min;
}

int minStickerNum3(vector<string> stickers, string target)
{
    std::sort(stickers.begin(), stickers.end(), [target](const string &a, const string &b){
        return containNum(a, target) > containNum(b, target);
    });
    unordered_map<string, int> memo;
    int ret = process3(stickers, target, 0, memo);
    return ret == INT32_MAX ? -1 : ret;
}
///================================================================
int process4(std::vector<std::string>& stickers, std::string target, unordered_map<string, int> &memo)
{
    if(memo.find(target) != memo.end())
        return memo[target];
    if (target.empty())
        return 0;
    int min = INT32_MAX;
    for(string s : stickers)
    {
        string rest = minus(s, target);
        if(rest == target)
            continue;

        int ret = process4(stickers, rest, memo);
        min = min < ret ? min : ret;
    }
    min = min == INT32_MAX ? INT32_MAX : min + 1;
    memo.emplace(target, min);
    return min;
}
int minStickerNum4(std::vector<std::string>& stickers, std::string target)
{
    unordered_map<string, int> memo;
    int ans = process4(stickers, target, memo);
    return ans == INT32_MAX ? -1 : ans;
}
///========================================================================
//另一种递归遍历，剪枝
int process5(std::vector<std::string>& stickers, std::string target, unordered_map<std::string, int> &memo)
{
    if(memo.find(target) != memo.end())
        return memo[target];
    if (target.length() == 0)
        return 0;
    int min = INT32_MAX;
    for (string s : stickers)
    {
        if(s.find(target[0]) == string::npos)
            continue;
        string rest = minus(s, target);
        if (rest != target)
            min = std::min(min, process5(stickers, rest, memo));
    }
    memo.emplace(target, min + (min == INT32_MAX ? 0 : 1));
    return min + (min == INT32_MAX ? 0 : 1);
}

int minStickerNum5(std::vector<std::string>& stickers, std::string target)
{
    unordered_map<std::string, int> memo;
    int ans = process5(stickers, target, memo);
    return ans == INT32_MAX ? -1 : ans;
}
///================================================================



///===============================================================


int main()
{                             //  2       2       3       4       3
    vector<string> stickers = {"sail","just","point","over","hard","share","say","distant","proper","occur","before","whose","guess","lead","prove","pattern","six","fat","add","music","grand","show","final","hope","listen","week","picture","buy","run","though","between","serve","here","nation","forward","stick","decide","post","ear","than","he","word","would","band","many","well","gun","wish","toward","think"};

    auto start1 = std::chrono::high_resolution_clock::now();
    int ret1 = minStickerNum5(stickers, "governgreat");
    std::cout<< ret1 << std::endl;
    auto end1 = std::chrono::high_resolution_clock::now();
    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end1 - start1);

    auto start2 = std::chrono::high_resolution_clock::now();
    int ret2 = minStickerNum4(stickers, "governgreat");
    std::cout<< ret2 << std::endl;
    auto end2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end2 - start2);

//    auto start3 = std::chrono::high_resolution_clock::now();
//    int ret3 = minStickerNum4(stickers, "overfresh");
//    std::cout<< ret3 << std::endl;
//    auto end3 = std::chrono::high_resolution_clock::now();
//    auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(end3 - start3);

    // 输出运行时间
    std::cout << "非排序版本运行时间: " << duration1.count() << " 微秒" << std::endl;
    std::cout << "排序版本的运行时间: " << duration2.count() << " 微秒" << std::endl;
//    std::cout << "记忆化搜索运行时间: " << duration3.count() << " 微秒" << std::endl;
}