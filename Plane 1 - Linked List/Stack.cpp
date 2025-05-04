#include <stdio.h>
#include <stdlib.h>

typedef struct Zone {
    int MTX;
    Zone *next;
    Zone *prev;
} Zone;

Zone *head = NULL, *tail = NULL;

Zone *CreateZone(int MTX) {
    Zone *newZone = (Zone*) malloc(sizeof(Zone));
    newZone->MTX = MTX;
    newZone->next = NULL;
    newZone->prev = NULL;
    return newZone;
}

// Push Command
void Push (int MTX) {
	Zone *newZone = CreateZone(MTX);
    if (head == NULL) {
        head = tail = newZone;
    } else {
        newZone->next = head;
        head->prev = newZone;
        head = newZone;
    }
}

// Pop Command
void Pop() {
    if (head == NULL) {
        printf("Permukaan saat ini kosong!\n");
        return;
    }
    
    Zone *temp = head;
    head = head->next;
    if (head == NULL) {
        tail = NULL;
    } else {
        head->prev = NULL;
    }
    
    free(temp);
}

// Peek / Peep Command
void Peek() {
	if (head == NULL) {
        printf("Permukaan saat ini kosong!\n");
        return;
    }
    
    printf("Next Zone: %d MTX\n", head->MTX);
}

// Alter Command
void ClearPlane() {
    int clear = 0;
    while (head != NULL) {
        Zone *temp = head;
        head = head->next;
        free(temp);
        clear++;
    }
    head = tail = NULL;
    printf("Berhasil membersihkan %d Zona!\n", clear);
}

void ViewPlane() {
    if (head == NULL) {
        printf("Permukaan saat ini kosong!\n");
        return;
    }
    Zone *curr = head;
    int cc = 1;
    printf("==========================\n");
    printf("     ZONA TERDAFTAR\n");
    printf("==========================\n");
    
    while (curr) {
        printf("Zone %d:\nMyctix Concentration: %d\n", cc, curr->MTX);
        printf("--------------------------\n");
        curr = curr->next;
        cc++;
    }
}

int main() {
	// Test Case 1
    Push(100);
	Push(200);
	Push(300);
	Peek();
	ViewPlane();
	Pop();
	Peek();
	ViewPlane();
	
	// Test Case 2
	Push(10);
	Push(20);
	Push(30);
	ClearPlane();
	ViewPlane();

	// Test Case 3
	Pop();
	Peek();
	Push(500);
	Peek();
	Pop();
	Pop();
    
    return 0;
}

