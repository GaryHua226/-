#include<iostream>
#include<string>
#include<regex>
#include<vector>

#include"Analyse.h"
#include"Table.h"
#include"User.h"
using namespace std;

inline void print_$()
{
	cout << "~$ ";
}
inline void print_arrow()
{
	cout << "(mysql)==> ";
}

//测试创建的table是否已经存在
bool is_valid_create(vector<Table> all_table, Table test_table)
{
	vector<Table>::iterator index = all_table.begin();
	for (; index != all_table.end(); index++)
		if (index->filename == test_table.filename)
		{
			cout << "this file name has been occupied by a table." << endl;
			return true;
		}
		else if (index->name == test_table.name)
		{
			cout << "this table name has been occipied by a table." << endl;
			return true;
		}
	return false;
}

void list_all_table(vector<Table>& all_table, User user)
{
	vector<Table>::iterator index = all_table.begin();
	int total = 0;
	for (; index != all_table.end(); index++)
	{
		if (index->owner == user.name)
		{
			total++;
			cout << "        " << index->name << ":" << " (" << index->colum << "," << index->row << ") ";
			cout << "[";

			for (int i=0;i < (int)index->content[0].size();i++)
			{
				cout <<index->content[0][i];
				if (i != index->content[0].size()-1)
					cout << " ";
				else
					cout << "]";
			}

			cout << " DROP INSERT DELETE SELECT ";

			cout << "[owner]" << endl;	
		}

		/*
		else if(this user has the access to the table )
		{	
			total++;
			cout << "        " << index->name << ":" << " (" << index->colum << "," << index->row << ") ";
			cout << "[";

			for (int i=0;i < (int)index->content[0].size();i++)
			{
				cout <<index->content[0][i];
				if (i != index->content[0].size()-1)
					cout << " ";
				else
					cout << "]";
			}

			cout << "(THE authority the user has) ";

			cout << "[user]" << endl;
		}
		*/

	}
	cout << "    total:" << total<<endl;
}

bool is_exist_table_name(vector<Table> all_table, string name)
{
	vector<Table>::iterator index = all_table.begin();
	for (; index != all_table.end(); index++)
		if (index->name == name)
		{
			return true;
		}
	return false;
}

int main()
{
	//for test data:
//---------------------------
	vector<string> test_data;
	//test_data.push_back("NAME");

	vector<vector<string>> test2_data;
	vector<string> b;
	b.push_back("NAME");
	b.push_back("li");
	test2_data.push_back(b);
	b.clear();
	b.push_back("GENDER");
	b.push_back("m");
	test2_data.push_back(b);

	vector<string> accesses;
	accesses.push_back("INSERT");
	accesses.push_back("DELETE");

	vector<string> users;
	users.push_back("guo");
	users.push_back("jin");
	//---------------------------


	vector<Table> all_table;
	Analyse a;
	/*while (1)
	{
		print_$();
		string command;
		getline(cin,command);
		if (command == "mySQL")
		{*/

	User test;
	test.name = "guolihua";

			while (1)//mysql内部
			{
				print_arrow();
				string order;
				getline(cin, order);
				if (order == "quit")//退出mysql
				{
					break;
				}
				if (a.create(order))
				{
					Table table;
					if (table.create_table(order))
						if (is_valid_create(all_table, table))
						{
							cout << "create successfully." << endl;
							table.owner = test.name;
							table.create_access_table();
							all_table.push_back(table);
						}
						else
						{
							DeleteFile(table.filename.c_str());
						}

				}
				else if (a.create_from_file(order))
				{
					Table table;
					if (table.create_table_from_file(order))
					{
						if (is_valid_create(all_table, table))
						{
							cout << "create successfully." << endl;
							table.owner = test.name;
							table.create_access_table();
							all_table.push_back(table);
						}
					}
				}
				else if (a.drop(order))
				{
					bool _drop = false;
					vector<string> word;
					a.split_all(order, word, " ");
					vector<Table>::iterator index = all_table.begin();
					for (; index != all_table.end(); index++)
						if (index->name == word[2])
						{
							_drop = true;
							index->drop_table();
							all_table.erase(index);
							cout << "Drop.\n";
							break;
						}
					if (_drop == false)
						cout << "no such table to drop." << endl;
				}
				else if (a.table_list(order))
				{
					list_all_table(all_table, test);
				}
				else if (a.insert_row(order))
				{
					Analyse a;
					vector<string> col;
					a.split_col(order, col, ", ");
					vector<string> word;
					a.split_all(order, word, " ");
					bool is_exist = false;
					vector<Table>::iterator index = all_table.begin();
					for (; index != all_table.end(); index++)
					{
						if (index->name == word[2])
						{
							index->insert_row(col);
							is_exist = true;
							break;
						}
					}
					if (is_exist == false)
						cout << "Table doesn't exist." << endl;
				}
				else if (a.insert_distinct(order))
				{
					vector<string> word;
					a.split_all(order, word, " ");
					bool is_exist = false;
					vector<Table>::iterator index = all_table.begin();
					for (; index != all_table.end(); index++)
					{
						if (index->name == word[2])
						{
							index->insert_distinct(test2_data);
							is_exist = true;
							break;
						}
					}
					if (is_exist == false)
						cout << "Table doesn't exist." << endl;

				}
				else if (a.delete_row(order))
				{
					vector<string> word;
					a.split_all(order, word, " ");
					bool is_exist = false;
					vector<Table>::iterator index = all_table.begin();
					for (; index != all_table.end(); index++)
					{
						if (index->name == word[2])
						{
							index->delete_row(word[4], word[6]);
							is_exist = true;
							break;
						}
					}
					if (is_exist == false)
						cout << "Table doesn't exist." << endl;

				}
				else if (a.delete_all(order))
				{
					vector<string> word;
					a.split_all(order, word, " ");
					bool is_exist = false;
					vector<Table>::iterator index = all_table.begin();
					for (; index != all_table.end(); index++)
					{
						if (index->name == word[3])
						{
							index->delete_all();
							is_exist = true;
							break;
						}
					}
					if (is_exist == false)
						cout << "Table doesn't exist." << endl;

				}
				else if (false/*a.select(order)*/)//这里应该放最普通的select,即按照用户给定的column来输出的那个
				{
					vector<string> word;
					a.split_all(order, word, " ");
					bool is_exist = false;
					vector<Table>::iterator index = all_table.begin();
					for (; index != all_table.end(); index++)
					{
						if (index->name == word[3])
						{
							index->select(test_data);
							is_exist = true;
							break;
						}
					}
					if (is_exist == false)
						cout << "Table doesn't exist." << endl;
				}
				else if (a.select_all(order))
				{
					vector<string> word;
					a.split_all(order, word, " ");
					bool is_exist = false;
					vector<Table>::iterator index = all_table.begin();
					for (; index != all_table.end(); index++)
					{
						if (index->name == word[3])
						{
							index->select_all();
							is_exist = true;
							break;
						}
					}
					if (is_exist == false)
						cout << "Table doesn't exist." << endl;
				}
				else if (a.select_distinct(order))
				{

					vector<string> word;
					a.split_all(order, word, " ");
					bool is_exist = false;
					vector<Table>::iterator index = all_table.begin();
					for (; index != all_table.end(); index++)
					{
						if (index->name == word[4])
						{
							index->select_all();
							is_exist = true;
							break;
						}
					}
					if (is_exist == false)
						cout << "Table doesn't exist." << endl;
				}
				else if (a.select_sort(order))
				{

				}
				else if (a.select_some(order))
				{

				}
				else if (a.select_file(order))
				{
					
				}
				else if (a.grant(order))
				{
					//for every_table in input
					//依次调用不同table的grant函数
					//-------------------------------------
					vector<string> word;
					a.split_all(order, word, " ");
					bool is_exist = false;
					vector<Table>::iterator index = all_table.begin();
					for (; index != all_table.end(); index++)
					{
						if (index->name == word[3])
						{
							index->grant(accesses/*这个需要从order里面分割出来*/, users/*这个要从order里面隔出来*/, test.name);
							cout << "grant successfully." << endl;
							is_exist = true;
							break;
						}
					}
					if (is_exist == false)
						cout << "Table doesn't exist." << endl;

					//--------------------------------------------
				}
				else if (a.revoke(order))
				{

				}
			}
		/*}
	}*/
	return 0;
}