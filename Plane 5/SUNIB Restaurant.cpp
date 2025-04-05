#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// Atribut ANSI
#define RESET   "\033[0m"  // Buat reset akhiran
#define RED     "\033[31m"       
#define GREEN   "\033[32m"  
#define YELLOW  "\033[33m"   
#define BLUE    "\033[34m"   
#define MAGENTA "\033[35m"   
#define CYAN    "\033[36m"  
#define WHITE   "\033[37m" 

struct Customer {
	int member;
	char name[100];
	Customer *next;
	Customer *prev;
};

Customer* head = NULL;
Customer* tail = NULL;

Customer* Generate (char name[], int member) {
	Customer* zone = (Customer*) malloc (sizeof(Customer));
	zone->member = member;
	strcpy(zone->name, name);
	zone->next = NULL;
	zone->prev = NULL;
	return zone;
}

void AddSort (char name[], int member) {
	Customer* cus = Generate(name, member);
	
	if (head == NULL) {
		head = tail = cus;
	} else if (member > head->member) {
		head->prev = cus;
		cus->next = head;
		head = cus;
	} else if (member <= tail->member) {
		tail->next = cus;
		cus->prev = tail;
		tail = cus;
	} else {
		Customer* curr = head;
		
		while (curr && member <= curr->member) {
			curr = curr->next;
		}
		
		curr->prev->next = cus;
		cus->prev = curr->prev;
		curr->prev = cus;
		cus->next = curr;
	}
}

void PopHead () {
	if (head == NULL) {
		printf("Current Queue is Empty\n");
		return;
	}
	
	switch (head->member) {
		case 0:
			printf("Attention! Guest %s is being served at a regular table.\n", head->name);
			break;
		case 1:
			printf("Attention! Member %s is being served at regular table.\n", head->name);
			break;
		case 2:
			printf("Attention! %s is being served at the VIP table.\n", head->name);
			break;
		case 3:
			printf("Attention! %s is being served at VVIP table.\n", head->name);
			break;
		default:
			printf("Invalid Membership. Debug!!\n");
	}
	
	if (head == tail) {
		head = tail = NULL;
	} else {
		Customer* temp = head;
		head = head->next;
		free(temp);
		temp = NULL;
	}
}

void ClearPlane () {
	int clear = 0;
    while (head != NULL) {
        Customer *temp = head;
        head = head->next;
        free(temp);
        clear++;
    }
    head = tail = NULL;
    printf("End of the Day! %d Customer kecewa!\n", clear);
}

void ViewPlane () {
	if (head == NULL) {
		printf(" Queue is Empty\n");
		return;
	}
	
	printf("Waiting List:\n");
	Customer* curr = head;
	int cc = 1;
	
	while (curr) {
		printf("%d. %s\n", cc, curr->name);
		curr = curr->next; cc++;
	}
	printf("\n");
}

// Menu Command
void Menu ();

int main () {
	Menu();
	return 0;
}


void Menu () {
	int position = 0;
	char input;
	system("cls");
	while (true) {
		printf("%s Welcome to SUNIB Restaurant%s\n", CYAN, RESET);
		ViewPlane();
		
		printf("%s 1. Add Customer to Queue %s\n", (position == 0) ? ">>" : "  ", (position == 0) ? "<<" : "  ");
		printf("%s 2. Serve One %s\n", (position == 1) ? ">>" : "  ", (position == 1) ? "<<" : "  ");
		printf("%s 3. Serve All %s\n", (position == 2) ? ">>" : "  ", (position == 2) ? "<<" : "  ");
		printf("%s 4. Dismiss Queue %s\n", (position == 3) ? ">>" : "  ", (position == 3) ? "<<" : "  ");
		printf("%s 5. Dismiss Queue %s\n", (position == 4) ? ">>" : "  ", (position == 4) ? "<<" : "  ");
        printf("\nGunakan [W] dan [S] untuk Navigasi");
		input = _getch();
		system("cls");
        if (input == 'w' || input == 'W') {
            if (position > 0) {
                position--;
            }
        } else if (input == 's' || input == 'S') {
            if (position < (5) - 1) {
                position++;
            }
        } else if (input == '\r') {
            switch (position) {
                case 0:
//                    FogMenu();
                    break;
                case 1:
//                    MyxMenu();
                    break;
                case 2:
					// PopMenu();
                    break;
                case 3:
					// ExitMenu();
					break;
				default:
					// Buat Penanda kalo ada Error
					printf("Out of Index!\n");
					break;
            }
        }
        
        system("cls");
	}
}
