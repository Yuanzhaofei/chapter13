//����ʱ��������Ԥ������(��Ŀ����----C/C++----Ԥ����----Ԥ����������)��_SCL_SECURE_NO_WARNINGS���Խ��
#include"String.h"
#include<memory>
#include<algorithm>
#include<iterator>
#include<cstring>
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
}
//������ֵ�����
String& String::operator=(const String &rsv) {
	auto currData = alloc_n_copy(rsv.elements, rsv.first_free);
	free();
	elements = currData.first;
	cap = first_free = currData.second;
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
		auto dest = newData;
		auto elem = elements;
		for (size_t i = 0; i != size(); ++i) {
			alloc.construct(dest++, std::move(*elem++));
		}
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