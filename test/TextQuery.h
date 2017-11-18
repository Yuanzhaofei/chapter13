#pragma once
#pragma once
#ifndef TEXTQUERY_H
#define TEXTQUERY_H
#include<string>
#include<vector>
#include<map>
#include<set>
#include<memory>
#include<iostream>
#include"StrVec.h"
using namespace std;


class QueryResult;//��ѯ���

//TextQuery�࣬���������ļ����������ʺͳ��ֵ�������map�У����ڲ�ѯ
class TextQuery {
public:
	using line_no = vector<string>::size_type;//��������
	//���캯������
	TextQuery(ifstream & infile);//��������������
	QueryResult query(const string&)const;//���뵥�ʣ����в�ѯ������ɳ�����Ա��������Ϊ����ָ�����ݳ�Ա�����ܱ��ı�
private:
	shared_ptr<StrVec> file;//���������ļ������������๲����Ϊ��������Ҫ��ӡ����������
	map<string, shared_ptr<set<line_no>>> wm;//�����ѯ���ʼ��кţ��к���Ҫ�������������࣬����ʹ�ö�̬�ڴ汣��
};

//�����������࣬��TextQuery�Ĳ�ѯ����query���أ����������ѯ�����Ҫ������Ԫ��
class QueryResult {
	friend ostream &print(ostream &os, const QueryResult & qr);//��ӡ�����������Ԫ����
public:
	using line_no = vector<string>::size_type;//��������
	QueryResult(string s, shared_ptr<set<line_no>> l, shared_ptr<StrVec> f) :sought(s), lines(l),file(f){}
	set<line_no>::iterator begin() { return lines->begin(); }//����set��λ�õ�����
	set<line_no>::const_iterator begin() const{ return lines->begin(); }//����set��λ�õ�����
	set<line_no>::iterator end() { return lines->end(); }//����set��λ�õ�����
	set<line_no>::const_iterator end()const { return lines->end(); }//����set��λ�õ�����
	shared_ptr<StrVec> get_file() { return file; }//����ָ�������ļ�������ָ��
	const shared_ptr<StrVec> get_file()const { return file; }
private:
	string sought;//��ѯ�ĵ���
	shared_ptr<set<line_no>> lines;//ָ���кŵ�shared_ptr
	shared_ptr<StrVec> file;//ָ�������ļ���shared_ptr
};
#endif // !TEXTQUERY_H
