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
void PushHead (int MTX) {
	Zone *newZone = CreateZone(MTX);
    if (head == NULL) {
        head = tail = newZone;
    } else {
        newZone->next = head;
        head->prev = newZone;
        head = newZone;
    }
}

void PushTail (int MTX) {
	Zone *newZone = CreateZone(MTX);
    if (tail == NULL) {
        head = tail = newZone;
    } else {
        tail->next = newZone;
        newZone->prev = tail;
        tail = newZone;
    }
}

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
    
    Zone *temp = head;
    head = head->next;
    if (head == NULL) {
        tail = NULL;
    } else {
        head->prev = NULL;
    }
    
    free(temp);
}

void PopTail() {
    if (tail == NULL) {
        printf("Permukaan saat ini kosong!\n");
        return;
    } 
    
    Zone *temp = tail;
    tail = tail->prev;
    if (tail != NULL) {
        tail->next = NULL;
    } else {
        head = NULL;
    }
    
    free(temp);
}

void PopSearch (int MTX) {
    Zone *curr = head;
    int clear = 0;
    
    while (curr != NULL) {
        if (curr->MTX == MTX) {
            clear++;
            if (curr == head) {
                PopHead();
                curr = head;
                continue;
            } else if (curr == tail) {
                PopTail();
                break;
            } else {
                Zone *temp = curr;
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                curr = curr->next;
                free(temp);
                continue;
            }
        }
        
        curr = curr->next;
    }
    
    if (clear) {
        printf("Berhasil membersihkan %d Zona!\n", clear);
    } else {
        printf("Zona dengan Konsentrasi Myctix %d tidak ditemukan!\n", MTX);
    }
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
    PushHead(550);
    PushHead(314);
    PushHead(920);
    PushTail(1125);
    PushTail(625);
    
    ViewPlane();
    ClearPlane();
    
    // Test Case 2
    PushSort(4567);
    PushSort(7891);
    PushSort(4567);
    PushSort(2250);
    PushSort(6600);
    PushSort(875);
    
    ViewPlane();
    
    // Test Case 3
    PopHead();
    PopTail();
    PopSearch(4567);
    PopSearch(875);
    ClearPlane();
    PopHead();
    PopTail();
    
    return 0;
}

