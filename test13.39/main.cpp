#include"TextQuery.h"
#include<fstream>
#include<string>
#include<iostream>
using namespace std;

void runQueries(ifstream &);
ostream & print(ostream &, const QueryResult &);//��ӡ��������

int main() {
	ifstream infile("test_book.txt");
	/*runQueries(infile);*/
	StrVec sv;
	sv.push_back("Ԭ");
	cout << sv.capacity()<< endl;
	sv.reserve(5);
	cout << sv.capacity() << endl;
	system("pause");
	return 0;
}
//runQueries ��������һ��ָ�������ļ���������,��ɲ�ѯ�ʹ�ӡ���������
void runQueries(ifstream & infile) {
	//���������ı�
	TextQuery tq(infile);//ʹ����������Ϊ��������tq
	//�û�������������Ҫ��ѯ�ĵ��ʣ������ж����������ӡ���
	while (true) {
		cout << "������Ҫ��ѯ�ĵ��ʣ�����q�˳���" << endl;
		string s;
		if (!(cin >> s) || s == "q") break;
		print(cout, tq.query(s)) << endl;//ʹ��print������������������������ӡ����������Ե���s�Ĳ�ѯӦʹ��TextQuery�ĳ�Ա�������
	}

}