


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
		while (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= 'а' && c <= 'я' || c >= 'А' && c <= 'Я')
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





/*

int size = 100000;
int num_of_data = 50000;
hs = new TArrayHash(4, size);
string *t;
t = new string[num_of_data];

string *dict = new string[250000];


//Загрузка словаря
ifstream ifs;
ifs.open("gauss_data_set_250K_words_2");
for (int i = 0; i < 250000; i++)
{
ifs >> dict[i];
}
ifs.close();



int n = floor(3 * log(size));


// Теперь все тащим из нашего словаря
for (int i = 0; i < num_of_data; i++) {
t[i] = dict[distr(gen)];
}




openAdressHashTable openAHST(35000, 4);
listhashTable listHST(sqrt(num_of_data) + 1, 4);

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




*/













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