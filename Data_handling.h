#include <iostream>
#include<direct.h>
#include<filesystem>
#include <fstream>
#include <string>
#include<windows.h>
#include "linked.h"
using namespace std;
string ln;
bool dirExists(string dirName_in)
{
	DWORD ftyp = GetFileAttributesA(dirName_in.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES)
		return false; //something is wrong with your path!
	if (ftyp & FILE_ATTRIBUTE_DIRECTORY)
		return true; // this is a directory!
	return false; // this is not a directory!
}
void records(int n)
{
	for (int i = 0; i < n; i++)
	{
		string rec_to_ins;
		cout << "\nEnter the record : ";
		cin >> rec_to_ins;
		append(rec_to_ins);
	}
}
void create_data(string a)
{
	dat * temp = beg;
	string dir_name;
	dir_name = "./Database/" + a;
	_mkdir(dir_name.c_str());
	ofstream ofile(".//Database//" + a + "//" + a + ".txt");
	while (temp != NULL)
	{
		string h;
		cout << "\n Enter " << temp->data << " ";
		cin >> h;
		ofile << h << "\n";
		temp = temp->next;
	}
}
void readit(string h, string re)
{
	string line;
	ifstream ofile(".//Database//" + h + "//" + h + ".txt");
	if (ofile.is_open())
	{
		dat * tt = beg;
		int i = 0;
		while (getline(ofile, line))
		{
			i++;
			if (tt->data == re)
			{
				cout << "\nThe required record is : " << line << "\n";
			}
			tt = tt->next;
		}
		ofile.close();
	}
	else
	{
		cout << "\nUnable to read file ";
	}
}
void rdir(string key)
{
	string dir_name, h;
	h = "./Database/" + key + "/" + key + ".txt";
	remove(h.c_str());
	dir_name = "./Database/" + key;
	_rmdir(dir_name.c_str());
}
