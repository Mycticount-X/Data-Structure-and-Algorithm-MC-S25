#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include <conio.h>

// Global Define
#define MENU_ITEMS 4
#define TSIZE 1007

// Atribut ANSI
#define RESET   "\033[0m"  // Buat reset akhiran
#define RED     "\033[31m"       
#define GREEN   "\033[32m"  
#define YELLOW  "\033[33m"   
#define BLUE    "\033[34m"   
#define MAGENTA "\033[35m"   
#define CYAN    "\033[36m"  
#define WHITE   "\033[37m" 

// By Michael Ahlovely Stevenson
// BlueJack Library
struct Zone {
	char id[40];
    char name[100];
    char author[40];
    char isbn[40];
    int pages;
	Zone* next;
	Zone* prev;
};

Zone* HashTable [TSIZE];
int bookcc = 0;

// Saya menggunakan Polynomial Rolling Hash
int hash(char id[]) {
    long long sum = 0;
    int prime = 31;
    for (int i = 0; id[i] != '\0'; i++) {
        sum = (sum * prime + id[i]) % TSIZE;
    }
    return (int)sum;
}


void initHashTable () {
	for (int i = 0; i < TSIZE; i++) {
		HashTable[i] = NULL;
	}
}

// Create Zone
Zone* CreateZone (char id[], char name[], char author[], char isbn[], int pages) {
	Zone* newzone = (Zone*) malloc (sizeof(Zone));
    strcpy(newzone->id, id);
    strcpy(newzone->name, name);
    strcpy(newzone->author, author);
    strcpy(newzone->isbn, isbn);
    newzone->pages = pages;
	newzone->next = NULL;
	newzone->prev = NULL;
	return newzone;
}

// Insert Command
void Insert (char id[], char name[], char author[], char isbn[], int pages) {
    int key = hash(id);
	Zone* newzone = CreateZone(id, name, author, isbn, pages);
	
	if (HashTable[key] == NULL) {
        HashTable[key] = newzone;
    }

    // Agar Insert lebih cepat saya Push di Depan
    else {
        newzone->next = HashTable[key];
        HashTable[key]->prev = newzone;
        HashTable[key] = newzone;
    }

    // Jika ingin Push di Belakang:
    // else {
    //     Zone* temp = HashTable[key];
    //     while (temp->next != NULL) {
    //         temp = temp->next;
    //     }
    //     temp->next = newzone;
    //     newzone->prev = temp;
    // }
}

// Delete Command
bool Delete (char id[]) {
    int key = hash(id);
	Zone* curr = HashTable[key];
	
	while (curr != NULL && strcmp(curr->id, id) != 0) {
		curr = curr->next;
	}
	
	// Not Found
	if (curr == NULL) {
		return false;
	}
	
	// Cek prev
	if (curr->prev != NULL) {
		curr->prev->next = curr->next;
	} else {
		HashTable[key] = curr->next;
	}
	
	// Cek next
	if (curr->next != NULL) {
		curr->next->prev = curr->prev;
	}
	
	free(curr);
	curr = NULL;
	
    return true;
}

// Alter Command
void ClearPlane() {
    for (int i = 0; i < TSIZE; i++) {
        struct Zone* curr = HashTable[i];
        while (curr) {
            struct Zone* temp = curr;
            curr = curr->next;
            free(temp);
            temp = NULL;
        }
        HashTable[i] = NULL;
    }
    bookcc = 0;
}


// Helper Function
bool isUnique (char name[]) {
    for (int i = 0; i < TSIZE; i++) {
        struct Zone* curr = HashTable[i];
        while (curr) {
            if (strcmp(curr->name, name) == 0) {
                return false;
            }
            curr = curr->next;
        }
    }
    return true;
}

bool isAuthor (char name[]) {
    if (strlen(name) < 3) {
        return false;
    }

    if (strncmp(name, "Mr.", 3) == 0 || strncmp(name, "Mrs.", 4) == 0) {
        return true;
    }

    return false;
}

bool isNum (char isbn[]) {
    int len = strlen(isbn);
    for (int i = 0; i < len; i++) {
        if (isbn[i] < '0' || isbn[i] > '9') {
            return false;
        }
    }
    return true;
}

bool isNotEmpty (){
    for (int i = 0; i < TSIZE; i++) {
        if (HashTable[i] != NULL) {
            return true;
        }
    }
    return false;
}

// Prototype Function
void Menu();
void ViewMenu();
void InsertMenu();
void DeleteMenu();
void ExitMenu();

int main () {
	initHashTable();

    // Test Init
    char id[40] = "B00001-23456789012-ML";
    char name[100] = "Legend of Sacred Master";
    char author[40] = "Mr. Mikhail Cychael";
    char isbn[40] = "23456789012";
    int pages = 100; bookcc++;
    Insert(id, name, author, isbn, pages);

    // Start Menu
    Menu ();
	return 0;
}


// Menu Func
void Menu () {
	int position = 0;
	char input;
	system("cls");
	while (true) {
		printf("%s BlueJack Library%s\n", CYAN, RESET);
		printf("%s 1. View Book %s\n", (position == 0) ? ">>" : "  ", (position == 0) ? "<<" : "  ");
		printf("%s 2. Insert Book %s\n", (position == 1) ? ">>" : "  ", (position == 1) ? "<<" : "  ");
		printf("%s 3. Remove Book %s\n", (position == 2) ? ">>" : "  ", (position == 2) ? "<<" : "  ");
		printf("%s 4. Exit %s\n", (position == 3) ? ">>" : "  ", (position == 3) ? "<<" : "  ");
        printf("\nGunakan [W] dan [S] untuk Navigasi");
		input = _getch();
		system("cls");
        if (input == 'w' || input == 'W') {
            if (position > 0) {
                position--;
            }
        } else if (input == 's' || input == 'S') {
            if (position < MENU_ITEMS - 1) {
                position++;
            }
        } else if (input == '\r') {
            switch (position) {
                case 0:
                    ViewMenu();
                    break;
                case 1:
                    InsertMenu();
                    break;
                case 2:
					DeleteMenu();
                    break;
                case 3:
					ExitMenu();
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

void ViewMenu () {
    if (!isNotEmpty()) {
        printf("%s(i) Tidak ada buku yang tersedia%s\n", RED, RESET);
        printf("Press enter to continue...");
        while (getchar() != '\n');
        return;
    }
    
    printf("%s(i) Gunakan Full Screen untuk pengalaman terbaik!\n%s", YELLOW, RESET);
    printf("=================================================================================================================================================\n");
    printf("| Book ID                        | Book Title                                         | Book Author               | ISBN          | Page Number |\n");
    printf("=================================================================================================================================================\n");
    for (int i = 0; i < TSIZE; i++) {
        struct Zone* curr = HashTable[i];
        while (curr) {
            printf("| %-30s | %-50s | %-25s | %-13s | %-11d |\n",
                curr->id, curr->name, curr->author, curr->isbn, curr->pages);
            curr = curr->next;
        }
    }
    printf("=================================================================================================================================================\n\n");

    printf("Press enter to continue...");
    while (getchar() != '\n');
}

void InsertMenu () {
    char id[40];
    char name[100];
    char author[40];
    char isbn[40];
    int pages;

    do {
        printf("\nNama Buku harus 5-50 karakter dan unik\n");
        printf("Masukkan Nama Buku [5-50]: ");
        scanf(" %[^\n]", name);
    } while (strlen(name) < 5 || strlen(name) > 50 || !isUnique(name)); 
    
    do {
        printf("\nPenulis harus 3-25 karakter dan dimulai dengan [Mr.] atau [Mrs.]\n");
        printf("Masukkan Penulis [3-25]: ");
        scanf(" %[^\n]", author);
    } while (strlen(author) < 3 || strlen(author) > 25 || !isAuthor(author));

    do {
        printf("\nISBN harus 10-13 karakter dan berupa numerik\n");
        printf("Masukkan ISBN [10-13]: ");
        scanf(" %[^\n]", isbn);
    } while (strlen(isbn) < 10 || strlen(isbn) > 13 || !isNum(isbn));

    do {
        printf("\nJumlah Halaman harus 16 atau lebih\n");
        printf("Masukkan Jumlah Halaman: "); scanf("%d", &pages);
    } while (pages < 16);

    // ID = BXXXXX-ISBN-AuthorName
    bookcc++;
    sprintf(id, "B%05d-%s-%c%c", bookcc, isbn, author[0], name[0]);

    Insert(id, name, author, isbn, pages);

    printf("%s\n(i) Buku berhasil ditambahkan%s\n", GREEN, RESET);
    printf("Press enter to continue..."); getchar();
    while (getchar() != '\n');
}

void DeleteMenu () {
    char id[40];
    printf("Input ID Buku yang ingin dihapus: ");
    scanf(" %[^\n]", id);
    
    if (Delete(id)) {
        printf("%s (i) Buku berhasil dihapus%s\n", GREEN, RESET);
    } else {
        printf("%s (i) Buku tidak ditemukan%s\n", RED, RESET);
    }

    printf("Press enter to continue..."); getchar();
    while (getchar() != '\n');
}

void ExitMenu () {
	int position = 0;
	char input;
	while (true) {
		printf(" %sAre you sure want to exit?%s\n", BLUE, RESET);
		printf("%s 1. Yes %s\n", (position == 0) ? ">>" : "  ", (position == 0) ? "<<" : "  ");
		printf("%s 2. No %s\n", (position == 1) ? ">>" : "  ", (position == 1) ? "<<" : "  ");
		input = _getch();
		system("cls");
		if (input == 'w' || input == 'W') {
			if (position > 0) {
				position--;
			}
		} else if (input == 's' || input == 'S') {
			if (position < 1) {
				position++;
			}
		} else if (input == '\r') {
			switch (position) {
				case 0:
					printf("Thank you for using BlueJack Library!\n");
					printf("Have a nice day :)\n\n");
					Sleep(1000);

					printf("%sCreator:%s\n", MAGENTA, RESET);
					printf("Name: Michael AS\n");
					printf("Github: Mycticount-X\n");
					printf("Youtube: Mycticount X\n");
					printf("HSR: 825019617\n");
					exit(0);
					break;
				case 1:
					return;
				default:
					// Buat Penanda kalo ada Error
					printf("Out of Index!\n");
					break;
			}
		}
	}

}
