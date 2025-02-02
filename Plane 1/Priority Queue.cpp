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
void PushSort (int MTX) {
	Zone *newZone = CreateZone(MTX);
    if (head == NULL) {
        head = tail = newZone;
    } else if (MTX < head->MTX) {
    	newZone->next = head;
        head->prev = newZone;
        head = newZone;
	} else if (MTX > tail->MTX) {
		tail->next = newZone;
        newZone->prev = tail;
        tail = newZone;
	} else {
		Zone *curr = head->next;
		while (MTX > curr->MTX) {
			curr = curr->next;
		}
		
		curr->prev->next = newZone;
		newZone->prev = curr->prev;
		newZone->next = curr;
		curr->prev = newZone;
	}
}

// Pop Command
void PopHead() {
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
    PushSort(4567);
    PushSort(7891);
    PushSort(4567);
    PushSort(2250);
    PushSort(6600);
    PushSort(875);
    
    ViewPlane();
    
    // Test Case 2
    PopHead();
    Peek();
    ClearPlane();
    PopHead();
    Peek();
    
    // Test Case 3
    PushSort(-4234);
    PushSort(-6320);
    Peek();
	PushSort(-5780);
    Peek();
    PushSort(-5560);
	ViewPlane();
    
    return 0;
}

