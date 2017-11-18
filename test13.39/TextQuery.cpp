#include"TextQuery.h"
#include<memory>
#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
//TextQuery��Ա��������
//���캯��
TextQuery::TextQuery(ifstream& infile) {
	string text;
	while (getline(infile, text)) {
		file->push_back(text);//��һ�ж���text��
		auto n = file->size() - 1;//��ǰ�к�
		istringstream line(text);
		string word;
		while (line >> word) {
			auto &lines = wm[word];//���word����wm�У����ص���һ���յ�shared_ptr��
			if (!lines)
				//���linesΪ��ָ�룬���������ڴ�
				lines.reset(new set<line_no>);
			lines->insert(n);//�����кŵ�set��
		}
	}
}//��������������
//��ѯ����query
QueryResult TextQuery::query(const string&s)const {
	static shared_ptr<set<line_no>> nodata(new set<line_no>);//���δ�ҵ����򷵻�һ���յ��к�set
	auto loc = wm.find(s);
	if (loc == wm.end())
		return QueryResult(s, nodata, file);
	else
		return QueryResult(s, loc->second, file);
}
ostream &print(ostream &os, const QueryResult & qr) {
	os << qr.sought << " occurs " << qr.lines->size() << " "
		<< (qr.lines->size() > 1 ? "times " : "time ") << endl;
	for (auto num : *qr.lines) {
		//��ӡÿһ�е��ı�
		os << "\t(line" << num + 1 << ") " << ends//��ӡ�к�
		<< *(qr.file->begin() + num) << endl;//��ӡfile�ж�Ӧ�е��ı�
			
		
	}
	return os;
}//��ӡ����