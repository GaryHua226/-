#include<iostream>
#include<string>
#include<regex>
#include<vector>
#include"Analyse.h"
using namespace std;
inline void print_$()
{
	cout << "~$ ";
}
inline void print_arrow()
{
	cout << "(mysql)==> ";
}

int main()
{
	bool grant[7][8][11]={ false };
	Analyse a;
	while (1)
	{
		print_$();
		string command;
		getline(cin,command);
		if (command == "mySQL")
		{
			while (1)//mysqlÄÚ²¿
			{
				print_arrow();
				string order;
				getline(cin, order);
				if (order == "quit")//ÍË³ömysql
				{
					break;
				}
				if (a.create(order))
				{

				}
			}
		}
	}
	return 0;
}