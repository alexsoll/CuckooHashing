#pragma once
#include "list.h"




class openAdressHashTable
{
public:
	int size;
	Node *root;
	int el_count;

	Node *cur;

	int k;
	int p;
	int *k_indep_arr;


	string empety_key = "";
	string was_use_key = "\n\r";
	
	int colission_resolving_count;

	int HashFunc(string key)
	{
		int hash_pos = 0;
		for (int i = 0; i < key.length(); i++)
		{
			hash_pos += key[i] * mypoww(67, i);			
		}

		return abs(hash_pos);
	}

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


	// Конструктор
	openAdressHashTable(int _size, int _k)
	{

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










		size = _size;
		colission_resolving_count = 0;
		if (size <= 0) throw - 1;
		cur = NULL;
		el_count = 0;


		root = new Node[size];
		for (int i = 0; i < size; i++)
		{
			root[i].key = empety_key;
			root[i].val = 0;
		}
	}


	// Деструктор
	~openAdressHashTable()
	{
		delete[] root;		
	}

	long long int mypoww(long long int a, long long int b) {
		long int res = 1;
		for (long long int i = 0; i < b; i++) {
			res *= a;
		}
		return res;
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








	// Вставка
	int Place(Node node)
	{
		//int pos = HashFunc(node.key) % size;	
		










		int pos = string_to_int(node.key);
		pos = k_indep_funck(pos) % size;



		if (isFull()) return -1;
		
		Node cur;
		cur = root[pos];
		int counter = 0;

		while (counter <= size) // доп защитка
		{
			if (cur.key == node.key) return 1; // Возвращаем, если нашли такой же
			if (cur.key == empety_key)
			{
				root[pos] = node;
				el_count++;
				return 0; //  Все отлично, вставились
			}
			if (cur.key == was_use_key || cur.key != empety_key)
			{
				pos += 1;
				pos %= size;
				colission_resolving_count++;
			}
			cur = root[pos];
			counter++;
		}

		return -1; // Нне нашли места :с		
	}


	bool isEmpety()
	{
		if (el_count == 0) return true;
		return false;
	
	}

	bool isFull()
	{
		if (el_count == size) return true;
		return false;
	}

	void print()
	{
		for (int i = 0; i < el_count; i++)
		{
			if (root[i].key != empety_key && root[i].key != was_use_key)
			{
				cout << i << " | key = " << root[i].key << " val = ";
				cout << root[i].val;
				cout << " |\n";				
			}
		}	
	}

	int Find(string st)
	{
		
		int pos = string_to_int(st);
		pos = k_indep_funck(pos) % size;
		Node el;
		el = root[pos];
		int counter = 0;
		while (counter < size + 1)
		{
			if (el.key == st) {
				cur = &el;
				return pos;
			}
			if (el.key == empety_key) return -1;
			if (el.key == was_use_key || (el.key != empety_key && el.key != was_use_key && st != el.key))
			{
				pos += 1;	pos %= size;
				el = root[pos];
			}
			counter += 1;
		}
		cur = NULL;
		return -1;

	}

};

