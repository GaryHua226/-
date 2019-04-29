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
	void split_col(const string& order, vector<string>& v, const string& separator);//分割指令
	void split_all(const string& order, vector<string>& v, const string& separator);
	void split(const string& order, vector<string>&v, const string& separator);//separate a line using separator and store in v
	void split_insert_distinct(const string& order, vector<string>&v, const string& separator);
	void split_insert_distinct_col(const string& order, vector<string>&v, vector<string>&val, const string&separator);
	
	bool table_list(const string&);//打印所有自己拥有的table
	bool create(const string&);//创建table
	bool create_from_file(const string&);//从文件创建table
	bool drop(const string&);//删除table
	bool insert_row(const string&);//插入信息
	bool insert_distinct(const string&);//插入一行，仅指定特定值
	bool delete_row(const string&);//删除若干行
	bool delete_all(const string&);//删除所有行
	bool select(const string&);//选择若干列展示
	bool select_all(const string&);//选择所有列展示
	bool select_distinct(const string&);//选择关键字展示
	bool select_sort(const string&);//排序展示
	bool select_some(const string&);//展示满足col=val的行
	bool select_file(const string&);//查询结果写入文件
	bool grant(const string&);//授权
	bool revoke(const string&);//收回权限
};

