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
void AppendZone (int MTX) {
	Zone *newZone = CreateZone(MTX);
    if (tail == NULL) {
        head = tail = newZone;
    } else {
        tail->next = newZone;
        newZone->prev = tail;
        tail = newZone;
    }
}

// Pop Command
void EnterZone() {
    if (head == NULL) {
        printf("Permukaan saat ini kosong!\n");
        return;
    }
    
    printf("Memasuki Zona!\nStatus: %d MTX\n", head->MTX);
    
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
    AppendZone(100);
	AppendZone(200);
	AppendZone(300);
	Peek();
	ViewPlane();
	EnterZone();
	Peek();
	ViewPlane();
	
	// Test Case 2
	AppendZone(10);
	AppendZone(20);
	AppendZone(30);
	ClearPlane();
	ViewPlane();

	// Test Case 3
	EnterZone();
	Peek();
	AppendZone(500);
	Peek();
	EnterZone();
	EnterZone();
    
    return 0;
}

