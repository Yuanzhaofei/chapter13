#include"String.h"
#include<iostream>
#include<vector>
using namespace std;
int main() {
	//test13.47
	vector<String> vS;
	String myStr = "yuanzhaofei";
	//test14.7
	cout << myStr << endl;
	//����push_back���ܻ�����vector���ڴ����·��䣬
	//��ʱԪ�ػ�Ӿ��ڴ濽�������ڴ棨��ΪString��û�ж����ƶ����캯����
	vS.push_back(myStr);
	vS.push_back(myStr);
	vS.push_back(myStr);
	vS.push_back(myStr);
	system("pause");
	return 0;
}