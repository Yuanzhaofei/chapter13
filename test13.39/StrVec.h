#pragma once

//设计保存string的动态内存管理类，实现程序运行中改变对象大小；
#ifndef STRVEC_H
#define STRVEC_H
#include<string>
#include<memory>
#include<utility>
using namespace std;
class StrVec {
public:
	StrVec():elements(nullptr),first_free(nullptr),cap(nullptr){}//默认构造函数
	StrVec(initializer_list<string>);//接受string列表初始化器的构造函数
	StrVec(const StrVec &);//拷贝构造函数
	StrVec(StrVec &&s) noexcept;//移动构造函数
	StrVec& operator=(const StrVec &);//拷贝赋值运算符
	StrVec& operator=(StrVec &&) noexcept;//移动赋值运算符
	~StrVec() { free(); };//析构函数
	void push_back(const string &);//尾部添加元素（拷贝版本）
	void push_back(string &&);//尾部添加元素（移动版本）
	size_t size() const;//返回元素数量
	size_t capacity() const; // 返回当前容量
	string * begin()const { return elements; }//返回首元素指针
	string * end() const { return first_free; }//返回尾后元素指针
	void reserve(size_t n);//分配至少容纳n个元素的内存空间
	void resize(size_t n,const string & = string());//改变容器大小
private:
	static allocator<string> alloc;//用于分配元素的alloctor对象
	//检查元素是否占满容量，被添加元素的函数使用
	void chk_n_alloc() {
		if (size() == capacity()) reallocate();
	}
	//工具函数，
	pair<string*, string*> alloc_n_copy(const string*,const string*);//分配新内存后拷贝元素
	void free();//销毁元素并释放原有内存
	void reallocate();//重新分配内存
	string* elements;//指向数组首元素指针
	string* first_free;//指向第一个空闲元素的指针；
	string* cap;//指向数组尾后的指针
};

#endif // !STRVEC_H
