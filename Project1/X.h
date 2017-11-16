#pragma once
//定义简单类，理解拷贝构造函数，拷贝赋值运算符和析构函数的调用
#ifndef X_H
#define X_H
#include<iostream>
using namespace std;
struct X {
	X() { cout << "默认构造函数：X()" << endl; }//默认构造函数
	X(const X &x) { cout << "拷贝构造函数：X(const X&)" << endl; }//拷贝构造函数
	X& operator=(const X&) { cout << "拷贝赋值运算符：X& operator=(const X&)" << endl; return *this; }
	~X() { cout << "析构函数：~X()" << endl; }
};
#endif // !X_H
