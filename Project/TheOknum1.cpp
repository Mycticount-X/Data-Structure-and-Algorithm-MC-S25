#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXOK 100

struct Oknum {
	char name[101];
	int palak;
	int jarak;
};

Oknum Heap[MAXOK];
int size = 0;

void swap (Oknum* a, Oknum* b) {
	Oknum t = *a;
	*a = *b;
	*b = t;
}

void MinHeapify (int i) {
	int min = i;
	int left = i*2+1;
	int right = i*2+2;
	
	if (left < size && (Heap[left].palak < Heap[min].palak ||
	(Heap[left].palak == Heap[min].palak && Heap[left].jarak < Heap[min].jarak)) ) {
		min = left;
	}
	if (right < size && (Heap[right].palak < Heap[min].palak ||
	(Heap[right].palak == Heap[min].palak && Heap[right].jarak < Heap[min].jarak)) ) {
		min = right;
	} 
	
	if (min != i) {
		swap(&Heap[i], &Heap[min]);
		MinHeapify(min);
	}
}

void Generate (char name[], int palak, int jarak) {
	if (size >= MAXOK) {
		printf("Heap penuh!\n");
		return;
	}
	
	int i = size++;
	Heap[i].jarak = jarak;
	Heap[i].palak = palak;
	strcpy(Heap[i].name, name);
	
	printf("Menambahkan %s ke dalam daftar target\n", name);
	
	while (i != 0 && (
	Heap[(i - 1)/2].palak > Heap[i].palak || 
	(Heap[(i-1)/2].palak == Heap[i].palak && Heap[(i-1)/2].jarak > Heap[i].jarak) )) {
		swap(&Heap[i], &Heap[(i-1)/2]);
		i = (i-1)/2;
	}
}

void ExtractMin () {
	if (size == 0) {
		printf("Heap Kosong!\n");
		return;
	}
	
	if (size == 1) {
		size--;
		printf("Menangkap %s\n", Heap[0].name);
		return;
	}
	
	printf("Menangkap %s\n", Heap[0].name);
	Heap[0] = Heap[size-1];
	size--;
	MinHeapify(0);
}

int Search (char name[]) {
	for (int i = 0; i < size; i++) {
		if (strcmp(name, Heap[i].name) == 0) {
			return i;
		}
	} return -1;
}

void Delete (char name[]) {
	int index = Search(name);
	if (index == -1) {
		printf("Preman Tidak Ditemukan!\n");
		return;
	}
	
	Heap[index] = Heap[size];
	size--;
	MinHeapify(0);
}

void Manage (char input[]) {
	char name[51];
	int palak, jarak;
	if (strcmp(input, "A") == 0) {
		scanf(" %s %d %d", name, &palak, &jarak);
		Generate(name, palak, jarak);
		
	} else if (strcmp(input, "E") == 0) {
		int x; scanf("%d", &x);
		while (x--) {
			ExtractMin();
		}
		
	} else if (strcmp(input, "D") == 0) {
		scanf("%s", name);
		Delete(name);
		
	} else if (strcmp(input, "X") == 0) {
		while (size > 0) {
			ExtractMin();
		}
		
	} else {
		printf("Invalid Input");
	}
}

void Solver () {
	int x;
	scanf("%d", &x);
	char input[51];
	
	for (int i = 0; i < x; i++) {
		scanf(" %s", input);
		Manage(input);
	}
}

int main () {
	Solver();
	return 0;
}

