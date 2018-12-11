#define _CRT_SECURE_NO_WARNINGS
#include "CuckooHash.h"
#include <time.h>
#include <cstdlib>
#include <random>
using namespace std;


char* GetChar(string str) {
	int len = str.length();

	char* res = new char[len + 1];

	for (int i = 0; i < len; i++) {
		res[i] = str[i];
	}

	res[len] = '\0';
	return res;
}

void Cuckoo(string *tr, int size , int n, TArrayHash* &hash) {
	bool flag;
	for (int i = 0, cnt = 0; i < size; i++) {
		flag = hash->Place(tr[i], cnt, n); 
 		if (flag == false) {
			hash->rehash();
			i = -1;
		}
	}
}

string randomStrGen(int length, std::normal_distribution<> &uid, std::mt19937 &gen) {
	static string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
	string result;
	result.resize(length);

	for (int i = 0; i < length; i++) {
		result[i] = charset[uid(gen)];
	}
	//cout << GetChar(result) << " ";
	return result;
}


int main() {

	static string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
	std::mt19937 gen(time(0));
	std::normal_distribution<> dist(30, 7);
	string result;
	result.resize(4);

	TArrayHash *hs;
	int size = 400;
	int num_of_data = 100;
	hs = new TArrayHash(size);
	string *t;
	t = new string[num_of_data];
	int n = floor(3 * log(2000));
	for (int i = 0; i < num_of_data; i++) {
		t[i] = randomStrGen(20, dist, gen);
	}
	Cuckoo(t,num_of_data,n, hs);
	int rehash = hs->GetNumOfRehash();
	cout << "Number of rehash is " << rehash << " " << '\n';
	hs->printHash();
}
