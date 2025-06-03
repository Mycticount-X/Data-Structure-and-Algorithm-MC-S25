#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 9

struct hashNode{
	char name[20];
	int key;
};

int hashFunction(char name[]){
	//COMPLETE THE CODE
	int summa = 0;
	for (int i = 0; name[i] != '\0'; i++) {
		summa += name[i];
	} return summa % SIZE;
}

// Zone* Table[SIZE] = NULL 
// >> Muscle Memory :)

hashNode Table[SIZE];

void initTable () {
	for (int i = 0; i < SIZE; i++) {
		Table[i].key = -1;
		strcpy(Table[i].name, "");
	}
}

void Insert (char s[]) {
	int hash = hashFunction(s);
	int index = hash;
	
	while (Table[index].key != -1) {
		printf(">> Next\n");
		index = (index + 1) % SIZE;
		if (index == hash) {
			printf("Permuka-- Tabel saat ini penuh\n");
			return;
		}
	}
	
	Table[index].key = hash;
	strcpy(Table[index].name, s);
	printf("%s masuk ke Tabel no-%d\n", s, index);
}

int main () {
	initTable();
	char *testCases[] = {"yve", "pharsa", "estes", "miya", "aulus", "lylia", "gusion"};
    int n = sizeof(testCases) / sizeof(testCases[0]);
    
    for (int i = 0; i < n; i++) {
        Insert(testCases[i]);
    }
	return 0;
}


