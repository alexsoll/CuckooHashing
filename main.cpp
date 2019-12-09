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

void time_to_add_x_in_build_table();


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




void time_to_find();



int main() {
	
	
	time_to_find();

	return 0;
}



void time_to_add_x_in_build_table()
{

	static string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
	std::mt19937 gen(time(0));
	std::normal_distribution<> dist(30, 7);


	string result;
	result.resize(4);
	srand(time(NULL));



	DWORD coockoo_time;
	DWORD open_adress_time;
	DWORD list_hash_time;


	TArrayHash *hs;


	// Разгеним таблицы
	int data_count = 1000000;
	int dict_size = 1000000;
	int add_ins = 20000;


	openAdressHashTable openAHST(data_count + add_ins, 5);
	listhashTable listHST(data_count / 10, 5);
	hs = new TArrayHash(5, data_count * 4);


	// Загрузим данные
	string *dict = new string[dict_size]; //  Весь словарь
	string *dict_to_hash = new string[data_count]; // Хэшируемая часть словаря
	ifstream ifs;
	ifs.open("gauss_data_set_1KK_words_1");

	for (int i = 0; i < dict_size; i++)
	{
		ifs >> dict[i];
	}
	// Считали данные в словарик

	// Захэшируем данные в таблички

	for (int i = 0; i < data_count; i++)
	{
		long long int index = 0;
		index = (double(dict_size) * double(i)) / double(data_count);
		dict_to_hash[i] = dict[index];
	}
	// Просто равномерно выберем данные


	DWORD st, en;
	cout << "ok dict build\n";
	st = GetTickCount();
	for (int i = 0; i < data_count; i++)
	{
		listHST.Place(Node(dict_to_hash[i], 0));
	}
	en = GetTickCount();
	list_hash_time = en - st;
	cout << "time build list hash = " << list_hash_time << "ms" << '\n';


	st = GetTickCount();
	for (int i = 0; i < data_count; i++)
	{
		openAHST.Place(Node(dict_to_hash[i], 0));
	}
	en = GetTickCount();
	open_adress_time = en - st;
	cout << "time build open address hash = " << open_adress_time << "ms" << '\n';
	// Заполнили обычные хэши
	//cout << "Ok list and open Hashing\n";


	st = GetTickCount();
	int n = floor(3 * log(data_count * 4));
	Cuckoo(dict_to_hash, data_count, n, hs);
	en = GetTickCount();
	coockoo_time = en - st;
	cout << "time build cuckoo hash = " << coockoo_time << "ms" << '\n';

	cout << "Number of different key " << hs->getDataCount() << "\n";

	// Довставляем еще 5К элементов

	string word;



	string *to_insert = new string[add_ins];

	for (int i = 0; i < add_ins; i++)
	{
		int pos = rand() * rand();

		pos = abs(pos) % 1000000;
		to_insert[i] = dict[pos];
	}


	st = GetTickCount();
	for (int i = 0; i < add_ins; i++)
	{
		hs->Place(to_insert[i], 0, 0, n);
	}
	en = GetTickCount();
	coockoo_time = en - st;

	cout << "Coocko time insert " << add_ins << '\t' << coockoo_time << "ms\n";


	st = GetTickCount();
	for (int i = 0; i < add_ins; i++)
	{
		listHST.Place(Node(to_insert[i], 0));
	}
	en = GetTickCount();
	list_hash_time = en - st;

	cout << "List time insert " << add_ins << '\t' << list_hash_time << "ms\n";



	st = GetTickCount();
	for (int i = 0; i < add_ins; i++)
	{
		openAHST.Place(Node(to_insert[i], 0));

	}
	en = GetTickCount();
	open_adress_time = en - st;

	cout << "Open adress time insert " << add_ins << '\t' << open_adress_time << "ms\n";




}





void time_to_del_half()
{
	static string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
	std::mt19937 gen(time(0));
	std::normal_distribution<> dist(30, 7);


	string result;
	result.resize(4);
	srand(time(NULL));

	DWORD coockoo_time;
	DWORD open_adress_time;
	DWORD list_hash_time;


	TArrayHash *hs;


	// Разгеним таблицы
	int data_count = 635000;
	int dict_size = 1000000;

	openAdressHashTable openAHST(data_count, 5);
	listhashTable listHST(sqrt(data_count), 5);
	hs = new TArrayHash(5, data_count * 4);


	// Загрузим данные
	string *dict = new string[dict_size]; //  Весь словарь
	string *dict_to_hash = new string[data_count]; // Хэшируемая часть словаря
	ifstream ifs;
	ifs.open("gauss_data_set_1KK_words_1");

	for (int i = 0; i < dict_size; i++)
	{
		ifs >> dict[i];
	}
	// Считали данные в словарик

	// Захэшируем данные в таблички

	for (int i = 0; i < data_count; i++)
	{
		long long int index = 0;
		index = (double(dict_size) * double(i)) / double(data_count);
		dict_to_hash[i] = dict[index];
	}
	// Просто равномерно выберем данные

	cout << "ok dict build\n";

	for (int i = 0; i < data_count; i++)
	{
		listHST.Place(Node(dict_to_hash[i], 0));
		openAHST.Place(Node(dict_to_hash[i], 0));
	}
	// Заполнили обычные хэши
	cout << "Ok list and open Hashing\n";




	int n = floor(3 * log(data_count * 4));
	Cuckoo(dict_to_hash, data_count, n, hs);

	cout << hs->getDataCount() << "\n";



	DWORD st, en;
	// Попробуем удалить из словаря четверть слов



	//	DWORD st, en;

	//Замутим удаление половины словаря
	st = GetTickCount();
	for (int i = 0; i < data_count;)
	{
		hs->Delete(dict_to_hash[i]);
		i += 2;
	}
	en = GetTickCount();
	coockoo_time = en - st;

	cout << "Coocko time = \t" << coockoo_time << "ms\n";


	st = GetTickCount();
	for (int i = 0; i < data_count;)
	{
		listHST.del(dict_to_hash[i]);
		i += 2;
	}
	en = GetTickCount();
	list_hash_time = en - st;

	cout << "List time  = \t" << list_hash_time << "ms\n";



	st = GetTickCount();
	for (int i = 0; i < data_count;)
	{
		openAHST.del(dict_to_hash[i]);
		i += 2;
	}
	en = GetTickCount();
	open_adress_time = en - st;

	cout << "Open adress time = \t" << open_adress_time << "ms\n";


}





void time_to_find()
{
	static string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
	std::mt19937 gen(time(0));
	std::normal_distribution<> dist(30, 7);


	string result;
	result.resize(4);
	srand(time(NULL));

	DWORD coockoo_time;
	DWORD open_adress_time;
	DWORD list_hash_time;


	TArrayHash *hs;


	// Разгеним таблицы
	int data_count = 10000;
	int dict_size = 1000000;

	openAdressHashTable openAHST(data_count, 5);
	listhashTable listHST(sqrt(data_count), 5);
	hs = new TArrayHash(5, data_count * 4);


	// Загрузим данные
	string *dict = new string[dict_size]; //  Весь словарь
	string *dict_to_hash = new string[data_count]; // Хэшируемая часть словаря
	ifstream ifs;
	ifs.open("gauss_data_set_1KK_words_1");

	for (int i = 0; i < dict_size; i++)
	{
		ifs >> dict[i];
	}
	// Считали данные в словарик

	// Захэшируем данные в таблички

	for (int i = 0; i < data_count; i++)
	{
		long long int index = 0;
		index = (double(dict_size) * double(i)) / double(data_count);
		dict_to_hash[i] = dict[index];
	}
	// Просто равномерно выберем данные

	cout << "ok dict build\n";

	for (int i = 0; i < data_count; i++)
	{
		listHST.Place(Node(dict_to_hash[i], 0));
		openAHST.Place(Node(dict_to_hash[i], 0));
	}
	// Заполнили обычные хэши
	cout << "Ok list and open Hashing\n";




	int n = floor(3 * log(data_count * 4));
	Cuckoo(dict_to_hash, data_count, n, hs);

	cout << hs->getDataCount() << "\n";



	DWORD st, en;

	//Замутим поиски всего словаря
	st = GetTickCount();
	for (int i = 0; i < data_count; i++)
	{
		hs->Find(dict_to_hash[i]);
	}
	en = GetTickCount();
	coockoo_time = en - st;

	cout << "Coocko time = \t" << coockoo_time << "ms\n";


	st = GetTickCount();
	for (int i = 0; i < data_count; i++)
	{
		listHST.Find(dict_to_hash[i]);
	}
	en = GetTickCount();
	list_hash_time = en - st;

	cout << "List time  = \t" << list_hash_time << "ms\n";

	st = GetTickCount();
	for (int i = 0; i < data_count; i++)
	{
		//openAHST.Find(dict_to_hash[i]);
	
			openAHST.Find(dict_to_hash[i]);
	}
	en = GetTickCount();
	open_adress_time = en - st;

	cout << "Open adress time = \t" << open_adress_time << "ms\n";

	cout << "Ok hashing\n";

}
