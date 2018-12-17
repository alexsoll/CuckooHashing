#pragma once
#include <iostream>
#include <time.h>
#include <random>
using namespace std;

//---------------------------------------------------------------------------------------------------------//



class THashTable {
protected:

	long long int mypoww(long long int a, long long int b) {
		long int res = 1;
		for (long long int i = 0; i < b; i++) {
			res *= a;
		}
		return res;
	}

	long long int HashFunc(int function, string st, int maxsize, int* &k_indep1, int* &k_indep2, int _p, int k) {
		long long int pos = 0;
		const int prime_number = 67;
		long long int res = 0, p_pow = 1;
		switch (function) {
			/*case 1:
				for (int i = 0; i < k.length(); i++)
					pos += abs(k[i]);
				pos = ((pos * _a1 + _b1) % _p) % maxsize;
				break;
			case 2:
				for (int i = 0; i < k.length(); i++) {
					pos += abs(k[i]);
				pos = ((pos * _a2 + _b2) % _p) % maxsize;
				}

			*/
		case 1:
			for (int i = 0; i < st.length(); i++) {
				pos += abs(st[i] - 'a' + 1) * p_pow;
				p_pow *= prime_number;
			}
				//pos += abs(st[i] * exp((i + 1)));
				//pos += abs(st[i] * (i+1));
			for (int i = 0; i < k; i++) {
				res += k_indep1[i] * mypoww(pos, k - i - 1);
			}
			res = abs(((res % _p) % maxsize));
			break;
		case 2:
			for (int i = 0; i < st.length(); i++) {
				pos += abs(st[i] - 'a' + 1) * p_pow;
				p_pow *= prime_number;
			}
				//pos += abs(st[i] * exp((i + 1)));
				//pos += abs(st[i] * (i + 1));
			for (int i = 0; i < k; i++) {
				res += k_indep2[i] * mypoww(pos, k - i - 1);
			}
			res = abs(((res % _p) % maxsize));
			break;
		}
		return res;
	}

};

 
//---------------------------------------------------------------------------------------------------------//


class TArrayHash : public THashTable {
protected:
	int maxsize, curr, DataCount, a1, b1, p, a2, b2;
	int num_of_rehash;
	string **arr;
	int k;
	int *k_indep_hash_func1, *k_indep_hash_func2;
	int pos[2];

	//static std::mt19937 gen;
	//static std::uniform_int_distribution<> dist;



public:
	TArrayHash(int _k = 2,int size = 500) {
		//srand(time(NULL));
		k = _k;
		num_of_rehash = 0;
		arr = new string*[2];
		arr[0] = new string[size];
		arr[1] = new string[size];
		maxsize = size;
		p = maxsize;
		k_indep_hash_func1 = new int[k];
		k_indep_hash_func2 = new int[k];
		while (true) {
			if (IsPrime(p) == true)
				break;
			else 
				p++;	
		}
		//p = 433494437;
		k_indep_hash_func1[0] = rand() % p + 1;
		k_indep_hash_func2[0] = rand() % p + 1;
		for (int i = 1; i < k; i++) {
			k_indep_hash_func1[i] = rand() % p ;
			k_indep_hash_func2[i] = rand() % p ;
		}
		for (int i = 0; i < k; i++) {
			cout << k_indep_hash_func1[i] << " ";
		}
		cout << '\n';
		for (int i = 0; i < k; i++) {
			cout << k_indep_hash_func2[i] << " ";
		}
		cout << '\n';
		for (int i = 0; i < maxsize; i++) {
			arr[0][i] = "-";
			arr[1][i] = "-";
		}
	}

	long int mypoww(long int a, long int b) {
	long int res = 1;
	for (long int i = 0; i < b; i++) {
		res *= a;
	}
	return res;
}

	bool IsPrime(int num) {
		for (int i = 2; i <= sqrt(num); i++)
			if (num%i == 0)
				return false;
		return true;
	}

	~TArrayHash() {
		delete[] arr[1];
		delete[] arr[2];
		delete[] arr;
		delete[] k_indep_hash_func1;
		delete[] k_indep_hash_func2;
	}


	void clear() {
		delete[] arr;
		arr = new string*[2];
		arr[0] = new string[maxsize];
		arr[1] = new string[maxsize];
		for (int i = 0; i < maxsize; i++) {
			arr[0][i] = "-";
			arr[1][i] = "-";
		}
		DataCount = 0;
		curr = 0;
	}

	void rehash() {
		DataCount = 0;
		//delete[] arr[1];
		//delete[] arr[2];
		delete[] arr;

		arr = new string*[2];
		arr[0] = new string[maxsize];
		arr[1] = new string[maxsize];
		k_indep_hash_func1[0] = rand() % p + 1;
		k_indep_hash_func2[0] = rand() % p + 1;
		for (int i = 1; i < k; i++) {
			k_indep_hash_func1[i] = rand() % p;
			k_indep_hash_func2[i] = rand() % p;
		}
		for (int i = 0; i < k; i++) {
			cout << k_indep_hash_func1[i] << " ";
		}
		cout << '\n';
		for (int i = 0; i < k; i++) {
			cout << k_indep_hash_func2[i] << " ";
		}
		cout << '\n';
		for (int i = 0; i < maxsize; i++) {
			arr[0][i] = "-";
			arr[1][i] = "-";
		}
	}
	int Find(string st) {
		curr = HashFunc(1,st, maxsize, k_indep_hash_func1, k_indep_hash_func2, p, k);
		if (arr[0][curr] == st || arr[0][curr] == st)
			return curr;
		curr = HashFunc(2, st, maxsize, k_indep_hash_func1, k_indep_hash_func2, p, k);
		if (arr[1][curr] == st || arr[1][curr] == st)
			return curr;
		return -1;
	}


	/* 
	This variant of the Place function attempts to add 
	an element to a particular hash table with the tableID index. 
	This option does not allow you to add an item to another table 
	when there is a free cell in it.
	*/

	bool Place(string tr, int tableID, int cnt, int n) { 
		bool flag;
		if (cnt == n) {
			cout << "Cycle present. Rehash. \n";
			rehash();
			num_of_rehash++;
			return false;
		}
		pos[0] = (this->HashFunc(1, tr, maxsize, k_indep_hash_func1, k_indep_hash_func2, p, k)) % maxsize;
		pos[1] = (this->HashFunc(2, tr, maxsize, k_indep_hash_func1, k_indep_hash_func2, p, k)) % maxsize;
		if (arr[0][pos[0]] == tr || arr[1][pos[1]] == tr)
			return true;
		if (arr[tableID][pos[tableID]] != "-") {
			string tmp = arr[tableID][pos[tableID]];
			//DataCount++; 
			arr[tableID][pos[tableID]] = tr;
			flag = Place(tmp, (tableID + 1) % 2, cnt + 1, n);
			if (flag == false)
				return false;
		}
		else {
			arr[tableID][pos[tableID]] = tr;
			DataCount++;
			return true;
		}
	}

	/*
	This implementation takes into account the possibility to 
	choose between two tables if there is free space. If there are 
	no places in any of them, a random one is selected and the element 
	is added there. The extruded element tries to change position.
	*/

	/*bool Place(string tr, int cnt, int n) {
		bool flag;
				
		
		if (cnt == n) {
			cout << "Cycle present. Rehash. \n";
			rehash();
			num_of_rehash++;
			return false;
		}

		pos[0] = (this->HashFunc(1, tr, maxsize, k_indep_hash_func1,k_indep_hash_func2, p, k));
		pos[1] = (this->HashFunc(2, tr, maxsize, k_indep_hash_func1, k_indep_hash_func2, p, k));

		if (arr[0][pos[0]] == tr || arr[1][pos[1]] == tr)
			return true;
		if (arr[0][pos[0]] != "-" && arr[1][pos[1]] == "-") {
			arr[1][pos[1]] = tr;
			DataCount++;
			return true;
		}
		if (arr[1][pos[1]] != "-" && arr[0][pos[0]] == "-") {
			arr[0][pos[0]] = tr;
			DataCount++;
			return true;
		}
		if (arr[1][pos[1]] != "-" && arr[0][pos[0]] != "-") {
			int rand_position = rand() % 2;
			string tmp = arr[rand_position][pos[rand_position]];
			arr[rand_position][pos[rand_position]] = tr;
			flag = Place(tmp, cnt + 1, n);
			if (flag == false)
				return false;
		}
		else {
			int rand_position = rand() % 2;
			arr[rand_position][pos[rand_position]] = tr;
			DataCount++;
		}
	}
	*/
	string GetValueInFirstTable(int pos) {
		return arr[0][pos];
	}
	string GetValueInSecondTable(int pos) {
		return arr[1][pos];
	}

	int GetNumOfRehash() {
		return num_of_rehash;
	}
	int getDataCount() {
		return DataCount;
	}

	void remove(string st) {
		int pos = Find(st);
		if (pos == -1) {
			return;
		}
		if (arr[0][curr] == st)
			arr[0][curr] = "-";
		else
			arr[1][curr] = "-";
	}

	char* GetString(string str) {
		int len = str.length();

		char* res = new char[len + 1];

		for (int i = 0; i < len; i++) {
			res[i] = str[i];
		}

		res[len] = '\0';
		return res;
	}


	void printHash() {
		cout << "--------------TABLE 1----------------TABLE2------------" << '\n';
		for (int i = 0; i < maxsize; i++) {
			string tmp = GetValueInFirstTable(i);
			//cout << i  << '\t' << GetString(arr[0][i]) << '\t' << GetString(arr[1][i]) << '\n';
			cout << i << '\t' << GetString(arr[0][i]) << '\t' << GetString(arr[1][i]) << '\n';
			//cout << "Ëîë";
		}
 		cout << "--------------------------------------------------------";
	}

};


//std::mt19937 TArrayHash::gen = std::mt19937(time(NULL));
//std::uniform_int_distribution<> TArrayHash::dist = std::uniform_int_distribution<>(0, INT_MAX);
//---------------------------------------------------------------------------------------------------------//
