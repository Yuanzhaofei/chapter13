#include "HasPtr.h"



HasPtr::HasPtr(const HasPtr &hp) :
	ps(new string(*hp.ps)),
	i(hp.i)
{
	//��
}
HasPtr&HasPtr::operator=(const HasPtr &hp) {
	auto newp = new string(*hp.ps);
	delete ps;//��Ҫ�ͷž��ڴ棡����
	ps = newp;
	i = hp.i;
	return *this;
}

HasPtr::~HasPtr()
{
	delete ps;
}
