#include<iostream>
#include<string>
using std::string;
using std::cout;
using std::endl;
struct TreeNode
{
	int pass;
	int end;
	TreeNode* nexts[26];
	TreeNode(): pass(0), end(0)
	{
		for(int i = 0; i < 26; i++)
			nexts[i] = nullptr;
	}
};


class trieTree
{
private:
	TreeNode* root;
public:
	trieTree(){root = new TreeNode;}
	void insert(string str);
	int search(string str);
	int prefixSearch(string str);
	int delstr(string str, int times);
};

void trieTree::insert(string str)
{
	if(str.size() == 0)
		return;
	int n;
	TreeNode* tmp = root;
	for(int i = 0; i < str.size(); i++)
	{
		n = str[i] - 'a';
		if(tmp->nexts[n] == nullptr)
			tmp->nexts[n] = new TreeNode;
		tmp = tmp->nexts[n];
		tmp->pass++;
	}
	if(tmp->end == 0)
		root->end++;
	tmp->end++;
	root->pass++;
};

int trieTree::search(string str)
{
	if(str.size() == 0)//!!!
		return 0;
	TreeNode* tmp = root;
	int i = 0;
	int n;
	for(i = 0; i < str.size(); i++)
	{
		n = str[i] - 'a';
		if(tmp->nexts[n] == nullptr)
			return 0;
		tmp = tmp->nexts[n];
	}
	return tmp->end;
}


int trieTree::prefixSearch(string str)
{
	if(str.size() == 0)//!!!
		return 0;
	TreeNode* tmp = root;
	int i = 0;
	int n;
	for(i = 0; i < str.size(); i++)
	{
		n = str[i] - 'a';
		if(tmp->nexts[n] == nullptr)
			return 0;
		tmp = tmp->nexts[n];
	}
	return tmp->pass;
}

int trieTree::delstr(string str, int times)
{
	int counts = this->search(str);
	if(counts == 0)
		return 0;
	int t = times == 0 ? counts : (times < counts ? times : counts);
	TreeNode* tmp = root;
	int n;
	for(int i = 0; i < str.size(); i++)
	{
		n = str[i] - 'a';
		tmp = tmp->nexts[n];
		tmp->pass -= t;
	}
	tmp->end -= t;
	if(t != counts)
		return t;
	for(int i = 0; i < str.size(); i++)
	{
		int k = 0;
		tmp = root;
		for(; k < str.size()-1-i; k++)
		{
			n = str[k] - 'a';
			tmp = tmp->nexts[n];
		}
		n = str[k] - 'a';
		if(tmp->nexts[n]->pass == 0)
		{
			delete tmp->nexts[n];
			tmp->nexts[n] = nullptr;
		}
	}
	return counts;

}


