#define _CRT_SECURE_NO_WARNINGS
#include "list.h"
#include <time.h>
#include "CuckooHash.h"
#include <cstdlib>
#include <random>
#include <fstream>
#include <vector>
#include "openAdressHash.h"
#include "listHash.h"
#include <Windows.h>
using namespace std;


struct dict;




struct dict
{
	vector<string> words;

	long int size;
};


string genRandString(int n)
{

	string out = "";
	for (int i = 0; i < n; i++)
	{
		out += 'a' + rand() % 26;
	}
	return out;
}

char* GetChar(string str) {
	int len = str.length();

	char* res = new char[len + 1];

	for (int i = 0; i < len; i++) {
		res[i] = str[i];
	}

	res[len] = '\0';
	return res;
}

void Cuckoo(string *tr, int size, int n, TArrayHash* &hash) {
	bool flag;
	for (int i = 0, cnt = 0; i < size; i++) {
		flag = hash->Place(tr[i], 0, cnt, n);
		if (flag == false) {
			hash->rehash();
			i = -1;
		}
	}
}




void volkovCuckoo(dict di, int size, int n, TArrayHash* &hash) {
	bool flag;
	size = di.size;
	for (int i = 0, cnt = 0; i < size; i++) {
		flag = hash->Place(di.words[i],0, cnt, n);
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
		result[i] = charset[abs(int(uid(gen)))%61];
	}
	//cout << GetChar(result) << " ";
	return result;
}












/*int main_2()
{
	srand(time(NULL));

	

	setlocale(LC_ALL, "Russian");

	dict di;
	di.size = 0;
	


	ifstream ifs("war.txt");

	if (ifs) cout << "good\n";

	char c;
	int counter = 0;

	while (counter < 20000)
	{
		string st = "";
		c = ifs.get();
		while (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= 'à' && c <= 'ÿ' || c >= 'À' && c <= 'ß')
		{
			st += c;
			c = ifs.get();
			counter++;
		}
		if (st.length() > 0)
		{
			di.words.push_back(st);
			di.size++;
		}
	}

	List list;

	cout << "war_list_size = " << di.size << "\n";
	for (int i = 0; i < di.size; i++)
	{
		list.push(Node(di.words[i], 1));
	}




	static string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
	std::mt19937 gen(time(0));
	std::normal_distribution<> dist(30, 7);
	string result;
	result.resize(4);

	TArrayHash *hs;
	int size = 10000;
	int num_of_data = 100;
	hs = new TArrayHash(size);
	string *t;
	t = new string[num_of_data];
	int n = floor(3 * log(2000));



	for (int i = 0; i < num_of_data; i++) {
		t[i] = randomStrGen(20, dist, gen);
		//	t[i] = "LOL";s
	}


	Cuckoo(t, num_of_data, n, hs);
	volkovCuckoo(di, num_of_data, n, hs);
	int rehash = hs->GetNumOfRehash();
	
	hs->printHash();
	cout << "Number of rehash is " << rehash << " " << '\n';


	return 0;
}*/

int main() {
	static string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
	std::mt19937 gen(time(0));
	std::normal_distribution<> dist(30, 7);
	string result;
	result.resize(4);
	srand(time(NULL));
	TArrayHash *hs;
	DWORD coockoo_time;
	DWORD open_adress_time;
	DWORD list_hash_time;


	List list;





	//for (int z = 0; z < 1000; z++)
	//{

		int size = 50000;
		int num_of_data = 35000;
		hs = new TArrayHash(5, size);
		string *t;
		t = new string[num_of_data];
		int n = floor(3 * log(size));
		//n = 4 * size;
		for (int i = 0; i < num_of_data; i++) {
			t[i] = randomStrGen(10, dist, gen);
		}


		openAdressHashTable openAHST(35000 * 1.5);
		listhashTable listHST(sqrt(num_of_data) + 1);




		DWORD st_time;
		DWORD en_time;

		st_time = GetTickCount();
		for (int i = 0; i < num_of_data; i++)
		{
			listHST.Place(Node(t[i], -1));
		}
		en_time = GetTickCount();
		list_hash_time = en_time - st_time;






		st_time = GetTickCount();
		for (int i = 0; i < num_of_data; i++)
		{
		openAHST.Place(Node(t[i], -1));
		}
		en_time = GetTickCount();
		open_adress_time = en_time - st_time;

		
//		ofstream ofs;
//		ofs.open("data", 'w');
//		for (int i = 0; i < num_of_data; i++)
//			ofs << t[i] << " ";
//		ofs.close();

	//	ifstream ifs("data");
		//for (int i = 0; i < num_of_data; i++)
		//	ifs >> t[i];
		//ifs.close();
	
		st_time = GetTickCount();
		Cuckoo(t, num_of_data, n, hs);
		en_time = GetTickCount();
		coockoo_time = en_time - st_time;


		int rehash = hs->GetNumOfRehash();



		
	//	hs->printHash();
		cout << "Number of rehash is " << rehash << " " << '\n';
		cout << "Number of string " << hs->getDataCount() << '\n';
	//	cout << "Count of element in list hash table = " << listHST.el_count << "\n";
		cout << "Collisio resolve count in open adress hash table = " << openAHST.colission_resolving_count << "\n";
		cout << "Avereage dispersion on list HS = " << listHST.dispers() << "\n";
		cout << "List table hash size = " << listHST.size << "\n";
		//openAHST.print();
		cout << "\n";
		cout << "Coockoo time = \t" << coockoo_time << "ms\n";
		cout << "Open adress time = \t" << open_adress_time << "ms\n";
		cout << "List hast table time = \t" << list_hash_time << "ms\n";


		//listHST.print();
		
	//}

	
	return 0;
}