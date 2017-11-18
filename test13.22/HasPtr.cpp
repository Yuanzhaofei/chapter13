#include "HasPtr.h"
//拷贝构造函数
HasPtr::HasPtr(const HasPtr &hp) :
	ps(hp.ps),
	i(hp.i),
	rcnt(hp.rcnt)
{
	++*rcnt;//引用计数加1
}
//拷贝赋值运算符
HasPtr&HasPtr::operator=(const HasPtr &hp) {
	++*hp.rcnt;//右边引用计数加1
	if (--*rcnt == 0) {//左边对象引用计数减1
		delete ps;//需要释放旧内存！！！
		delete rcnt;
	}		
	ps = hp.ps;
	i = hp.i;
	rcnt = hp.rcnt;
	return *this;
}

HasPtr::~HasPtr(){
	if (--*rcnt == 0) {//左边对象引用计数减1
		delete ps;//需要释放旧内存！！！
		delete rcnt;
	}
}
