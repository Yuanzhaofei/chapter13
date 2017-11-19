#include"TextQuery.h"
#include<fstream>
#include<string>
#include<iostream>
using namespace std;

void runQueries(ifstream &);
ostream & print(ostream &, const QueryResult &);//打印函数声明

int main() {
	ifstream infile("test_book.txt");
	/*runQueries(infile);*/
	StrVec sv;
	sv.push_back("袁");
	cout << sv.capacity()<< endl;
	sv.reserve(5);
	cout << sv.capacity() << endl;
	system("pause");
	return 0;
}
//runQueries 函数接受一个指向输入文件的输入流,完成查询和打印结果的任务
void runQueries(ifstream & infile) {
	//保存输入文本
	TextQuery tq(infile);//使用输入流作为参数构造tq
	//用户交互，输入想要查询的单词（可能有多个），并打印结果
	while (true) {
		cout << "输入想要查询的单词，输入q退出。" << endl;
		string s;
		if (!(cin >> s) || s == "q") break;
		print(cout, tq.query(s)) << endl;//使用print函数，接受输出流，将结果打印到输出流，对单词s的查询应使用TextQuery的成员函数完成
	}

}