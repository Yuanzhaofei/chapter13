#include "HasPtr.h"



HasPtr::HasPtr(const HasPtr &hp) :
	ps(new string(*hp.ps)),
	i(hp.i)
{
	//空
}
HasPtr&HasPtr::operator=(const HasPtr &hp) {
	auto newp = new string(*hp.ps);
	delete ps;//需要释放旧内存！！！
	ps = newp;
	i = hp.i;
	return *this;
}

HasPtr::~HasPtr()
{
	delete ps;
}
