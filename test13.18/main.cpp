#include"Employee.h"
#include<iostream>
using namespace std;
int main() {
	Employee e1("yuan"), e2;
	cout << e1.get_id() << ends << e2.get_id() << endl;
	Employee e3 = e1, e4;
	e4 = e1;
	cout << e3.get_id() << ends << e4.get_id() << endl;
	system("pause");
	return 0;
}