//编译时报错，加入预处理器(项目属性----C/C++----预处理----预处理器定义)：_SCL_SECURE_NO_WARNINGS可以解决
#include"String.h"
#include<memory>
#include<algorithm>
#include<iterator>
#include<cstring>
#include<iostream>
using namespace std;
//返回元素数量
size_t String::size() const {
		return first_free - elements;
}
//返回当前容量
size_t String::capacity() const {
	return cap - elements;
}
//尾部添加元素
void String::push_back(const char &s) {
	chk_n_alloc();
	//经过检查，此时必有足够空间添加新元素
	alloc.construct(first_free++, s);
}
//分配新内存,后拷贝元素
pair<char*, char*> String::alloc_n_copy(const char *b, const char *e) {
	auto data = alloc.allocate(e - b);
	return { data, uninitialized_copy(b,e,data) };//返回新内存中元素的首位置和尾后位置
}
//销毁元素并释放原有内存
void String::free() {
	if (elements) {
		//要求释放内存空间的对象不能是空
		for_each(elements, first_free, [](const char s) {alloc.destroy(&s); });
		//for (auto p = first_free; p != elements;/*为空*/)
		//	alloc.destroy(--p);//析构对象
	}
	alloc.deallocate(elements, cap - elements);//释放内存
}
//接受C风格字符串指针的构造函数
String::String(const char *c) {
	auto newData = alloc_n_copy(c, c+strlen(c));//这里没有检查c是否为c风格字符串，需要用户自行注意
	elements = newData.first;
	cap = first_free = newData.second;
}

//接受char列表初始化器的构造函数
String::String(initializer_list<char> iniList) {
	auto newData = alloc_n_copy(iniList.begin(), iniList.end());
	elements = newData.first;
	cap = first_free = newData.second;
}
//拷贝构造函数
String::String(const String &sv) {
	//调用alloc_n_copy函数分配新内存，并拷贝函数
	auto newData = alloc_n_copy(sv.elements, sv.first_free);
	elements = newData.first;
	cap = first_free = newData.second;
	cout << "调用了拷贝构造函数。" << endl;
}
//移动构造函数
String::String(String &&s) noexcept :elements(s.elements), first_free(s.first_free), cap(s.cap) {
	s.elements = s.first_free = s.cap = nullptr;//确保销毁s时不释放已经转移控制权的内存
	cout << "调用了移动构造函数。" << endl;
}
//拷贝赋值运算符
String& String::operator=(const String &rsv) {
	auto currData = alloc_n_copy(rsv.elements, rsv.first_free);
	free();
	elements = currData.first;
	cap = first_free = currData.second;
	cout << "调用了拷贝赋值运算符。" << endl;
	return *this;
}
//移动赋值运算符，必须正确处理自赋值
String& String::operator=(String &&rsv) noexcept {
	if (this != &rsv) {
		//比较左右对象是否为同一个对象，应该比较它们的地址是否相同
		free();
		elements = rsv.elements;
		first_free = rsv.first_free;
		cap = rsv.cap;
		rsv.elements = rsv.first_free = rsv.cap = nullptr;
	}
	cout << "调用了移动赋值运算符。" << endl;
	return *this;
}
//重新分配内存
void String::reallocate() {
	reserve(2 * (capacity() + 1));
	//auto newdata = alloc.allocate(2 * (capacity()+1));//分配两倍的新内存空间
	////将数据从就内存移动到新内存，不直接拷贝！！！
	//auto dest = newdata;
	//auto elem = elements;
	//for (size_t i = 0; i != size(); ++i) {
	//	alloc.construct(dest++, std::move(*elem++));
	//}
	//free();
	//elements = newdata;
	//first_free = dest;
	//cap = elements + 2 * (capacity() + 1);
}
//分配至少容纳n个元素的内存空间，只有n大于当前容量时，才会分配新的内存
void String::reserve(size_t n) {
	if (n > capacity()) {
		auto newData = alloc.allocate(n);//分配新内存空间
		//将数据从就内存移动到新内存，不直接拷贝！！！
		//auto dest = newData;
		//auto elem = elements;
		//for (size_t i = 0; i != size(); ++i) {
		//	alloc.construct(dest++, std::move(*elem++));
		//}
		auto dest = uninitialized_copy(make_move_iterator(begin()), make_move_iterator(end()), newData);
		free();
		elements = newData;
		first_free = dest;
		cap = elements + n;
	}
}
//改变容器大小
void String::resize(size_t n, const char &s) {
	//n小于size()时，丢弃多出的元素(使用destroy函数）
	if (n < size()) {		
		for (auto beg = elements + n; beg != first_free;/*空*/) {
			alloc.destroy(beg++);//将多出部分元素析构掉
		}
	}
	//n大于size()，需要创建新的元素
	else {
		reserve(n);//首先分配内存
		for (auto beg = first_free; beg != elements + n;) {
			alloc.construct(beg, s);
		}
	}
}
allocator<char> String::alloc;//用于分配元素的alloctor对象

//为String类定义输出运算符
ostream& operator<<(ostream&os, const String &s) {
	for_each(s.elements, s.first_free, [&os](const char &c) {os << c; });
	return os;
}