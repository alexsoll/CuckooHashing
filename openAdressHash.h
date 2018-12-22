#pragma once
#include "list.h"




class openAdressHashTable
{
public:
	int size;
	Node *root;
	int el_count;
	int *k_indep_hash_func;
	int p;
	int k;

	string empety_key = "";
	string was_use_key = "\n\r";
	
	int colission_resolving_count;

	int HashFunc(string key)
	{
		long long int pos = 0;
		const int prime_number = 67;
		long long int res = 0, p_pow = 1;
		/*int hash_pos = 0;
		for (int i = 0; i < key.length(); i++)
		{
			hash_pos += key[i] * mypoww(67, i);			
		}

		return abs(hash_pos);*/

		for (int i = 0; i < key.length(); i++) {
			pos += abs(key[i] - 'a' + 1) * p_pow;
			p_pow *= prime_number;
		}
		for (int i = 0; i < k; i++) {
			res += k_indep_hash_func[i] * mypoww(pos, k - i - 1);
		}
		res = abs(((res % p) % size));
		return res;
	}

	// Конструктор
	openAdressHashTable(int _size, int _k)
	{
		size = _size;
		colission_resolving_count = 0;
		if (size <= 0) throw - 1;
		
		el_count = 0;

		///// Add k-independent Hash Function /////
		k = _k;
		k_indep_hash_func = new int[k];
		p = size;
		while (true) {
			if (IsPrime(p) == true)
				break;
			else
				p++;
		}

		k_indep_hash_func[0] = (rand() % p) + 1;
		for (int i = 1; i < k; i++) {
			k_indep_hash_func[i] = rand() % p;
		}

		///////////////////////////////////////

		root = new Node[size];
		for (int i = 0; i < size; i++)
		{
			root[i].key = empety_key;
			root[i].val = 0;
		}
	}

	~openAdressHashTable()
	{
		delete[] root;		
	}

	bool IsPrime(int num) {
		for (int i = 2; i <= sqrt(num) + 1; i++)
			if (num%i == 0)
				return false;
		return true;
	}

	long long int mypoww(long long int a, long long int b) {
		long int res = 1;
		for (long long int i = 0; i < b; i++) {
			res *= a;
		}
		return res;
	}

	int Place(Node node)
	{
		int pos = HashFunc(node.key);	
		

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



};

