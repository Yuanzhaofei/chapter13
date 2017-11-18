#ifndef HASPTR_H
#define HASPTR_H
#include<string>
using namespace std;
//定义行为像指针的类HasPtr指向一个string
//需要引用计数
class HasPtr
{
public:
	HasPtr(const string & s = string()) :ps(new string(s)), i(0),rcnt(new size_t(1)) {}
	~HasPtr();
	HasPtr(const HasPtr &hp);
	HasPtr& operator=(const HasPtr &hp);
private:
	string *ps;//
	size_t *rcnt;//引用计数
	int i;
};
#endif // HASPTR_H



