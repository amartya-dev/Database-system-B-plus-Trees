#pragma once
#include<iostream>
using namespace std;
struct dat
{
	string data;
	dat * next;
}*beg;
void append(string a)
{
	dat *temp, *p = beg;
	if (beg == NULL)
	{
		temp = new dat;
		temp->data = a;
		temp->next = NULL;
		beg = temp;
	}
	else
	{
		temp = new dat;
		temp->data = a;
		while (p->next != NULL)
		{
			p = p->next;
		}
		p->next = temp;
		temp->next = NULL;
	}
}