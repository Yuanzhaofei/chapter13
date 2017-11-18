#pragma once
#include<string>
using namespace std;
class HasPtr
{
public:
	HasPtr(const string & s=string()):ps(new string(s)),i(0){}
	~HasPtr();
	HasPtr(const HasPtr &hp);
	HasPtr& operator=(const HasPtr &hp);
private:
	string *ps;
	int i;
};

