#pragma once
//����Employee�࣬������Ա������Ψһ֤��
#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include<string>
using namespace std;
class Employee {
public:
	Employee() { id = ++Employee::globalId; }
	Employee(const string & s) :name(s) { id = ++globalId; }
	Employee(const Employee & e) :name(e.name) { id = ++globalId; }
	Employee& operator=(const Employee & e) { name = e.name; id = ++globalId; return *this; }
	size_t get_id() { return id; }
private:
	static size_t globalId;
	string name;
	size_t id;
};
size_t Employee::globalId = 0;//���ھ�̬��Ա���ⲿ����
#endif // !EMPLOYEE_H
