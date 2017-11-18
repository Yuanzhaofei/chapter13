#ifndef HASPTR_H
#define HASPTR_H
#include<string>
using namespace std;
//������Ϊ��ָ�����HasPtrָ��һ��string
//��Ҫ���ü���
class HasPtr
{
public:
	HasPtr(const string & s = string()) :ps(new string(s)), i(0),rcnt(new size_t(1)) {}
	~HasPtr();
	HasPtr(const HasPtr &hp);
	HasPtr& operator=(const HasPtr &hp);
private:
	string *ps;//
	size_t *rcnt;//���ü���
	int i;
};
#endif // HASPTR_H



