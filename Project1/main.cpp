//������࣬��⿽�����캯����������ֵ����������������ĵ���
#include"X.h"
#include<memory>
#include<vector>
using namespace std;
X copyX(const X x) { return x; }
int main() {
	{
	X x1, x2;//Ĭ�Ϲ��캯��
	X x3(x1), x4 = x2;//�������죬��������
	cout << endl;
	x4 = copyX(x2);//�Ҳ���ʱ����������������
	cout << endl;
	X x5[2] = {};
	cout << endl;
	x5[0] = x1;//������ֵ
	cout << endl;
	X *xp = new X();
	cout << endl;
	delete xp;
	cout << endl;
	auto xsp1(make_shared<X>()), xsp2 = (make_shared<X>()), xsp3(xsp1);
	cout << endl;
	xsp2.reset();
	cout << endl;
	vector<X> xv;
	cout << endl;
	xv.push_back(x1);
	cout << endl;
}
	system("pause");
	return 0;
}