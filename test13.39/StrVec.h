#pragma once

//��Ʊ���string�Ķ�̬�ڴ�����࣬ʵ�ֳ��������иı�����С��
#ifndef STRVEC_H
#define STRVEC_H
#include<string>
#include<memory>
#include<utility>
using namespace std;
class StrVec {
public:
	StrVec():elements(nullptr),first_free(nullptr),cap(nullptr){}//Ĭ�Ϲ��캯��
	StrVec(initializer_list<string>);//����string�б��ʼ�����Ĺ��캯��
	StrVec(const StrVec &);//�������캯��
	StrVec(StrVec &&s) noexcept;//�ƶ����캯��
	StrVec& operator=(const StrVec &);//������ֵ�����
	StrVec& operator=(StrVec &&) noexcept;//�ƶ���ֵ�����
	~StrVec() { free(); };//��������
	void push_back(const string &);//β�����Ԫ�أ������汾��
	void push_back(string &&);//β�����Ԫ�أ��ƶ��汾��
	size_t size() const;//����Ԫ������
	size_t capacity() const; // ���ص�ǰ����
	string * begin()const { return elements; }//������Ԫ��ָ��
	string * end() const { return first_free; }//����β��Ԫ��ָ��
	void reserve(size_t n);//������������n��Ԫ�ص��ڴ�ռ�
	void resize(size_t n,const string & = string());//�ı�������С
private:
	static allocator<string> alloc;//���ڷ���Ԫ�ص�alloctor����
	//���Ԫ���Ƿ�ռ�������������Ԫ�صĺ���ʹ��
	void chk_n_alloc() {
		if (size() == capacity()) reallocate();
	}
	//���ߺ�����
	pair<string*, string*> alloc_n_copy(const string*,const string*);//�������ڴ�󿽱�Ԫ��
	void free();//����Ԫ�ز��ͷ�ԭ���ڴ�
	void reallocate();//���·����ڴ�
	string* elements;//ָ��������Ԫ��ָ��
	string* first_free;//ָ���һ������Ԫ�ص�ָ�룻
	string* cap;//ָ������β���ָ��
};

#endif // !STRVEC_H
