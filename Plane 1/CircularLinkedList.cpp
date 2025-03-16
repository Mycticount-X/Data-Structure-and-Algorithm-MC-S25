#include <stdio.h>
#include <stdlib.h>

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
}

void PushHead (int MTX) {
	Zone* newzone = CreateZone(MTX);
	
	if (head == NULL) {
		head = tail = newzone;
		head->next = head;
		head->prev = head;
	}
	
	else if (head == tail) {
		head->next = newzone;
		tail = newzone;
		tail->next = head;
		tail->prev = head;
	}
	
	else {
		head->prev = newzone;
		newzone->next = head;
		head = newzone;
		tail->next = head;
		head->prev = tail;
	}
}

void PopHead () {
	if (head == NULL) {
		printf("Permukaan saat ini kosong!\n");
		return;
	}
	
	else if (head == tail) {
		free(head);
		head = tail = NULL;
		return;
	}
	
	Zone* del = head;
	head = head->next;
	
	// Sisa 2 Zone
	if (head == tail) {
		head->next = head;
		head->prev = head;
	} else {
		head->prev = tail;
		tail->next = head;
	}
	
	free(del);
	del = NULL;
}

int main () {
	return 0;
}