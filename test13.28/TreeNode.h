#pragma once
#ifndef TREENODE_H
#define TREENODE_H
#include<string>
using namespace std;
//����һ��TreeNode�࣬�������һ��string��һ��int��������ָ�����Ҷ����ָ��
class TreeNode {
private:
	string value;
	int count;
	TreeNode *left;
	TreeNode *right;
};
#endif // !TREENODE_H
