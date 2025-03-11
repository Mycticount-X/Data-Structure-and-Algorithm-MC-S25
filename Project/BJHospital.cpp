#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include <conio.h>

// Global Define
#define MENU_ITEMS 4

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
// BlueJack Hospital
struct Patient {
    char name[100];
    int age;
    char desc[100];
    int code;
    Patient *next;
    Patient *prev;
};

Patient *head = NULL;
Patient *tail = NULL;

Patient* createPatient (char name[], int age, char desc[], int code) {
    Patient *newPatient = (Patient*)malloc(sizeof(Patient));
    newPatient->age = age;
    newPatient->code = code;
    newPatient->next = NULL;
    newPatient->prev = NULL;
    strcpy(newPatient->name, name);
    strcpy(newPatient->desc, desc);
    return newPatient;
}

void PushSort (char name[], int age, char desc[], int code) {
    Patient *newPatient = createPatient(name, age, desc, code);
    if (head == NULL) {
        head = tail = newPatient;
    }
    
    // Code 1 = Red
    // Code 2 = Yellow
    // Code 3 = Green
    else if (code < head->code) {
        newPatient->next = head;
        head->prev = newPatient;
        head = newPatient;
    } else if (code > tail->code) {
        tail->next = newPatient;
        newPatient->prev = tail;
        tail = newPatient;
    } else {
        Patient *curr = head;
    
        while (curr->next && code >= curr->code) {
            curr = curr->next;
        }

        newPatient->next = curr;
        newPatient->prev = curr->prev;

        if (curr->prev) {
            curr->prev->next = newPatient;
        }
        curr->prev = newPatient;

        if (newPatient->prev == NULL) {
            head = newPatient;
        }
    }
}

void ViewPlane () {
    if (head == NULL) {
        printf("Antrian saat ini kosong!\n");
        return;
    }
    Patient *curr = head;
    int cc = 1;
    printf("==========================================================================================\n");
    printf("| No  | Nama Pasien               | Umur | Deskripsi Penyakit                  | Kode    |\n");
    printf("==========================================================================================\n");
    
    while (curr) {
        printf("| %-3d | %-25s | %-4d | %-34s | %-7s |\n"
            , cc, curr->name, curr->age, curr->desc,
            (curr->code == 1) ? "Red" : (curr->code == 2) ? "Yellow" : "Green");
        curr = curr->next;
        cc++;
    }
    
    printf("==========================================================================================\n\n");
}

void PopHead () {
    if (head == NULL) {
        printf("Antrian saat ini kosong!\n");
        return;
    }

    printf("Nama      : %s\n", head->name);
    printf("Umur      : %d\n", head->age);
    printf("Deskripsi : %s\n", head->desc);
    printf("Kode      : %s\n\n", (head->code == 1) ? "Red" : (head->code == 2) ? "Yellow" : "Green");

    Patient* temp = head;
    if (head == tail) {
        head = tail = NULL;
    } else {
        head = head->next;
        head->prev = NULL;
    }

    free(temp);
}

void InitCase () {
    // Ini TestCase Awal
    PushSort("Mikha", 20, "Jantung Koroner Varian 12B", 1);
    PushSort("Mas Joe", 32, "Sakit Ringan Katanya", 3);
    PushSort("Ahlovely", 21, "Demam Parah sampe gabisa maraton", 2);
    PushSort("May", 11, "Sekarang bukan bulan Mei", 2);
    PushSort("MTanzil", 23, "Batuk batuk", 3);
}

// Prototype Function
void Menu();
void InsertMenu();
void ViewMenu();
void PopMenu();
void ExitMenu();

int main () {
    InitCase();
    Menu();
    return 0;
}

// Menu Func
void Menu () {
	int position = 0;
	char input;
	system("cls");
	while (true) {
		printf("%s BlueJack Hospital%s\n", CYAN, RESET);
		printf("%s 1. Insert %s\n", (position == 0) ? ">>" : "  ", (position == 0) ? "<<" : "  ");
		printf("%s 2. View %s\n", (position == 1) ? ">>" : "  ", (position == 1) ? "<<" : "  ");
		printf("%s 3. Next Queue %s\n", (position == 2) ? ">>" : "  ", (position == 2) ? "<<" : "  ");
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
                    InsertMenu();
                    break;
                case 1:
                    ViewMenu();
                    break;
                case 2:
					PopMenu();
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

void InsertMenu () {
    char name[100], desc[100], code[100];
    int age;
    
    printf("Masukkan Nama Pasien [4-25]: ");
    scanf(" %[^\n]", name);

    while (strlen(name) < 4 || strlen(name) > 25) {
        printf("\nNama Pasien harus 4-25 karakter\n");
        printf("Masukkan Nama Pasien [4-25]: ");
        scanf(" %[^\n]", name);
    }

    printf("\nMasukkan Umur Pasien [>= 0]: ");
    scanf(" %d", &age);

    while (age < 0) {
        printf("\nSejak kapan ada manusia umur Negatif?!\n");
        printf("Masukkan Umur Pasien [>= 0]: ");
        scanf(" %d", &age);
    }

    printf("\nMasukan Deskripsi Penyakit [6-100]: ");
    scanf(" %[^\n]", desc);

    while (strlen(desc) < 6 || strlen(desc) > 100) {
        printf("\nDeskripsi Penyakit harus 6-100 karakter\n");
        printf("Masukan Deskripsi Penyakit [6-200]: ");
        scanf(" %[^\n]", desc);
    }

    printf("\nMasukkan Kode Penyakit [Red|Yellow|Green]: ");
    scanf(" %[^\n]", code);
    
    while (strcmpi(code, "Red") != 0 && strcmpi(code, "Yellow") != 0 && strcmpi(code, "Green") != 0) {
        printf("\nKode Penyakit harus Red, Yellow, atau Green\n");
        printf("Masukkan Kode Penyakit [Red|Yellow|Green]: ");
        scanf(" %[^\n]", code);
    }
    
    // Red = 1
    // Yellow = 2
    // Green = 3
    PushSort(name, age, desc, (strcmpi(code, "Red") == 0) ? 1 : (strcmpi(code, "Yellow") == 0) ? 2 : 3);
    
    printf("%sWelcome to BlueJack Hospital, %s!%s\n", GREEN, name, RESET);
    printf("Press enter to continue..."); getchar();
	while (getchar() != '\n');
}

void ViewMenu () {
    printf("Antrian saat ini...\n");

    ViewPlane();

    printf("Press enter to continue...");
	while (getchar() != '\n');
}

void PopMenu () {
    printf("Pasien berikutnya...\n");
    PopHead();
    printf("Press enter to continue...");
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
					printf("Thank you for using BlueJack Hospital!\n");
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
