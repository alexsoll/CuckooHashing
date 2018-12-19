#pragma once
#include "list.h"



class listhashTable
{


public:


	long long int mypoww(long long int a, long long int b) {
		long int res = 1;
		for (long long int i = 0; i < b; i++) {
			res *= a;
		}
		return res;
	}


	int HashFunc(string key)
	{
		int hash_pos = 0;
		for (int i = 0; i < key.length(); i++)
		{
			hash_pos += key[i] * mypoww(67, i);
		}

		return abs(hash_pos);
	}


	
	int size;
	int el_count;
	List *root;
	
	listhashTable(int _size)
	{

		el_count = 0;
		size = _size;
		root = new List[size];
	}

	bool isEmpty()
	{
		if (el_count == 0) return true;
		return false;
	}

	int Place(Node node)
	{
		int pos = HashFunc(node.key);
		pos %= size;

		bool already_exist = root[pos].findKey(node.key);
		if (already_exist) return 1;

		root[pos].push(node);
		el_count++;	
	}

	void print()
	{
		for (int i = 0; i < size; i++)
		{
			cout << "---------------\n";
			cout << i + 1;
			
			if (root[i].size == 0) cout << " - \n";
			else
			{
				
				Node *cur = root[i].root;
				for (int j = 0; j < root[i].size; j++)
				{
					cout << "\t" << i + 1 << "." << j + 1 << "\t"<< cur->key << "\n";
					cur = cur->next;
				}
				//cout << "---------------\n";
			}


		}
	}
	
	double dispers()
	{
		double me = (double(el_count) / (double)size); // Вот примерно по столько элементов мы ждем в каждом списке
				
		// Теперь посчитаем среднее по отклонению
		double disp_sum = 0;

		for (int i = 0; i < size; i++)
		{
			disp_sum += (double(root[i].size) - me) *  (double(root[i].size) - me);
		}
		disp_sum = sqrt(disp_sum);
		disp_sum /= size;
		return disp_sum;
	}



};

