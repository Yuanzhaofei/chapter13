#include "HasPtr.h"
//�������캯��
HasPtr::HasPtr(const HasPtr &hp) :
	ps(hp.ps),
	i(hp.i),
	rcnt(hp.rcnt)
{
	++*rcnt;//���ü�����1
}
//������ֵ�����
HasPtr&HasPtr::operator=(const HasPtr &hp) {
	++*hp.rcnt;//�ұ����ü�����1
	if (--*rcnt == 0) {//��߶������ü�����1
		delete ps;//��Ҫ�ͷž��ڴ棡����
		delete rcnt;
	}		
	ps = hp.ps;
	i = hp.i;
	rcnt = hp.rcnt;
	return *this;
}

HasPtr::~HasPtr(){
	if (--*rcnt == 0) {//��߶������ü�����1
		delete ps;//��Ҫ�ͷž��ڴ棡����
		delete rcnt;
	}
}
