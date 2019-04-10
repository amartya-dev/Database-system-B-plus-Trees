#include<iostream>
#include "Data_handling.h"
#include "B+.h"
#include<fstream>
using namespace std;
fstream indset(".//index.txt", ios::app);
fstream recset(".//recset.txt", ios::app);
int main()
{
	if (dirExists("./Database") == true)
	{
		cout << "\nDatabase already exists data has been loaded, continue ";
		string line, line2;
		ifstream load(".//index.txt");
		if (load.is_open())
		{
			int i = 0;
			while (getline(load, line))
			{
				i++;
				insert(line);
			}
			load.close();
		}
		ifstream load2(".//recset.txt");
		if (load2.is_open())
		{
			int i = 0;
			while (getline(load2, line))
			{
				i++;
				append(line);
			}
			load2.close();
		}
	}
	else
	{
		_mkdir("./Database");
		int n;
		cout << "\nThe database has been created , enter the number of attributes of a record to continue ";
		cin >> n;
		records(n);
		dat * temp = beg;
		while (temp != NULL)
		{
			recset << temp->data << "\n";
			temp = temp->next;
		}
	}
	int ch = 1;
	while (ch != 0)
	{
		cout << "\nEnter : \n1 for entering records \n2 for deleting record \n3 search for a particular record : ";
		cin >> ch;
	if (ch == 1)
	{
		string key_value, line;
		cout << "\nEnter the key value for the record : ";
		cin >> key_value;
		indset << key_value << "\n";
		create_data(key_value);
		insert(key_value);
	}
	else if (ch == 2)
	{
		string key_value;
		cout << "\nEnter the key value for the record to be deleted : ";
		cin >> key_value;
		del(root, key_value);
		rdir(key_value);
	}
	else if (ch == 3)
	{
		string to_search;
		cout << "\nEnter the key value to be searched : ";
		cin >> to_search;
		if (search(root, to_search) == true)
		{
			string temp;
			cout << "\nEnter the record which you want to print : ";
			cin >> temp;
			readit(to_search, temp);
		}
		else
		{
			cout << "\nData does not exist in the system ";
		}
	}
}
}