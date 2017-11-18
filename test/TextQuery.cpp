#include"TextQuery.h"
#include<memory>
#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
//TextQuery成员函数定义
//构造函数
TextQuery::TextQuery(ifstream& infile) {
	string text;
	while (getline(infile, text)) {
		file->push_back(text);//将一行读入text中
		auto n = file->size() - 1;//当前行号
		istringstream line(text);
		string word;
		while (line >> word) {
			auto &lines = wm[word];//如果word不在wm中，返回的是一个空的shared_ptr，
			if (!lines)
				//如果lines为空指针，则给其分配内存
				lines.reset(new set<line_no>);
			lines->insert(n);//插入行号到set中
		}
	}
}//利用输入流构造
//查询函数query
QueryResult TextQuery::query(const string&s)const {
	static shared_ptr<set<line_no>> nodata(new set<line_no>);//如果未找到，则返回一个空的行号set
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
		//打印每一行的文本
		os << "\t(line" << num + 1 << ") " << ends//打印行号
		<< *(qr.file->begin() + num) << endl;//打印file中对应行的文本
			
		
	}
	return os;
}//打印函数