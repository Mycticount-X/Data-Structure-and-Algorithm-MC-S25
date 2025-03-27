#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Movie {
	char name[100];
	char genre[100];
	char alter[100];
	int time;
	Movie* next;
	Movie* prev;
};

Movie* head = NULL;
Movie* tail = NULL;
Movie* headw = NULL;
Movie* tailw = NULL;

void lower (char* str) {
	while (*str) {
		if (*str >= 'A' && *str <= 'Z') {
			*str += 32;
		}
		str++;
	}
}

Movie* Generate (char name[], char genre[], char alter[], int time) {
	Movie* mov = (Movie*) malloc (sizeof(Movie));
	strcpy(mov->name, name);
	strcpy(mov->genre, genre);
	strcpy(mov->alter, alter);
	mov->time = time;
	mov->next = NULL;
	mov->prev = NULL;
	return mov;
}

void Insert (char name[], char genre[], int time) {
	char alter[100];
	strcpy(alter, name);
	lower(alter);
	
	Movie* mov = Generate(name, genre, alter, time);
	
	if (head == NULL) {
		head = tail = mov;
	} else if (strcmp(alter, head->alter) < 0) {
		mov->next = head;
		head->prev = mov;
		head = mov;
	} else if (strcmp(alter, tail->alter) >= 0) {
		mov->prev = tail;
		tail->next = mov;
		tail = mov;
	} else {
		Movie* curr = head;
		while (curr && (strcmp(alter, curr->alter) > 0)) {
			curr = curr->next;
		}
		
		mov->next = curr;
		mov->prev = curr->prev;
		curr->prev->next = mov;
		curr->prev = mov;
	}
}

void InsertLater (char name[], char genre[], int time) {
	char alter[100];
	strcpy(alter, name);
	lower(alter);
	
	Movie* mov = Generate(name, genre, alter, time);
	
	if (headw == NULL) {
		headw = tailw = mov;
	} else if (strcmp(alter, headw->alter) < 0) {
		mov->next = headw;
		headw->prev = mov;
		headw = mov;
	} else if (strcmp(alter, tailw->alter) >= 0) {
		mov->prev = tailw;
		tailw->next = mov;
		tailw = mov;
	} else {
		Movie* curr = headw;
		while (curr && (strcmp(alter, curr->alter) > 0)) {
			curr = curr->next;
		}
		
		mov->next = curr;
		mov->prev = curr->prev;
		if (curr->prev) curr->prev->next = mov;
		else headw = mov;
		curr->prev = mov;
	}
}

void Play () {
	if (head == NULL) {
		printf("Main Playlist is Empty\n");
		return;
	}
	
	printf("WATCHED: %s %s %d\n", head->name, head->genre, head->time);
	
	if (head == tail) {
		free(head);
		head = tail = NULL;
	} else {
		Movie* temp = head;
		head = head->next;
		free(temp);
		temp = NULL;
	}
}

void Merge () {
	if (headw == NULL) {
		printf("Watch Later Playlist is Empty\n");
		return;
	}
	
	Movie* curr = headw;
	while (curr) {
        Insert(curr->name, curr->genre, curr->time);
        Movie* temp = curr;
        curr = curr->next;
        free(temp);
    }
	
	headw = tailw = NULL;
}

void ViewPlane () {
	if (head == NULL) {
		printf("Main Playlist is Empty\n");
		return;
	}
	
	Movie* curr = head;
	while (curr) {
		printf("%s %s %d\n", curr->name, curr->genre, curr->time);
		curr = curr->next;
	}
}

void ViewLater () {
	if (headw == NULL) {
		printf("Main Playlist is Empty\n");
		return;
	}
	
	Movie* curr = headw;
	while (curr) {
		printf("%s %s %d\n", curr->name, curr->genre, curr->time);
		curr = curr->next;
	}
}

void ClearPlane () {
	if (head) {
		Movie* curr = head;
		while (curr) {
			Movie* temp = curr;
	        curr = curr->next;
	        free(temp);
		}
		
		head = tail = NULL;
	}
	
	if (headw) {
		Movie* curr = headw;
		while (curr) {
			Movie* temp = curr;
	        curr = curr->next;
	        free(temp);
		}
		
		headw = tailw = NULL;
	}
	
	printf("Plane Clear\n");
}

bool Manage (char input[]) {
	char name[100], genre[100];
	int time;
	lower(input);
	if (strcmp(input, "insert_main") == 0) {
		scanf(" %s %s %d", name, genre, &time);
		Insert(name, genre, time);
		
	} else if (strcmp(input, "insert_watch_later") == 0) {
		scanf(" %s %s %d", name, genre, &time);
		InsertLater(name, genre, time);
		
	} else if (strcmp(input, "play") == 0) {
		Play();
		
	} else if (strcmp(input, "merge") == 0) {
		Merge();
		
	} else if (strcmp(input, "display_main") == 0) {
		ViewPlane();
		
	} else if (strcmp(input, "display_watch_later") == 0) {
		ViewLater();
		
	} else if (strcmp(input, "stop") == 0) {
		ClearPlane();
		return true;
		
	} else {
		printf("Invalid Input!\n");
	}
	
	return false;
}

void Menu () {
	char input[100];
	bool stop;
	while (true) {
		scanf(" %[^\n]", input);
		stop = Manage(input);
//		printf("Loop\n");
		if (stop) break;
	}
}

int main () {
	Menu();
	return 0;
}
