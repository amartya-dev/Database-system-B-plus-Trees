#pragma once
#include<iostream>
#include<string>
using namespace std;
# define count 100
//a tree node declared as class
class node;
class nodeprt
{
public:
	string data;
	node * down;
	nodeprt()
	{
		data = "";
		down = NULL;
	}
};
class node
{
public:
	//an array pointing to the nodeparts
	nodeprt * parts[count];
	bool isleaf;
	node * left_down;
	node * up;
	node * right;
	node()
	{
		for (int i = 0; i < count; i++)
		{
			parts[i] = new nodeprt();
			parts[i] = NULL;
		}
	}
}*root, *endleaf;
//a function to split a node which would return the root node part to be
//further inserted in the up node
nodeprt * split(node * source)
{
	node * temp_child2;
	temp_child2 = new node;
	nodeprt * temp_root;
	temp_root = new nodeprt;
	temp_root = source->parts[(int)((count - 1) / 2)];
	for (int i = (int)((count - 1) / 2) + 1; i < count; i++)
	{
		temp_child2->parts[i - (int)(count / 2)] = new nodeprt;
		temp_child2->parts[i - (int)(count / 2)] = source->parts[i];
		temp_child2->parts[i] = NULL;
	  source->parts[i] = NULL;
	}
	temp_root->down = temp_child2;
	source->right = temp_child2;
	return (temp_root);
}
//a function to insert a node part into a node
void insert(node * source, nodeprt * temp_root);
//a function to insert a srting into a node
void insert(node * source, string dat_ins)
{
	//checking if the node has a vacant space and if it is not fully vacant
	if (source->parts[count - 1] == NULL && source->parts[0] != NULL)
	{
		int i = 0;
		//checking the place where the data has to be inserted
		while (source->parts[i] != NULL && source->parts[i]->data < dat_ins)
		{
			i++;
		}
		//checking if there is no value existing at the place where data has
		//to be inserted
			if (source->parts[i] == NULL)
			{
				source->parts[i] = new nodeprt;
				source->parts[i]->data = dat_ins;
			}
		//to be executed if the place where data is to be inserted is already
		//full
			else
			{
				//loop to check the place which is empty
				int j = i;
				while (source->parts[j] != NULL)
				{
					j++;
				}
				source->parts[j] = new nodeprt;
				source->parts[j] = source->parts[j - 1];
				//loop to shift all the values to the right and insert the value
				//at the required place
					for (int k = j; k > i - 1; k--)
					{
						source->parts[k] = source->parts[k - 1];
					}
				source->parts[i] = new nodeprt;
				source->parts[i]->data = dat_ins;
			}
		source->isleaf = true;
		source->right = NULL;
	}
	//if the tree doesn't exist
	else if (source->parts[0] == NULL)
	{
		source->parts[0] = new nodeprt;
		source->parts[0]->data = dat_ins;
		root = source;
		source->isleaf = true;
	}
	//if the node where the value is to be inserted is already full
	else
	{
		nodeprt * temp;
		temp = new nodeprt;
		//splitting the source
		temp = split(source);
		//inserting data after splitting of the full node
		if (dat_ins < temp->data)
		{
			insert(source, dat_ins);
		}
		else
		{
			insert(source->right, dat_ins);
		}
		//making the nodepart returned as the root node if there is no preexisting
		//node above it
			if (source->up == NULL)
			{
				node * temp1;
				temp1 = new node;
				temp1->parts[0] = new nodeprt;
				temp1->parts[0] = temp;
				for (int i = 1; i < count; i++)
				{
					temp1->parts[i] = new nodeprt;
					temp1->parts[i] = NULL;
				}
				root = temp1;
				source->up = root;
				source->right->up = root;
				root->left_down = source;
			}
		//inserting the nodepart in the above node
			else
			{
				//recursive call with function overloading to insert the nodepart
				//into the above node
					insert(source->up, temp);
			}
	}
}
//a function to insert the nodepart returned after the splitting into a node
void insert(node * source, nodeprt * temp_root)
{
	if (source->parts[count - 1] == NULL)
	{
		int i = 0;
		while (source->parts[i]->data < temp_root->data)
		{
			i++;
		}
	  if (source->parts[i] == NULL)
	  {
		  source->parts[i] = new nodeprt;
		  source->parts[i] = temp_root;
	  }
	  else
	  {
		  int j = i;
		  while (source->parts[j] != NULL)
		  {
			  j++;
		  }
		  source->parts[j] = new nodeprt;
		  source->parts[j] = source->parts[j - 1];
		  for (int k = j; k > i - 1; k--)
		  {
			  source->parts[k] = source->parts[k - 1];
		  }
		  source->parts[i] = new nodeprt;
		  source->parts[i] = temp_root;
	  }
	}
	else
	{
		nodeprt * temp;
		temp = new nodeprt;
		temp = split(source);
		if (temp_root->data < temp->data)
		{
			insert(source, temp_root->data);
		}
		if (source->up == NULL)
		{
			node * temp1;
			temp1 = new node;
			temp1->parts[0] = new nodeprt;
			temp1->parts[0] = temp;
			for (int i = 1; i < count; i++)
			{
				temp1->parts[i] = new nodeprt;
				temp1->parts[i] = NULL;
			}
			root = temp1;
			source->up = root;
			root->left_down = source;
		}
		else
		{
			insert(source->up, temp);
		}
	}
}
//a function to search for a particular data
bool search(node * source, string a)
{
	bool exists = false;
	if (source->isleaf == true)
	{
		int i = 0;
		while (i < count && source->parts[i] != NULL)
		{
			if (source->parts[i]->data == a)
			{
				exists = true;
			}
			i++;
		}
		return (exists);
	}
	else
	{
		if (source->parts[0]->data >= a)
		{
			return (search(source->left_down, a));
		}
		else
		{
			int j = 0;
			while ((source->parts[j] != NULL) && (source->parts[j]->data < a))
			{
				j++;
			}
			return(search(source->parts[j - 1]->down, a));
		}
	}
}
void del(node * source, string to_del)
{
	if (search(root, to_del) == true)
	{
		if (source->parts[0]->data >= to_del)
		{
			del(source->left_down, to_del);
		}
		else
		{
			int i = 0;
			while (source->parts[i] != NULL && source->parts[i]->data <
				to_del)
			{
				i++;
			}
			if (source->isleaf == true && source->parts[i]->data == to_del)
			{
				source->parts[i]->data = "";
				for (int j = i; j < (count - 1); j++)
				{
					source->parts[j] = source->parts[j + 1];
				}
			}
			else
			{
				del(source->parts[i - 1]->down, to_del);
			}
		}
	}
	else
	{
		cout << "\n Data doesn't exist in the database ";
	}
}
void insert(string dat_ins)
{
	if (root == NULL)
	{
		endleaf = new node;
		insert(endleaf, dat_ins);
		root = new node;
		root = endleaf;
	}
	else if (root == endleaf)
	{
		insert(endleaf, dat_ins);
	}
	else
	{
		node * temp = root;
		while (temp->isleaf != true)
		{
			if (dat_ins < temp->parts[0]->data)
			{
				insert(temp->left_down, dat_ins);
				break;
			}
			else
			{
				int i = 0;
				while (temp->parts[i] != NULL && temp->parts[i]->data <
					dat_ins)
				{
					i++;
				}
				temp = temp->parts[i - 1]->down;
				insert(temp, dat_ins);
			}
		}
	}
}