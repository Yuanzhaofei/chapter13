#pragma once

//���string��ļ򻯰汾String
#ifndef STRING_H
#define STRING_H
#include<string>
#include<memory>
#include<utility>
using namespace std;
class String {
public:
	String():elements(nullptr),first_free(nullptr),cap(nullptr){}//Ĭ�Ϲ��캯��
	String(const char *);//����C����ַ���ָ��Ĺ��캯��
	String(initializer_list<char>);//����char�б��ʼ�����Ĺ��캯��
	String(const String &);//�������캯��
	String& operator=(const String &);//������ֵ�����
	~String() { free(); };//��������
	void push_back(const char &);//β�����Ԫ��
	size_t size() const;//����Ԫ������
	size_t capacity() const; // ���ص�ǰ����
	char * begin()const { return elements; }//������Ԫ��ָ��
	char * end() const { return first_free; }//����β��Ԫ��ָ��
	void reserve(size_t n);//������������n��Ԫ�ص��ڴ�ռ�
	void resize(size_t n,const char & = char());//�ı�������С
private:
	static allocator<char> alloc;//���ڷ���Ԫ�ص�alloctor����
	//���Ԫ���Ƿ�ռ�������������Ԫ�صĺ���ʹ��
	void chk_n_alloc() {
		if (size() == capacity()) reallocate();
	}
	//���ߺ�����
	pair<char*, char*> alloc_n_copy(const char*,const char*);//�������ڴ�󿽱�Ԫ��
	void free();//����Ԫ�ز��ͷ�ԭ���ڴ�
	void reallocate();//���·����ڴ�
	char* elements;//ָ��������Ԫ��ָ��
	char* first_free;//ָ���һ������Ԫ�ص�ָ�룻
	char* cap;//ָ������β���ָ��
};

#endif // !STRING_H
