#include"String.h"
#include<iostream>
using namespace std;
int main() {
	const char c[] = { 'y','u','a','n' };
	const char c2[] = "yuan";
	String s(c2);
	cout << s.size() << endl;
	system("pause");
	return 0;
}