#pragma once
//������࣬��⿽�����캯����������ֵ����������������ĵ���
#ifndef X_H
#define X_H
#include<iostream>
using namespace std;
struct X {
	X() { cout << "Ĭ�Ϲ��캯����X()" << endl; }//Ĭ�Ϲ��캯��
	X(const X &x) { cout << "�������캯����X(const X&)" << endl; }//�������캯��
	X& operator=(const X&) { cout << "������ֵ�������X& operator=(const X&)" << endl; return *this; }
	~X() { cout << "����������~X()" << endl; }
};
#endif // !X_H
