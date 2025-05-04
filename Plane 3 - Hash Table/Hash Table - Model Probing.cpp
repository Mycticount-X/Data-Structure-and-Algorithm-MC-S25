#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TSIZE 10
#define HASH 0.264453146

struct Zone {
	int MTX;
	bool occ;
};

Zone HashTable [TSIZE];

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


// Init HashTable dan Create Zone - Tidak Terpakai
// Karena bkn pake Pointer of Zone

// Insert Command
void Insert (int MTX) {
	int key = hash(MTX);
	int idx = key;
	
	for (int i = 0; i < TSIZE; i++) {
		if (HashTable[idx].occ == false) {
			HashTable[idx].MTX = MTX;
			HashTable[idx].occ = true;
			return;
		}
		idx = (key + i) % TSIZE;
	}
	printf("Permukaan saat ini penuh\n");
}

// Delete Command
void Delete (int MTX) {
	int key = hash(MTX);
	int idx = key;
	
	for (int i = 0; i < TSIZE; i++) {
		if (HashTable[idx].occ == true && HashTable[idx].MTX == MTX) {
			HashTable[idx].MTX = 0;
			HashTable[idx].occ = false;
			return;
		}
		idx = (key + i) % TSIZE;
	}
	printf("Zona tidak ditemukan\n");
	
}

// Alter Command
void ClearPlane() {
    for (int i = 0; i < TSIZE; i++) {
        HashTable[i].MTX = 0;
		HashTable[i].occ = false;
    }
}

void ViewPlane () {
	for (int i = 0; i < TSIZE; i++) {
		if (HashTable[i].occ) {
            printf("HashTable[%d]: %d\n", i, HashTable[i].MTX);
        } else {
            printf("HashTable[%d]: NULL\n", i);
        }
	}
}


int main () {
    Insert(15);
    Insert(25);
    Insert(35);
    Insert(45);
    Insert(5);
    
    printf("Hash Table after insertion:\n");
    ViewPlane();
    
    Delete(25);
    printf("\nHash Table after deletion of 25:\n");
    ViewPlane();
    
    printf("\nClearing Hash Table:\n");
    ClearPlane();
    ViewPlane();
    
    // Test cases
    printf("\nTest Case 1: Insert and clear\n");
    Insert(10);
    Insert(20);
    ViewPlane();
    ClearPlane();
    ViewPlane();
    
    printf("\nTest Case 2: Insert, delete, and clear\n");
    Insert(30);
    Insert(40);
    Delete(30);
    ViewPlane();
    ClearPlane();
    ViewPlane();
    
    printf("\nTest Case 3: Clear empty table\n");
    ClearPlane();
    ViewPlane();
	return 0;
}
