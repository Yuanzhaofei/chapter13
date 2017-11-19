#pragma once

//设计string类的简化版本String
#ifndef STRING_H
#define STRING_H
#include<string>
#include<memory>
#include<utility>
using namespace std;
class String {
public:
	String():elements(nullptr),first_free(nullptr),cap(nullptr){}//默认构造函数
	String(const char *);//接受C风格字符串指针的构造函数
	String(initializer_list<char>);//接受char列表初始化器的构造函数
	String(const String &);//拷贝构造函数
	String& operator=(const String &);//拷贝赋值运算符
	~String() { free(); };//析构函数
	void push_back(const char &);//尾部添加元素
	size_t size() const;//返回元素数量
	size_t capacity() const; // 返回当前容量
	char * begin()const { return elements; }//返回首元素指针
	char * end() const { return first_free; }//返回尾后元素指针
	void reserve(size_t n);//分配至少容纳n个元素的内存空间
	void resize(size_t n,const char & = char());//改变容器大小
private:
	static allocator<char> alloc;//用于分配元素的alloctor对象
	//检查元素是否占满容量，被添加元素的函数使用
	void chk_n_alloc() {
		if (size() == capacity()) reallocate();
	}
	//工具函数，
	pair<char*, char*> alloc_n_copy(const char*,const char*);//分配新内存后拷贝元素
	void free();//销毁元素并释放原有内存
	void reallocate();//重新分配内存
	char* elements;//指向数组首元素指针
	char* first_free;//指向第一个空闲元素的指针；
	char* cap;//指向数组尾后的指针
};

#endif // !STRING_H
