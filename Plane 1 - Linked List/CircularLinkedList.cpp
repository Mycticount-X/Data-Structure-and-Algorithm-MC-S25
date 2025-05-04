#include <stdio.h>
#include <stdlib.h>

// Data Structure with MX
struct Zone {
	int MTX;
	Zone* next;
	Zone* prev;
};

Zone* head = NULL;
Zone* tail = NULL;

Zone* CreateZone (int MTX) {
	Zone* newzone = (Zone*) malloc(sizeof(Zone));
	newzone->MTX = MTX;
	newzone->next = NULL;
	newzone->prev = NULL;	
	return newzone;
}

// Push Command
void PushHead(int MTX) {
    Zone* newzone = CreateZone(MTX);
    
    if (head == NULL) {
        head = tail = newzone;
        head->next = head;
        head->prev = head;
    } else {
        tail->next = newzone;
        newzone->prev = tail;
        newzone->next = head;
        head->prev = newzone;
        head = newzone;
    }
}

void PushSort (int MTX) {
	Zone* newzone = CreateZone(MTX);
	
	if (head == NULL) {
		head = tail = newzone;
        head->next = head;
        head->prev = head;
		return;
		
	} else if (MTX < head->MTX) {
		tail->next = newzone;
        newzone->prev = tail;
        newzone->next = head;
        head->prev = newzone;
        head = newzone;
        return;
        
	} else if (MTX > tail->MTX) {
		tail->next = newzone;
        newzone->prev = tail;
        newzone->next = head;
        head->prev = newzone;
        tail = newzone;
        return;
	}
	
	Zone* curr = head->next;
	while (curr != head && MTX > curr->MTX) {
		curr = curr->next;
	}
	
	curr->prev->next = newzone;
	newzone->prev = curr->prev;
	newzone->next = curr;
	curr->prev = newzone;
	
}

// Pop Command
void PopHead() {
    if (head == NULL) {
        printf("Permukaan saat ini kosong!\n");
        return;
    }

    Zone* del = head;

    if (head == tail) {
        head = tail = NULL;
    } else {
        head = head->next;
        head->prev = tail;
        tail->next = head;
    }

    free(del);
    del = NULL;
}

void PopSearch (int MTX) {
	if (head == NULL) {
        printf("Permukaan saat ini kosong!\n");
        return;
    }
    
    Zone* del = head;
    if (head->MTX == MTX) {
    	if (head == tail) {
    		free(del);
	        head = tail = NULL;
	    } else {
	        head = head->next;
	        head->prev = tail;
	        tail->next = head;
	        free(del);
	    }
	    del = NULL;
	    printf("Zona berhasil dihapus!\n");
        return;
	}
	
    
    del = head->next;
    while (del != head && del->MTX != MTX) {
        del = del->next;
    }
    
    if (del->MTX == MTX) {
    	if (del == tail) {
            tail = tail->prev;
        }
        
        del->next->prev = del->prev;
        del->prev->next = del->next;

        free(del);
        printf("Zona berhasil dihapus!\n");
	} else {
		printf("Zona tidak diteukan!\n");
	}
}

// Alter Command
void ViewPlane () {
	if (head == NULL) {
		printf("Permukaan saat ini kosong!\n");
		return;
	}
	
	Zone* curr = head;
	int cc = 1;
    printf("==========================\n");
    printf("      ZONA TERDAFTAR\n");
    printf("==========================\n");
    
	do {
		printf("Zone: %d\nMyctix Consentration: %d\n", cc, curr->MTX);
		printf("--------------------------\n");
		curr = curr->next;
		++cc;
	} while (curr != head);
}

void ClearPlane () {
	if (head == NULL) {
		printf("Permukaan saat ini kosong!\n");
		return;
	}
	
	Zone* curr = head;
	Zone* next;
	int cc = 0;
	
	do {
		next = curr->next;
		free(curr);
		curr = next;
		++cc;
	} while (curr != head);
	
	head = tail = NULL;
	printf("Berhasil Menghapus %d Zona!\n", cc);
}

int main () {
	// Test Case 1
	PushHead(23);
	PushHead(53);
	PushHead(77);
	ViewPlane();
	ClearPlane();
	ViewPlane();
	
	// Test Case 2
	PushSort(50);
	PushSort(20);
	PushSort(80);
	PushSort(40);
	PushSort(60);
	ViewPlane();
	PopSearch(10);
	PopSearch(40);
	PopSearch(50);
	PopSearch(20);
	PopSearch(60);
	PopSearch(80);
	PopSearch(10);
	ViewPlane();
	
	// Test Case 3
	PushSort(50);
	PushSort(20);
	PushSort(80);
	PushSort(40);
	PushSort(60);
	ViewPlane();
	PopSearch(20);  // Hapus head
	ViewPlane();
	PopSearch(80);  // Hapus tail
	ViewPlane();


	return 0;
}
