#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<regex>
using namespace std;
class Analyse
{
public:
	bool legal = false;
	void split_col(const string& order, vector<string>& v, const string& separator);//�ָ�ָ��
	void split_all(const string& order, vector<string>& v, const string& separator);

	bool create(const string&);//����table
	bool drop(string input_string);//ɾ��table
	bool insert(string input_string);//������Ϣ
	bool delete_info(string);//ɾ����Ϣ
	bool select(string input_string);//ѡ��
	bool grant(string input_string);//��Ȩ
	bool revoke(string input_string);//�ջ�Ȩ��
};

