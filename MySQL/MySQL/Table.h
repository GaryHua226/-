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
	vector<vector<string>> content;//表格内容
	void drop_table();//删除table
	void insert(string, vector<vector<string>>);//插入信息
	void delete_info(string, vector<vector<string>>);//删除信息

	string name;//表名
	string filename;//文件名
	string accessfilename;//记录权限表的文件名
	string owner;//创建者
	int row;//记录有多少行
	int colum;//记录有多少列


	void load_content();//将文件里面的东西load进content中
	void store_content();//将content里面的东西store进文件中
	void delete_all();
	void delete_row(const string, const string);
	bool create_table(const string);//创建table
	bool create_table_from_file(const string);//从文件创建table
	void create_access_table();//创建权限表格
	bool insert_row(vector<string>);
	bool insert_distinct(vector<vector<string>>);
	void select_all();
	void select(vector<string>);
	void selectDistinct(const string);
	void grant(vector<string>, vector<string>, const string);
	void revoke(vector<string>, vector<string>, const string);
	Table() { row = 0; colum = 0; }
};