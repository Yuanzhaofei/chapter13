#pragma once
#pragma once
#ifndef TEXTQUERY_H
#define TEXTQUERY_H
#include<string>
#include<vector>
#include<map>
#include<set>
#include<memory>
#include<iostream>
#include"StrVec.h"
using namespace std;


class QueryResult;//查询结果

//TextQuery类，保存输入文件，并将单词和出现的行整理到map中，便于查询
class TextQuery {
public:
	using line_no = vector<string>::size_type;//行数类型
	//构造函数定义
	TextQuery(ifstream & infile);//利用输入流构造
	QueryResult query(const string&)const;//输入单词，进行查询，定义成常量成员函数，因为两个指针数据成员都不能被改变
private:
	shared_ptr<StrVec> file;//保存输入文件，与输出结果类共享，因为输出结果需要打印单词所在行
	map<string, shared_ptr<set<line_no>>> wm;//保存查询单词及行号，行号需要拷贝给输出结果类，所以使用动态内存保存
};

//定义输入结果类，由TextQuery的查询函数query返回，包含输出查询结果需要的所有元素
class QueryResult {
	friend ostream &print(ostream &os, const QueryResult & qr);//打印结果函数的友元声明
public:
	using line_no = vector<string>::size_type;//行数类型
	QueryResult(string s, shared_ptr<set<line_no>> l, shared_ptr<StrVec> f) :sought(s), lines(l),file(f){}
	set<line_no>::iterator begin() { return lines->begin(); }//返回set首位置迭代器
	set<line_no>::const_iterator begin() const{ return lines->begin(); }//返回set首位置迭代器
	set<line_no>::iterator end() { return lines->end(); }//返回set首位置迭代器
	set<line_no>::const_iterator end()const { return lines->end(); }//返回set首位置迭代器
	shared_ptr<StrVec> get_file() { return file; }//返回指向输入文件的智能指针
	const shared_ptr<StrVec> get_file()const { return file; }
private:
	string sought;//查询的单词
	shared_ptr<set<line_no>> lines;//指向行号的shared_ptr
	shared_ptr<StrVec> file;//指向输入文件的shared_ptr
};
#endif // !TEXTQUERY_H
