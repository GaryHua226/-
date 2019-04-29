#pragma once
#include<vector>
#include<string>
#include<fstream>
#include<iostream>
#include<direct.h>
#include<ostream>
#include<Windows.h>
#include <algorithm>
#include<sstream>
#include"Analyse.h"
using namespace std;
class Table
{
public:
	vector<vector<string>> content;//�������
	void drop_table();//ɾ��table
	void insert(string, vector<vector<string>>);//������Ϣ
	void delete_info(string, vector<vector<string>>);//ɾ����Ϣ

	string name;//����
	string filename;//�ļ���
	string accessfilename;//��¼Ȩ�ޱ���ļ���
	string owner;//������
	int row;//��¼�ж�����
	int colum;//��¼�ж�����


	void load_content();//���ļ�����Ķ���load��content��
	void store_content();//��content����Ķ���store���ļ���
	void delete_all();
	void delete_row(const string, const string);
	bool create_table(const string);//����table
	bool create_table_from_file(const string);//���ļ�����table
	void create_access_table();//����Ȩ�ޱ��
	bool insert_row(vector<string>);
	bool insert_distinct(vector<vector<string>>);
	void select_all();
	void select(vector<string>);
	void selectDistinct(const string);
	void grant(vector<string>, vector<string>, const string);
	void revoke(vector<string>, vector<string>, const string);
	Table() { row = 0; colum = 0; }
};