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
		string cin_name;//������û���
		cin >> cin_name;
		print_arrow();
		cout << "password: ";
		string cin_psw;//���������
		cin >> cin_psw;
	}
}