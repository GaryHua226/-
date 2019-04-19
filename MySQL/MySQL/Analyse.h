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
	void split_col(const string& order, vector<string>& v, const string& separator);//分割指令
	void split_all(const string& order, vector<string>& v, const string& separator);

	bool create(const string&);//创建table
	bool drop(string input_string);//删除table
	bool insert(string input_string);//插入信息
	bool delete_info(string);//删除信息
	bool select(string input_string);//选择
	bool grant(string input_string);//授权
	bool revoke(string input_string);//收回权限
};

