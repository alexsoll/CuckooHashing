#pragma once
#include <stdlib.h>
#include <string>
#include <iostream>
using namespace std;


class Node
{


public:
	string  key;
	long int val;

	Node * prev;
	Node * next;


	Node(string str, long int _val)
	{
		key = str;
		val = _val;	
	}


	Node()
	{
		prev = NULL;
		next = NULL;
	}
	
};


class List
{
public:
	Node *root;
	Node *tail;
	int size;



	List()
	{
		root = NULL;
		size = 0;
	}
	
	int push(Node node)
	{
		
		if (size == 0)
		{
			root = new Node;
			root->next = NULL;
			root->prev = NULL;
			root->key = node.key;
			root->val = node.val;
			tail = root;
			size++;
			return 0;
		}
		

		if (size != 0)
		{
			bool status;

			status = findKey(node.key);

			if (status == true) return 1;

			Node *tmp = new Node;
			tmp->next = NULL;
			tmp->prev = tail;
			tail->next = tmp;
			tmp->val = node.val;
			tmp->key = node.key;
			tail = tmp;
			size++;
			return 0;
		}
			
		
	}

	bool findKey(string key)
	{
		if (size == 0) return false;
		else
		{
			Node * curr = root;
			for (int i = 0; i < size; i++)
			{
				if (curr->key == key)
				{
					return true;
				}
				curr = curr->next;
			}
			return false;
		}	
	}

	void printList()
	{
		Node * curr = root;
		for (int i = 0; i < size; i++)
		{
			cout << "| key = " << curr->key << " val = ";
			cout << curr->val;
			cout << " |";
			curr = curr->next;
		}
	}



};


