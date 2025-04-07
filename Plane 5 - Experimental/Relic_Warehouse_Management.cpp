#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#define SIZE 10

typedef struct Relic {
	int MTX;
	double weight;
	struct Relic* prev;
	struct Relic* next;	
} Relic;

Relic* Table[SIZE];

Relic* Gen(int MTX, double weight) {
	Relic* relic = (Relic*) malloc(sizeof(Relic));
	relic->MTX = MTX;
	relic->weight = weight;
	relic->next = NULL;
	relic->prev = NULL;
	return relic;
}

int hashing(int MTX, double weight) {
	return (MTX + (int)weight) % SIZE;
}

void initTable() {
	for (int i = 0; i < SIZE; i++) {
		Table[i] = NULL;
	}
}

void Add(int MTX, double weight) {
	int hash = hashing(MTX, weight);
	Relic* relic = Gen(MTX, weight);

	if (Table[hash] == NULL) {
		Table[hash] = relic;
	} else {
		relic->next = Table[hash];
		Table[hash]->prev = relic;
		Table[hash] = relic;
	}
}

bool Pickup(int MTX, double weight) {
	int hash = hashing(MTX, weight);
	Relic* curr = Table[hash];

	while (curr) {
		if (curr->MTX == MTX && fabs(curr->weight - weight) < 0.01) break;
		curr = curr->next;
	}

	if (curr == NULL) {
		return false;
	}

	if (curr->prev == NULL) {
		Table[hash] = curr->next;
	} else {
		curr->prev->next = curr->next;
	}

	if (curr->next != NULL) {
		curr->next->prev = curr->prev;
	}

	free(curr);
	return true;
}

Relic* Search(int MTX, double weight) {
	int hash = hashing(MTX, weight);
	Relic* curr = Table[hash];

	while (curr) {
		if (curr->MTX == MTX && fabs(curr->weight - weight) < 0.01) break;
		curr = curr->next;
	}

	return curr;
}

void ViewWarehouse() {
	for (int i = 0; i < SIZE; i++) {
		Relic* curr = Table[i];
		printf("Slot %d:\n", i);
		while (curr) {
			printf("<=> Relic [%d MTX] [%.2lf kg]\n", curr->MTX, curr->weight);
			curr = curr->next;
		}
		printf("\n");
	}
}

void ClearWarehouse() {
	for (int i = 0; i < SIZE; i++) {
		Relic* curr = Table[i];
		while (curr) {
			Relic* temp = curr;
			curr = curr->next;
			free(temp);
		}
		Table[i] = NULL;
	}
}

int main() {
	initTable();
	// Test Case
	Add(100, 5.25);
	Add(105, 7.80);
	Add(100, 5.23);
	ViewWarehouse();

	if (Pickup(105, 7.80)) {
		printf("Relic diangkat!\n");
	} else {
		printf("Relic tidak ditemukan.\n");
	}
	
	ViewWarehouse();
	ClearWarehouse();
	return 0;
}

