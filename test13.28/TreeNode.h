#pragma once
#ifndef TREENODE_H
#define TREENODE_H
#include<string>
using namespace std;
//定义一个TreeNode类，对象包含一个string，一个int，和两个指向左右对象的指针
class TreeNode {
private:
	string value;
	int count;
	TreeNode *left;
	TreeNode *right;
};
#endif // !TREENODE_H
