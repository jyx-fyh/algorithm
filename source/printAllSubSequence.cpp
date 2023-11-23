//
// Created by ButcherX on 23-11-18.
//
#include<string>
#include<iostream>
using std::string;

// 什么是字符串的子序列：字符串的一个子序列是原始字符串删除
// 一些（也可以不删除）字符而不改变剩余字符相对位置形成的新字符串。
// （例如，"ace"是"abcde"的一个子序列，而"aec"不是）

void process(const string &str, string path, int index, bool print)
{
    if(index == str.size())
        return;
    if(print)
    {
        path += str[index];
        //如果要打印非重复子序列,加入set去重即可
        //if(set.find(path) == set.end())
        std::cout << path << std::endl;
        //set.emplace(path);
    }
    process(str, path, index + 1, false);
    process(str, path, index + 1, true);
}

void printAllSubSequence(string str)
{
    string path;
    process(str, path, 0, false);
    process(str, path, 0, true);
}

int main()
{
    string str = "1234";
    printAllSubSequence(str);
}


