#include"Table.h"
bool Table::create_table(const string order)//创建table
{
	Analyse a;
	vector<string> col;
	a.split_col(order, col, ", ");
	this->colum = (int)col.size();
	this->content.push_back(col);

	vector<string> word;
	a.split_all(order, word, " ");
	this->name = word[2];
	this->filename = word[2] + ".txt";

	this->filename = word[4].c_str();
	//判断要创建的table是否已经存在，即查找是否有相同的文件名即可
//--------------------------------------------------	
	fstream _file;
	_file.open(word[4].c_str(), ios::in);
	if (_file)
	{
		cout << "file already existed." << endl;
		return false;
	}

	//---------------------------------------------------	

	ofstream out_file;
	out_file.open(word[4].c_str(), ios::out);
	if (!out_file)
	{
		cout << "文件创建失败";
		return false;
	}
	for (int i = 0; i < (int)col.size(); i++)
	{
		out_file << col[i];
		if (i != col.size() - 1)
			out_file << ",";
		else
			out_file << endl;
	}
	out_file.close();
	return true;
}

bool Table::create_table_from_file(const string order)//从文件创建table
{
	Analyse a;
	vector<string> col;
	a.split_col(order, col, ", ");
	vector<string> word;
	a.split_all(order, word, " ");
	this->name = word[2];
	this->filename = word[4];

	//判断文件存不存在
//----------------------------------------	
	fstream infile;
	infile.open(word[4].c_str(), ios::in);
	if (!infile)
	{
		cout << "file not existed\n";
		return false;
	}
	//----------------------------------------	

		//以下将用来读取第一行的标题
	string temp;
	getline(infile, temp);
	vector<string> title;
	a.split(temp, title, ",");
	this->content.push_back(title);
	this->colum = (int)title.size();
	//一下将读取每一行的内容
	vector<string> row;
	while (getline(infile, temp))
	{
		row.clear();
		a.split(temp, row, ",");
		this->content.push_back(row);
		this->row++;
	}
	infile.close();
	return true;
}

void Table::create_access_table()
{
	this->accessfilename = this->name + ".csv";
	ofstream access_file;
	access_file.open(this->accessfilename.c_str(), ios::out);
	access_file.close();
}

void Table::drop_table()//删除table
{
	DeleteFile(this->filename.c_str());
}

bool Table::insert_row(vector<string> column)
{
	ofstream out_file;
	out_file.open(this->filename.c_str(), ios::app);
	if (!out_file)
	{
		cout << "file open failed." << endl;
		return false;
	}
	for (int i = 0; i < (int)column.size(); i++)
	{
		out_file << column[i];
		if (i != (int)column.size() - 1)
			out_file << ",";
		else
			out_file << endl;
	}
	out_file.close();
	cout << "Insert successfully." << endl;
	this->content.push_back(column);
	this->row++;
	return true;
}

bool Table::insert_distinct(vector<vector<string>> insert_infos)
{
	ofstream out_file;
	out_file.open(this->filename, ios::app);
	if (!out_file)
	{
		cout << "Cannot open the file." << endl;
		return false;
	}
	for (int i = 0; i < (int)content[0].size(); i++)
	{
		for (int j = 0; j < (int)insert_infos.size(); j++)
		{
			if (insert_infos[j][0] == content[0][i])
			{
				out_file << insert_infos[j][1];
				break;
			}
		}
		if (i == (int)content[0].size() - 1)
			out_file << endl;
		else
			out_file << ",";
	}
	cout << "Insert successfully." << endl;
	out_file.close();
	load_content();
	return true;
}

void Table::delete_all()
{
	ifstream in_file;
	in_file.open(this->filename, ios::in);
	if (!in_file)
	{
		cout << "file cannot be opened." << endl;
		return;
	}
	vector<string> title;
	string temp;
	getline(in_file, temp);
	Analyse a;
	a.split(temp, title, ",");

	in_file.close();

	ofstream out_file;
	out_file.open(this->filename, ios::out);
	for (int i = 0; i < (int)title.size(); i++)
	{
		out_file << title[i];
		if (i == (int)title.size() - 1)
			out_file << endl;
		else
			out_file << ",";
	}
	out_file.open(this->filename, ios::out);
	out_file.close();
	this->row = 0;
	load_content();
	cout << "Delete successfully." << endl;
}

void Table::delete_row(const string del_column, const string del_value)
{
	int index;//记录要删除的column是第几个
	for (int i = 0; i < this->colum; i++)
		if (this->content[0][i] == del_column)
		{
			index = i;
			break;
		}
	//先将content里面的对应数据删掉，再尝试写会文件里面
	vector<vector<string>> temp;
	vector<vector<string>>::iterator it1 = content.begin();
	temp.push_back(*it1);
	it1++;
	for (; it1 < content.end(); it1++)
	{
		if ((*it1)[index] == del_value)
			continue;
		temp.push_back(*it1);
	}
	content.swap(temp);
	store_content();
	cout << "Delete successfully." << endl;
}

void Table::load_content()
{
	ifstream in_file;
	in_file.open(this->filename, ios::in);
	if (!in_file)
	{
		cout << "error";
		return;
	}
	content.clear();
	vector<string> row;
	string temp;
	Analyse a;
	this->row = -1;
	this->content.clear();
	while (getline(in_file, temp))
	{
		row.clear();
		a.split(temp, row, ",");
		this->content.push_back(row);
		this->row++;
	}
	in_file.close();
}

void Table::store_content()
{
	ofstream out_file;
	out_file.open(this->filename, ios::out);
	if (!out_file)
	{
		cout << "error!" << endl;
		return;
	}
	vector<vector<string>>::iterator it1 = content.begin();
	for (; it1 != content.end(); it1++)
	{
		for (int i = 0; i < (int)(*it1).size(); i++)
		{
			out_file << (*it1)[i];
			if (i != (int)(*it1).size() - 1)
				out_file << ",";
			else
				out_file << endl;
		}
	}
	out_file.close();
}

void Table::select(vector<string> show_cols)
{
	for (int i = 0; i < (int)show_cols.size(); i++)
	{
		printf("%-10s", show_cols[i].c_str());
		if (i == (int)show_cols.size() - 1)
			cout << endl;
	}
	vector<int> indexs;
	for (int i = 0; i < (int)show_cols.size(); i++)
	{
		for (int j = 0; j < (int)this->content[0].size(); j++)
		{
			if (show_cols[i] == content[0][j])
			{
				indexs.push_back(j);
				break;
			}
		}
	}
	vector<vector<string>>::iterator it1 = this->content.begin();
	it1++;
	for (; it1 < this->content.end(); it1++)
	{
		for (int i = 0; i < (int)indexs.size(); i++)
		{
			printf("%-10s", (*it1)[indexs[i]].c_str());
			if (i == (int)indexs.size() - 1)
				cout << endl;
		}
	}
}


void Table::select_all()
{
	printf("%-5s", "ID");
	for (int i = 0; i < this->content[0].size(); i++)
	{
		printf("%-10s", this->content[0][i].c_str());
		if (i == this->content[0].size() - 1)
			cout << endl;
	}
	vector<vector<string>>::iterator it1 = content.begin();
	it1++;
	int i = 1;
	for (; it1 != content.end(); it1++)
	{
		printf("%-5d", i);
		for (int j = 0; j < (int)(*it1).size(); j++)
		{
			printf("%-10s", (*it1)[j].c_str());
			if (j == (int)(*it1).size() - 1)
				cout << endl;
		}
		i++;
	}
}

bool is_exist(vector<string> buff, const string new_str)//判断new_str是否已经存在buff中
{
	vector<string>::iterator it1 = buff.begin();
	for (; it1 < buff.end(); it1++)
	{
		if ((*it1) == new_str)
			return true;
	}
	return false;
}

void Table::selectDistinct(const string show_col)
{
	bool col_exist = false;
	vector<string> buff;//先将要输出的东西存到这里以检查有没有相同的
	int index;//记录要从展示的列是content里面的第几列
	for (index = 0; index < (int)content[0].size(); index++)
	{
		if (content[0][index] == show_col)
		{
			col_exist = true;
			break;
		}
	}
	if (!col_exist)
	{
		cout << "this column doesn't exist." << endl;
		return;
	}
	cout << show_col.c_str() << endl;
	vector<vector<string>>::iterator it1 = content.begin();
	it1++;
	for (; it1 < content.end(); it1++)
	{
		if (!is_exist(buff, (*it1)[index]))
			buff.push_back((*it1)[index]);
	}
	vector<string>::iterator it2 = buff.begin();
	for (; it2 < buff.end(); it2++)
	{
		cout << (*it2) << endl;
	}
}

bool got_access(vector<vector<string>> access_table, const string test_user, const string test_application)
{
	for (int i = 0; i < (int)access_table.size(); i++)
	{
		if (access_table[i][1] == test_user && access_table[i][2] == test_application)
			return true;
	}
	return false;
}

void Table::grant(vector<string> accesses, vector<string> users, const string current_user)
{
	vector<vector<string>> ori_access_table;//先将原来的表读出来看看使用grant的user是否有相应地权限来授予他人
	ifstream in_file;
	in_file.open(this->accessfilename.c_str(), ios::in);
	if (!in_file)
	{
		cout << "error." << endl;
		return;
	}
	string lineStr;
	while (getline(in_file, lineStr))
	{
		stringstream ss(lineStr);
		string str;
		vector<string> lineArray;
		//按照逗号分隔
		while (getline(ss, str, ','))
			lineArray.push_back(str);
		ori_access_table.push_back(lineArray);
	}
	in_file.close();

	ofstream out_file;
	out_file.open(this->accessfilename.c_str(), ios::app);
	for (int i = 0; i < (int)accesses.size(); i++)
	{
		if (!(this->owner == current_user || got_access(ori_access_table, current_user, accesses[i])))
			continue;
		for (int j = 0; j < (int)users.size(); j++)
		{
			out_file << current_user << ',' << users[j] << ',' << accesses[i] << endl;
		}
	}
	out_file.close();
}

bool has_granted(vector<vector<string>> access_table, const string current_user, const string test_user, const string test_application)
{
	for (int i = 0; i < (int)access_table.size(); i++)
	{
		if (access_table[i][0] == current_user && access_table[i][1] == test_user && access_table[i][2] == test_application)
			return true;
	}
	return false;
}

/*void Table::revoke(vector<string> accesses, vector<string> users, const string current_user)
{
	vector<vector<string>> ori_access_table;//先将原来的表读出来看看使用grant的user是否有相应地权限来授予他人
	ifstream in_file;
	in_file.open(this->accessfilename.c_str(), ios::in);
	if (!in_file)
	{
		cout << "error." << endl;
		return;
	}
	string lineStr;
	while (getline(in_file, lineStr))
	{
		stringstream ss(lineStr);
		string str;
		vector<string> lineArray;
		//按照逗号分隔
		while (getline(ss, str, ','))
			lineArray.push_back(str);
		ori_access_table.push_back(lineArray);
	}
	in_file.close();

	ofstream out_file;
	out_file.open(this->accessfilename.c_str(), ios::app);
	for (int i = 0; i < (int)accesses.size(); i++)
	{

		for (int j = 0; j < (int)users.size(); j++)
		{
			for (int i = 0; i < (int)ori_access_table.size(); i++)
			{
				if (ori_access_table[i][0] == current_user && ori_access_table[i][1] == users[j] && ori_access_table[i][2] == accesses[i])
					ori_access_table.erase(ori_access_table[i]);
			}
		}
	}
	out_file.close();


}*/