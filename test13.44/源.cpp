#include"String.h"
#include<iostream>
#include<vector>
using namespace std;
int main() {
	//test13.47
	vector<String> vS;
	String myStr = "yuanzhaofei";
	//test14.7
	cout << myStr << endl;
	//调用push_back可能会引起vector的内存重新分配，
	//此时元素会从旧内存拷贝到新内存（因为String类没有定义移动构造函数）
	vS.push_back(myStr);
	vS.push_back(myStr);
	vS.push_back(myStr);
	vS.push_back(myStr);
	system("pause");
	return 0;
}