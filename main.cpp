#include "CuckooHash.h"
using namespace std;


TArrayHash Cuckoo(string *tr, int n) {
	TArrayHash *hash;
	hash = new TArrayHash();

	for (int i = 0, cnt = 0; i < n; i++, cnt = 0)
		hash->Place(tr[i], 0, cnt, n);

	return *hash;
}

int main() {
	TArrayHash *hs;
	hs = new TArrayHash();
	string *t;
	t = new string[2];
	t[0] = "hello";
	t[1] = "world";
	*hs = Cuckoo(t, 2);
}
