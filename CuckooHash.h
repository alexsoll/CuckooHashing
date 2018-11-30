#pragma once
#include <iostream>
using namespace std;

//---------------------------------------------------------------------------------------------------------//


class THashTable{
protected:
	int HashFunc(int function, string k) {
		
		int pos = 0;
		switch (function) {
		case 1:
			for (int i = 0; i < k.length(); i++)
				pos += ((k[i] * 20 + 57) % 32749) % 500;
		
		case 2:
			for (int i = 0; i < k.length(); i++) {
				pos += ((k[i] * 13 + 73) % 32749) % 500;
			}
		return pos;
		}
	}
};


//---------------------------------------------------------------------------------------------------------//


class TArrayHash : public THashTable {
protected:
	int maxsize, curr, DataCount;
	string **arr;
	int pos[2];
public:
	TArrayHash(int size = 500) {
		arr = new string*[2];
		arr[0] = new string[size];
		arr[1] = new string[size];
		maxsize = size;
		for (int i = 0; i < maxsize; i++) {
			arr[0][i] = " ";
			arr[1][i] = " ";
		}
	}

	~TArrayHash() {
		delete[] arr;
	}

	void clear() {
		delete[] arr;
		arr = new string*[2];
		arr[0] = new string[maxsize];
		arr[1] = new string[maxsize];
		for (int i = 0; i < maxsize; i++) {
			arr[0][i] = " ";
			arr[1][i] = " ";
		}
		DataCount = 0;
		curr = 0;
	}


	bool Find(string k) {
		curr = HashFunc(1,k);
		if (arr[0][curr] == k || arr[0][curr] == k)
			return true;
		curr = HashFunc(2, k);
		if (arr[1][curr] == k || arr[1][curr] == k)
			return true;
		return false;
	}

	void Place(string tr, int tableID, int cnt, int n) {
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

};

//---------------------------------------------------------------------------------------------------------//
