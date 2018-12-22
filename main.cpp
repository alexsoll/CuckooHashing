#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
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

		openAdressHashTable openAHST(35000, 2);
		listhashTable listHST(sqrt(num_of_data) + 1, 2);
		
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


		st_time = GetTickCount();
		Cuckoo(t, num_of_data, n, hs);
		en_time = GetTickCount();
		coockoo_time = en_time - st_time;


		int rehash = hs->GetNumOfRehash();
				

		cout << "Number of rehash is " << rehash << " " << '\n';
		cout << "Number of string " << hs->getDataCount() << '\n';
	
		cout << "Collisio resolve count in open adress hash table = " << openAHST.colission_resolving_count << "\n";
		cout << "Avereage dispersion on list HS = " << listHST.dispers() << "\n";
		cout << "List table hash size = " << listHST.size << "\n";
	
		cout << "\n";
		cout << "Coockoo time = \t" << coockoo_time << "ms\n";
		cout << "Open adress time = \t" << open_adress_time << "ms\n";
		cout << "List hast table time = \t" << list_hash_time << "ms\n";
		



	
	return 0;
}

















/* // LIST TESTING BLOCK
list.push(Node("Lol", 1));
list.del("Lol");
list.printList();
list.push(Node("Lol", 1));
list.printList();
list.push(Node("Lol1", 1));
cout << "\n";
list.printList();
list.del("Lol");
cout << "\n";
list.printList();
list.push(Node("Lol2", 1));
list.push(Node("Lol3", 1));
list.push(Node("Lol4", 1));
list.push(Node("Lol5", 1));
cout << "\n";
list.printList();
list.del("Lol5");
cout << "\n";
list.printList();

list.del("Lol3");
cout << "\n";
list.printList();
*/










// Data_set_generation


/*
for (int i = 0; i < 50000; i++)
{
string_to_int_stats[i] = 0;
}




string ran;

ofstream ofs;
ofs.open("gauss_data_set_250K_words_3", 'w');


ofstream ofs_2;
ofs_2.open("gauss_data_set_250K_staticks_words_3", 'w');




int counter = 0;
int o_counter = 0;;


while (counter < 5000)
{
ran = randomStrGen(10, dist, gen);
int pos = string_to_int(ran) % 50000;
if (pos < 10000)
{
ofs << ran << " ";
string_to_int_stats[pos]++;
counter++;
}

}
cout << "10K gen" << "\n";
counter = 0;



while (counter < 20000)
{
ran = randomStrGen(10, dist, gen);
int pos = string_to_int(ran) % 50000;
if (pos > 10000 && pos < 15000)
{
ofs << ran << " ";
string_to_int_stats[pos]++;
counter++;
}

}
cout << "10-15K gen" << "\n";
counter = 0;



while (counter < 200000)
{
ran = randomStrGen(10, dist, gen);
int pos = string_to_int(ran) % 50000;
if (pos > 15000 && pos < 35000)
{
ofs << ran << " ";
string_to_int_stats[pos]++;
counter++;
}

}
cout << "15-35K gen" << "\n";
counter = 0;


while (counter < 20000)
{
ran = randomStrGen(10, dist, gen);
int pos = string_to_int(ran) % 50000;
if (pos > 35000 && pos < 40000)
{
ofs << ran << " ";
string_to_int_stats[pos]++;
counter++;
}

}
cout << "35-40KK gen" << "\n";
counter = 0;

while (counter < 5000)
{
ran = randomStrGen(10, dist, gen);
int pos = string_to_int(ran) % 50000;
if (pos > 40000 && pos < 50000)
{
ofs << ran << " ";
string_to_int_stats[pos]++;
counter++;
}

}
cout << "40-50K gen" << "\n";
counter = 0;




for (int i = 0; i < 50000; i++)
ofs_2 << string_to_int_stats[i] << "\r\n";

ofs.close();
ofs_2.close();



*/