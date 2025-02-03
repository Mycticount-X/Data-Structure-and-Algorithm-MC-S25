#include <stdio.h>
#include <stdlib.h>

#define TSIZE 10
#define HASH 0.264453146

struct Zone {
	int MTX;
	Zone* next;
	Zone* prev;
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

// Create Zone
Zone* CreateZone (int MTX) {
	Zone* newzone = (Zone*) malloc (sizeof(Zone));
	newzone->MTX = MTX;
	newzone->next = NULL;
	newzone->prev = NULL;
	return newzone;
}

// Insert Command
void Insert (int MTX) {
	int key = hash(MTX);
	Zone* newzone = CreateZone(MTX);
	
	if (HashTable[key] == NULL) {
        HashTable[key] = newzone;
    } else {
        newzone->next = HashTable[key];
        HashTable[key]->prev = newzone;
        HashTable[key] = newzone;
    }
}

// Delete Command
void Delete (int MTX) {
	int key = hash(MTX);
	Zone* curr = HashTable[key];
	
	while (curr != NULL && curr->MTX != MTX) {
		curr = curr->next;
	}
	
	// Not Found
	if (curr == NULL) {
		printf("Zona tidak ditemukan\n");
		return;
	}
	
	// Cek prev
	if (curr->prev != NULL) {
		curr->prev->next = curr->next;
	} else {
		HashTable[key] = curr->next;
	}
	
	// Cek next
	if (curr->next != NULL) {
		curr->next->prev = curr->prev;
	}
	
	free(curr);
	curr = NULL;
	
}

// Alter Command
void ClearPlane() {
    for (int i = 0; i < TSIZE; i++) {
        struct Zone* curr = HashTable[i];
        while (curr) {
            struct Zone* temp = curr;
            curr = curr->next;
            free(temp);
            temp = NULL;
        }
        HashTable[i] = NULL;
    }
}

void ViewPlane () {
	for (int i = 0; i < TSIZE; i++) {
		printf("HashTable[%d]: ", i);
		Zone* curr = HashTable[i];
		while (curr) {
			printf("%d <=> ", curr->MTX);
			curr = curr->next;
		}
		printf("NULL\n");
	}
}


int main () {
	initHashTable();
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
