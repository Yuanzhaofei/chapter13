//����ʱ����������Ԥ������(��Ŀ����----C/C++----Ԥ����----Ԥ����������)��_SCL_SECURE_NO_WARNINGS���Խ��
#include"StrVec.h"
#include<memory>
using namespace std;
//����Ԫ������
size_t StrVec::size() const {
	if (elements != nullptr)
		return first_free - elements;
	else
		return 0;
}
//���ص�ǰ����
size_t StrVec::capacity() const {
	if (elements != nullptr)
		return cap - elements;
	else
		return 0;
}
//β������Ԫ��
void StrVec::push_back(const string &s) {
	chk_n_alloc();
	//������飬��ʱ�����㹻�ռ�������Ԫ��
	alloc.construct(first_free++, s);
}
//�������ڴ�󿽱�Ԫ��
pair<string*, string*> StrVec::alloc_n_copy(const string *b, const string *e) {
	auto data = alloc.allocate(e - b);
	return { data, uninitialized_copy(b,e,data) };//�������ڴ���Ԫ�ص���λ�ú�β��λ��
}
//����Ԫ�ز��ͷ�ԭ���ڴ�
void StrVec::free() {
	if (elements) {
		//Ҫ���ͷ��ڴ�ռ�Ķ������ǿ�
		for (auto p = first_free; p != elements;/*Ϊ��*/)
			alloc.destroy(--p);//��������
	}
	alloc.deallocate(elements, cap - elements);//�ͷ��ڴ�
}
//����string�б���ʼ�����Ĺ��캯��
StrVec::StrVec(initializer_list<string> iniList) {
	auto newData = alloc_n_copy(iniList.begin(), iniList.end());
	elements = newData.first;
	cap = first_free = newData.second;
}
//�������캯��
StrVec::StrVec(const StrVec &sv) {
	//����alloc_n_copy�����������ڴ棬����������
	auto newData = alloc_n_copy(sv.elements, sv.first_free);
	elements = newData.first;
	cap = first_free = newData.second;
}
//������ֵ�����
StrVec& StrVec::operator=(const StrVec &rsv) {
	auto currData = alloc_n_copy(rsv.elements, rsv.first_free);
	free();
	elements = currData.first;
	cap = first_free = currData.second;
	return *this;
}
//���·����ڴ�
void StrVec::reallocate() {
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
void StrVec::reserve(size_t n) {
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
void StrVec::resize(size_t n, const string &s) {
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
allocator<string> StrVec::alloc;//���ڷ���Ԫ�ص�alloctor����