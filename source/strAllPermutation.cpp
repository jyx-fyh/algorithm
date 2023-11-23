//
// Created by ButcherX on 23-11-17.
//
#include<iostream>
#include<string>
#include<unordered_set>
using std::string;
using std::unordered_set;

//生成式
void process1(string str, int cur, string path, unordered_set<char> set)
{
    if(cur == str.size())
    {
        std::cout << path << std::endl;
        return;
    }
    for(int i = 0; i < str.size(); i++)
    {
        if(set.find(str[i]) == set.end())
        {
            set.emplace(str[i]);
            process1(str, cur + 1, path + str[i], set);
            set.erase(str[i]);//恢复现场，容易忽略
        }
    }
}

void printAllPermutation1(string str)
{
    unordered_set<char> set;
    string path = "";
    process1(str, 0, path, set);
}

//交换式-参数设计更好
void process2(string str, int index)
{
    if(index == str.size())
    {
        std::cout << str << std::endl;
        return;
    }
    for(int i = index; i < str.size(); i++)
    {
        std::swap(str[index], str[i]);
        process2(str, index + 1);
        std::swap(str[index], str[i]);
    }
}
void printAllpremutation2(string str)
{
    process2(str, 0);
}

int main()
{
    string str = "1234";
    printAllPermutation1(str);
    std::cout << "==========" << std::endl;
    printAllPermutation1(str);
}