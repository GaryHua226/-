#include"Analyse.h"
/*string Analyse::split_string(const string& s, const string& c)//切割出括号内的内容
{
	string::size_type pos1, pos2;
	pos1 = s.find("(") + 1;
	pos2 = s.find(")");
	string str = s.substr(pos1, pos2 - pos1);
	return str;
}

void Analyse::split(const string& s, vector<string> &v, const string& c)//括号内按,分割
{
	string::size_type pos1, pos2;
	int i = 0;
	while (i<2)
	{
		pos1 = s.find(", ");
		v.push_back(s.substr(0, pos1));
		v.push_back(s.substr(pos1 + 2, s.length()));
	}
}*/

void Analyse::split_all(const string& order, vector<string>& v,const string& separator)
{
	string::size_type pos_sub_begin; // 子串开始位置  
	string::size_type pos_sep;//分隔符位置  
	string::size_type pos_end;
	if (order.find("(") == string::npos || order.find(")") == string::npos)
	{
		pos_sep = order.find(" ");
		pos_sub_begin = 0;
		while (string::npos != pos_sep)
		{
			v.push_back(order.substr(pos_sub_begin, pos_sep - pos_sub_begin));
			pos_sub_begin = pos_sep + separator.size();
			pos_sep = order.find(separator, pos_sub_begin);
		}
		if (pos_sub_begin != order.length())// 截取最后一段数据     
			v.push_back(order.substr(pos_sub_begin));
	}
	else
	{
		pos_sep = order.find(" ");
		pos_sub_begin = 0;
		pos_end = order.find("(");
		while (string::npos != pos_sep && pos_sep < pos_end)
		{
			v.push_back(order.substr(pos_sub_begin, pos_sep - pos_sub_begin));
			pos_sub_begin = pos_sep + separator.size();
			pos_sep = order.find(separator, pos_sub_begin);
		}
		pos_sub_begin = order.find(")") + 2;
		pos_sep = order.find(" ", pos_sub_begin);
		while (string::npos != pos_sep)
		{
			v.push_back(order.substr(pos_sub_begin, pos_sep - pos_sub_begin));
			pos_sub_begin = pos_sep + separator.size();
			pos_sep = order.find(separator, pos_sub_begin);
		}
		if (pos_sub_begin != order.length())// 截取最后一段数据     
			v.push_back(order.substr(pos_sub_begin));
	}
}

void Analyse::split_col(const string& order, vector<string>& v, const string& separator)
{
	string::size_type pos_sub_begin; // 子串开始位置  
	string::size_type pos_sep;//分隔符位置  
	string::size_type pos_end;
	pos_sep= order.find(", ");   
	pos_sub_begin= order.find("(")+1;  
	pos_end = order.find(")");
	while (string::npos != pos_sep)    
	{      
		v.push_back(order.substr(pos_sub_begin, pos_sep- pos_sub_begin));
		pos_sub_begin = pos_sep + separator.size();
		pos_sep = order.find(separator, pos_sub_begin);
	}    
	if (pos_sub_begin != pos_end )// 截取最后一段数据     
		v.push_back(order.substr(pos_sub_begin, pos_end - pos_sub_begin));
}
	
bool Analyse::create(const string& order)
{
	Analyse a;
	vector<string> col;
	a.split_col(order, col, ", ");
	vector<string> word;
	a.split_all(order, word, " ");
	if (order.find("(") == string::npos || order.find(")") == string::npos)
	{
		if (word.size()==5&&word[0] == "CREATE"&&word[1] == "TABLE"&&word[2] != ""&&word[3] == "FROM"&&word[4].size() >= 5)
		{
			smatch result;
			regex pattern("(.*)(.{4})");
			if (regex_match(word[4], result, pattern))
			{
				if (result[2] == ".txt")
				{
					cout << "Create successfully.\n";
					a.legal = true;
					return true;
				}
			}
		}
	}
	else
	{
		if (word.size()==5&&word[0] == "CREATE"&&word[1] == "TABLE"&&word[2] != ""&&word[3] == "TO"&&word[4].size()>=5)
		{
			smatch result;
			regex pattern("(.*)(.{4})");
			if (regex_match(word[4], result, pattern))
			{
				if (result[2] == ".txt")
				{
					cout << "Create successfully.\n";
					a.legal = true;
					return true;
				}
			}
		}
	}
	cout << "Illegal order.\n";
	return false;
}
