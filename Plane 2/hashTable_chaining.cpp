#include <stdio.h>
#include <stdlib.h>

#define TSIZE 10
#define HASH 0.264453146

struct Zone {
	int MTX;
	Zone* next;
};

Zone* HashTable [TSIZE];

// Polynomial Rolling Hash
int hash (int x) {
	int base = 31;
    int mod = TSIZE;
    int key = 0;
    while (x > 0) {
        key = (key * base + (x % 10)) % mod;
        x /= 10;
    }
    return key;
}

void initHashTable () {
	for (int i = 0; i < TSIZE; i++) {
		HashTable[i] = NULL;
	}
}

Zone* CreateZone (int MTX) {
	Zone* newzone = (Zone*) malloc (sizeof(Zone));
	newzone->MTX = MTX;
	newzone->next = NULL;
	return newzone;
}

void Insert (int MTX) {
	int key = hash(MTX);
	Zone* newzone = CreateZone(MTX);
	newzone->next = HashTable[key];
}

void Delete (int MTX) {
	
}

int main () {
	
	return 0;
}
