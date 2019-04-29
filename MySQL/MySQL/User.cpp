#include"User.h"

inline void print_$()
{
	cout << "~$ ";
}
inline void print_arrow()
{
	cout << "(mysql)==> ";
}

void login()
{
	User user;
	bool flag_name = false;
	bool flag_password = false;
	while (1)
	{
		print_arrow();
		cout << "login: ";
		string cin_name;//输入的用户名
		cin >> cin_name;
		print_arrow();
		cout << "password: ";
		string cin_psw;//输入的密码
		cin >> cin_psw;
	}
}