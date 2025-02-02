#include <stdio.h>
#include <stdlib.h>

typedef struct Zone {
    int MTX;
    struct Zone *next;
} Zone;

Zone *head = NULL, *tail = NULL;

Zone *CreateZone(int MTX) {
    Zone *newZone = (Zone*) malloc(sizeof(Zone));
    newZone->MTX = MTX;
    newZone->next = NULL;
    return newZone;
}

// Push Command
void PushHead(int MTX) {
    Zone *newZone = CreateZone(MTX);
    if (head == NULL) {
        head = tail = newZone;
    } else {
        newZone->next = head;
        head = newZone;
    }
}

void PushTail(int MTX) {
    Zone *newZone = CreateZone(MTX);
    if (tail == NULL) {
        head = tail = newZone;
    } else {
        tail->next = newZone;
        tail = newZone;
    }
}

void PushSort(int MTX) {
    Zone *newZone = CreateZone(MTX);
    if (head == NULL) {
        head = tail = newZone;
    } else if (head->MTX >= MTX) {
        newZone->next = head;
        head = newZone;
    } else if (tail->MTX <= MTX) {
        tail->next = newZone;
        tail = newZone;
    } else {
        Zone *back = head;
        Zone *curr = head->next;
        while (curr != NULL && curr->MTX < MTX) {
            back = curr;
            curr = curr->next;
        }
        back->next = newZone;
        newZone->next = curr;
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
    free(temp);
    if (head == NULL) tail = NULL;
}

void PopTail() {
    if (head == NULL) {
        printf("Permukaan saat ini kosong!\n");
        return;
    }
    if (head == tail) {
        free(head);
        head = tail = NULL;
        return;
    }
    Zone *curr = head;
    while (curr->next != tail) {
        curr = curr->next;
    }
    free(tail);
    tail = curr;
    tail->next = NULL;
}

void PopSearch(int MTX) {
    Zone *back = NULL;
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
                back->next = curr->next;
                curr = curr->next;
                free(temp);
                continue;
            }
        }
        back = curr;
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
    tail = NULL;
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
    printf("    ZONA TERDAFTAR\n");
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

