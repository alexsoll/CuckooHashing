#define _CRT_SECURE_NO_WARNINGS
#include "CuckooHash.h"
#include <time.h>
#include <cstdlib>
#include <random>
using namespace std;





int main_2() {

	/*static string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
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

	*/
	return 0;
}
