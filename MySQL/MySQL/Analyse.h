#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<regex>
#include<direct.h>
#include"Table.h"
using namespace std;
class Analyse
{
public:
	void split_col(const string& order, vector<string>& v, const string& separator);//�ָ�ָ��
	void split_all(const string& order, vector<string>& v, const string& separator);
	void split(const string& order, vector<string>&v, const string& separator);//separate a line using separator and store in v
	void split_insert_distinct(const string& order, vector<string>&v, const string& separator);
	void split_insert_distinct_col(const string& order, vector<string>&v, vector<string>&val, const string&separator);
	
	bool table_list(const string&);//��ӡ�����Լ�ӵ�е�table
	bool create(const string&);//����table
	bool create_from_file(const string&);//���ļ�����table
	bool drop(const string&);//ɾ��table
	bool insert_row(const string&);//������Ϣ
	bool insert_distinct(const string&);//����һ�У���ָ���ض�ֵ
	bool delete_row(const string&);//ɾ��������
	bool delete_all(const string&);//ɾ��������
	bool select(const string&);//ѡ��������չʾ
	bool select_all(const string&);//ѡ��������չʾ
	bool select_distinct(const string&);//ѡ��ؼ���չʾ
	bool select_sort(const string&);//����չʾ
	bool select_some(const string&);//չʾ����col=val����
	bool select_file(const string&);//��ѯ���д���ļ�
	bool grant(const string&);//��Ȩ
	bool revoke(const string&);//�ջ�Ȩ��
};

