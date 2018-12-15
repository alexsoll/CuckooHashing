#pragma once
#include <iostream>
#include <time.h>
using namespace std;

//---------------------------------------------------------------------------------------------------------//


class THashTable{
protected:
	int HashFunc(int function, string k, int maxsize, int _a1, int _b1, int _a2, int _b2, int _p) {
		int pos = 0;
		switch (function) {
		case 1:
			for (int i = 0; i < k.length(); i++)
				pos += abs(k[i]);
			pos = ((pos * _a1 + _b1) % _p) % maxsize;
			break;
		case 2:
			for (int i = 0; i < k.length(); i++) {
				pos += abs(k[i]);
			pos = ((pos * _a2 + _b2) % _p) % maxsize;
			}
		
		}

		return pos;
	}
};


//---------------------------------------------------------------------------------------------------------//


class TArrayHash : public THashTable {
protected:
	int maxsize, curr, DataCount, a1, b1, p, a2, b2;
	int num_of_rehash;
	string **arr;
	int pos[2];




public:
	TArrayHash(int size = 500) {
		srand(time(NULL));
		num_of_rehash = 0;
		arr = new string*[2];
		arr[0] = new string[size];
		arr[1] = new string[size];
		maxsize = size;
		p = maxsize;
		while (true) {
			if (IsPrime(p) == true)
				break;
			else 
				p++;	
		}
		a1 = rand() % p + 1;
		b1 = rand() % p;
		a2 = rand() % p + 1;
		b2 = rand() % p;
		for (int i = 0; i < maxsize; i++) {
			arr[0][i] = "-";
			arr[1][i] = "-";
		}
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
		a1 = rand() % p + 1;
		b1 = rand() % p;
		a2 = rand() % p + 1;
		b2 = rand() % p;
		for (int i = 0; i < maxsize; i++) {
			arr[0][i] = "-";
			arr[1][i] = "-";
		}
	}
	int Find(string k) {
		curr = HashFunc(1,k, maxsize, a1,b1,a2,b2,p);
		if (arr[0][curr] == k || arr[0][curr] == k)
			return curr;
		curr = HashFunc(2, k, maxsize, a1, b1, a2, b2, p);
		if (arr[1][curr] == k || arr[1][curr] == k)
			return curr;
		return -1;
	}


	/* 
	This variant of the Place function attempts to add 
	an element to a particular hash table with the tableID index. 
	This option does not allow you to add an item to another table 
	when there is a free cell in it.
	*/

	/*void Place(string tr, int tableID, int cnt, int n) {  
		if (cnt == n) {
			cout << "Cycle present. Rehash. \n";
			return;
		}
		pos[0] = (this->HashFunc(1, tr)) % maxsize;
		pos[1] = (this->HashFunc(2, tr)) % maxsize;
		if (arr[0][pos[0]] == tr || arr[1][pos[1]] == tr)
			return;
		if (arr[tableID][pos[tableID]] != " ") {
			string tmp = arr[tableID][pos[tableID]];
			arr[tableID][pos[tableID]] = tr;
			Place(tmp, (tableID + 1) % 2, cnt + 1, n);
		}
		else {
			arr[tableID][pos[tableID]] = tr;
		}
	}*/

	/*
	This implementation takes into account the possibility to 
	choose between two tables if there is free space. If there are 
	no places in any of them, a random one is selected and the element 
	is added there. The extruded element tries to change position.
	*/

	bool Place(string tr, int cnt, int n) {
		bool flag;
		
		
		
		if (cnt == n) { // ??????????????
			cout << "Cycle present. Rehash. \n";
			rehash();
			num_of_rehash++;
			return false;
		}







		pos[0] = (this->HashFunc(1, tr, maxsize, a1, b1, a2, b2, p));
		pos[1] = (this->HashFunc(2, tr, maxsize, a1, b1, a2, b2, p));

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
	
	string GetValueInFirstTable(int pos) {
		return arr[0][pos];
	}
	string GetValueInSecondTable(int pos) {
		return arr[1][pos];
	}

	int GetNumOfRehash() {
		return num_of_rehash;
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

//---------------------------------------------------------------------------------------------------------//
