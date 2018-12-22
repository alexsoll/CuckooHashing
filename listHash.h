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


	
	int size;
	int el_count;
	List *root;
	int *k_indep_hash_func;
	int p;
	int k;
	
	listhashTable(int _size, int _k)
	{

		el_count = 0;
		size = _size;
		root = new List[size];

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

	}

	bool IsPrime(int num) {
		for (int i = 2; i <= sqrt(num) + 1; i++)
			if (num%i == 0)
				return false;
		return true;
	}

	bool isEmpty()
	{
		if (el_count == 0) return true;
		return false;
	}

	int Place(Node node)
	{
		int pos = HashFunc(node.key);
		//pos %= size;

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

