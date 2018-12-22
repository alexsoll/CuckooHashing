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



	int string_to_int(string st)
	{

		int pos = 0;
		int prime = 67;
		int pow = 1;
		for (int i = 0; i < st.length(); i++)
		{
			pos += st[i] * pow;
			pow *= prime;
		}
		pos = abs(pos);
		return pos;
	}



	int Find(string st)
	{
		int pos = string_to_int(st);
		pos = k_indep_funck(pos) % size;

		bool find;

		find = root[pos].findKey(st);

		if (find)
		{
			Node * tmp;
			tmp = root[pos].root;

			for (int i = 0; i < root[pos].size; i++)
			{
				if (tmp->key == st)
				{
					cur = tmp;
					break;

				}
			}
			return 1;
		}
		cur = NULL;
		return -1;	
	}
	
	int del(string st)
	{
		int pos = HashFunc(st);
		pos %= size;
		int res = root[pos].del(st);

		if (res == 1) return 1;
		if (res == -1) return -1;
	}



	
	int size;
	int el_count;
	List *root;
	Node * cur;

	int k;
	int p;
	int *k_indep_arr;

	int k_indep_funck(int hs)
	{

		int res = 0;
		for (int i = 0; i < k; i++) {
			res += k_indep_arr[i] * mypoww(hs, k - i - 1);
		}
		res = abs(((res % p) % size));

		return res;
	}



	bool IsPrime(int num) {
		for (int i = 2; i <= sqrt(num) + 1; i++)
			if (num%i == 0)
				return false;
		return true;
	}

	
	listhashTable(int _size, int _k)
	{
		cur = NULL;
		el_count = 0;
		size = _size;
		root = new List[size];



		k = _k;

		k_indep_arr = new int[k];

		p = _size;

		while (true) {
			if (IsPrime(p) == true)
				break;
			else
				p++;
		}

		k_indep_arr[0] = (rand() % p) + 1;

		for (int i = 1; i < k; i++) {
			k_indep_arr[i] = rand() % p;
		}





	}

	bool isEmpty()
	{
		if (el_count == 0) return true;
		return false;
	}

	int Place(Node node)
	{
		//int pos = HashFunc(node.key);
	//	pos %= size;
		int pos = string_to_int(node.key);
		pos = k_indep_funck(pos) % size;


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

