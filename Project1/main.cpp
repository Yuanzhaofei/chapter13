//定义简单类，理解拷贝构造函数，拷贝赋值运算符和析构函数的调用
#include"X.h"
#include<memory>
#include<vector>
using namespace std;
X copyX(const X x) { return x; }
int main() {
	{
	X x1, x2;//默认构造函数
	X x3(x1), x4 = x2;//拷贝构造，拷贝构造
	cout << endl;
	x4 = copyX(x2);//右侧临时对象会调用析构函数
	cout << endl;
	X x5[2] = {};
	cout << endl;
	x5[0] = x1;//拷贝赋值
	cout << endl;
	X *xp = new X();
	cout << endl;
	delete xp;
	cout << endl;
	auto xsp1(make_shared<X>()), xsp2 = (make_shared<X>()), xsp3(xsp1);
	cout << endl;
	xsp2.reset();
	cout << endl;
	vector<X> xv;
	cout << endl;
	xv.push_back(x1);
	cout << endl;
}
	system("pause");
	return 0;
}