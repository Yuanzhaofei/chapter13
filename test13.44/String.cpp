//����ʱ��������Ԥ������(��Ŀ����----C/C++----Ԥ����----Ԥ����������)��_SCL_SECURE_NO_WARNINGS���Խ��
#include"String.h"
#include<memory>
#include<algorithm>
#include<iterator>
#include<cstring>
#include<iostream>
using namespace std;
//����Ԫ������
size_t String::size() const {
		return first_free - elements;
}
//���ص�ǰ����
size_t String::capacity() const {
	return cap - elements;
}
//β�����Ԫ��
void String::push_back(const char &s) {
	chk_n_alloc();
	//������飬��ʱ�����㹻�ռ������Ԫ��
	alloc.construct(first_free++, s);
}
//�������ڴ�,�󿽱�Ԫ��
pair<char*, char*> String::alloc_n_copy(const char *b, const char *e) {
	auto data = alloc.allocate(e - b);
	return { data, uninitialized_copy(b,e,data) };//�������ڴ���Ԫ�ص���λ�ú�β��λ��
}
//����Ԫ�ز��ͷ�ԭ���ڴ�
void String::free() {
	if (elements) {
		//Ҫ���ͷ��ڴ�ռ�Ķ������ǿ�
		for_each(elements, first_free, [](const char s) {alloc.destroy(&s); });
		//for (auto p = first_free; p != elements;/*Ϊ��*/)
		//	alloc.destroy(--p);//��������
	}
	alloc.deallocate(elements, cap - elements);//�ͷ��ڴ�
}
//����C����ַ���ָ��Ĺ��캯��
String::String(const char *c) {
	auto newData = alloc_n_copy(c, c+strlen(c));//����û�м��c�Ƿ�Ϊc����ַ�������Ҫ�û�����ע��
	elements = newData.first;
	cap = first_free = newData.second;
}

//����char�б��ʼ�����Ĺ��캯��
String::String(initializer_list<char> iniList) {
	auto newData = alloc_n_copy(iniList.begin(), iniList.end());
	elements = newData.first;
	cap = first_free = newData.second;
}
//�������캯��
String::String(const String &sv) {
	//����alloc_n_copy�����������ڴ棬����������
	auto newData = alloc_n_copy(sv.elements, sv.first_free);
	elements = newData.first;
	cap = first_free = newData.second;
	cout << "�����˿������캯����" << endl;
}
//�ƶ����캯��
String::String(String &&s) noexcept :elements(s.elements), first_free(s.first_free), cap(s.cap) {
	s.elements = s.first_free = s.cap = nullptr;//ȷ������sʱ���ͷ��Ѿ�ת�ƿ���Ȩ���ڴ�
	cout << "�������ƶ����캯����" << endl;
}
//������ֵ�����
String& String::operator=(const String &rsv) {
	auto currData = alloc_n_copy(rsv.elements, rsv.first_free);
	free();
	elements = currData.first;
	cap = first_free = currData.second;
	cout << "�����˿�����ֵ�������" << endl;
	return *this;
}
//�ƶ���ֵ�������������ȷ�����Ը�ֵ
String& String::operator=(String &&rsv) noexcept {
	if (this != &rsv) {
		//�Ƚ����Ҷ����Ƿ�Ϊͬһ������Ӧ�ñȽ����ǵĵ�ַ�Ƿ���ͬ
		free();
		elements = rsv.elements;
		first_free = rsv.first_free;
		cap = rsv.cap;
		rsv.elements = rsv.first_free = rsv.cap = nullptr;
	}
	cout << "�������ƶ���ֵ�������" << endl;
	return *this;
}
//���·����ڴ�
void String::reallocate() {
	reserve(2 * (capacity() + 1));
	//auto newdata = alloc.allocate(2 * (capacity()+1));//�������������ڴ�ռ�
	////�����ݴӾ��ڴ��ƶ������ڴ棬��ֱ�ӿ���������
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
//������������n��Ԫ�ص��ڴ�ռ䣬ֻ��n���ڵ�ǰ����ʱ���Ż�����µ��ڴ�
void String::reserve(size_t n) {
	if (n > capacity()) {
		auto newData = alloc.allocate(n);//�������ڴ�ռ�
		//�����ݴӾ��ڴ��ƶ������ڴ棬��ֱ�ӿ���������
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
//�ı�������С
void String::resize(size_t n, const char &s) {
	//nС��size()ʱ�����������Ԫ��(ʹ��destroy������
	if (n < size()) {		
		for (auto beg = elements + n; beg != first_free;/*��*/) {
			alloc.destroy(beg++);//���������Ԫ��������
		}
	}
	//n����size()����Ҫ�����µ�Ԫ��
	else {
		reserve(n);//���ȷ����ڴ�
		for (auto beg = first_free; beg != elements + n;) {
			alloc.construct(beg, s);
		}
	}
}
allocator<char> String::alloc;//���ڷ���Ԫ�ص�alloctor����

//ΪString�ඨ����������
ostream& operator<<(ostream&os, const String &s) {
	for_each(s.elements, s.first_free, [&os](const char &c) {os << c; });
	return os;
}