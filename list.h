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
	
	int del(string st)
	{
		Node *cur;

		// Ноль
		if (size == 0) return -1;


		// Один
		if (size == 1)
		{
			if (root->key == st)
			{
				size = 0;
				delete root;
				root = NULL;
				tail = NULL;
				return 1;
			}
			else return - 1;
		}
		
		// Много
		cur = root;
		for (int i = 0; i < size; i++)
		{
			if (cur->key == st)
			{

				// Первый
				if (cur == root)
				{
					Node * tmp;
					tmp = root;
					root = root->next;
					delete tmp;
					root->prev = NULL;
					size--;
					return 1;
				}				
				
				//Последний
				if (cur == tail)
				{
					tail = cur->prev;
					delete cur;
					size--;
					return 1;
				}
							
				//В серединке
				Node * tmp;
				tmp = cur;
				cur->next->prev = cur->prev;
				cur->prev->next = cur->next;
				delete tmp;
				size--;
				return 1;

			}


			cur = cur->next;

		}
		return -1;	
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


