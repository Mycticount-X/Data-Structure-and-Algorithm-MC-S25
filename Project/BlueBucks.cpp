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

struct Customer {
    char name[50];
    char phone[30];
    char email[50];
    int points;
    int spend;

    Customer* left;
    Customer* right;
};

Customer* core = NULL;

Customer* CreateCustomer(char name[], char phone[], char email[], int points, int spend) {
    Customer* newCustomer = (Customer*) malloc(sizeof(Customer));
    strcpy(newCustomer->name, name);
    strcpy(newCustomer->phone, phone);
    strcpy(newCustomer->email, email);
    newCustomer->points = points;
    newCustomer->spend = spend;

    newCustomer->left = NULL;
    newCustomer->right = NULL;
    return newCustomer;
}

// Helper Function
Customer *minCustomer(Customer *root) {
    Customer *current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Tree Function
Customer* Generate (Customer* curr, char name[], char phone[], char email[], int points, int spend) {
    if (curr == NULL) {
        core = CreateCustomer(name, phone, email, points, spend);
        return core;
    }

    if (strcmp(curr->phone, phone) > 0) {
        curr->left = Generate(curr->left, name, phone, email, points, spend);
    } else if (strcmp(curr->phone, phone) < 0) {
        curr->right = Generate(curr->right, name, phone, email, points, spend);
    } else {
        // Validasi Duplikat
        return NULL;
    }
}

Customer* Delete (Customer* curr, char name[], char phone[], char email[], int points, int spend) {
    if (curr == NULL) {
        // printf("Customer not found!\n");
        return NULL;
    }

    if (strcmp(curr->phone, phone) > 0) {
        curr->left = Delete(curr->left, name, phone, email, points, spend);
    } else if (strcmp(curr->phone, phone) < 0) {
        curr->right = Delete(curr->right, name, phone, email, points, spend);
    } else {
        // Tanpa Anak
        if (curr->left == NULL && curr->right == NULL) {
            free(curr);
            curr = NULL;
        }
        
        // Anak Satu
        else if (curr->left == NULL) {
            Customer* temp = curr;
            curr = curr->right;
            free(temp);
        } else if (curr->right == NULL) {
            Customer* temp = curr;
            curr = curr->left;
            free(temp);
        }

        // Anak Dua
        else {
            Customer* temp = minCustomer(curr->right);
            curr = temp;
            curr->right = Delete(curr->right, temp->name, temp->phone, temp->email, temp->points, temp->spend);
        }
    }
    return curr;
}

// Search Customer
Customer* Search (Customer* curr, char phone[]) {
    if (curr == NULL) {
        return NULL;
    }

    if (strcmp(curr->phone, phone) > 0) {
        return Search(curr->left, phone);
    } else if (strcmp(curr->phone, phone) < 0) {
        return Search(curr->right, phone);
    } else {
        return curr;
    }
}

// Traversal Order
void Inorder (Customer* curr) {
    if (curr == NULL) {
        return;
    }

    Inorder(curr->left);
    printf("| %-25s | %-13s | %-20s | %-6d |\n", curr->name, curr->phone, curr->email, curr->points);
    Inorder(curr->right);
}

// Helper Function
bool isNum (char phone[]) {
    int len = strlen(phone);
    for (int i = 0; i < len; i++) {
        if (phone[i] < '0' || phone[i] > '9') {
            return false;
        }
    }
    return true;
}

bool isPerson (char name[]) {
    if (strlen(name) < 3) {
        return false;
    }

    if (strncmp(name, "Mr.", 3) == 0 || strncmp(name, "Mrs.", 4) == 0) {
        return true;
    }

    return false;
}

bool isEmail(char email[]) {
    int len = strlen(email);
    if (len < 10 || len > 20) return false;

    int at = -1, dot = -1;
    int at_count = 0;

    for (int i = 0; i < len; i++) {
        if (email[i] == '@') {
            at = i;
            at_count++;
        } else if (email[i] == '.') {
            dot = i;
        }
    }

    if (at_count != 1 || at <= 0 || at >= len - 1) return false;

    if (dot <= at) return false;

    if (strcmp(email + dot, ".com") == 0 || strcmp(email + dot, ".co.id") == 0) {
        return true;
    }

    return false;
}

bool isDrink(char drink[]) {
    if (strcmpi(drink, "Cafe Latte") == 0 || strcmpi(drink, "Caramel Macchiato") == 0 || strcmpi(drink, "Cappuccino") == 0 || strcmpi(drink, "Cafe Mocha") == 0) {
        return true;
    }
    return false;
}

void refreshPoints(Customer* curr) {
    int points = (curr->spend / 50000) * 3;
    curr->spend = curr->spend % 50000;
    curr->points += points;
}

// Prototype Function
void Menu();
void InsertMenu();
void ViewMenu();
void DeleteMenu();
void ExitMenu();

int main () {
    return 0;
}

// Menu Func
void Menu () {
	int position = 0;
	char input;
	system("cls");
	while (true) {
		printf("%s Blue Bucks %s\n", CYAN, RESET);
		printf("%s 1. Process Order %s\n", (position == 0) ? ">>" : "  ", (position == 0) ? "<<" : "  ");
		printf("%s 2. View All Customer %s\n", (position == 1) ? ">>" : "  ", (position == 1) ? "<<" : "  ");
		printf("%s 3. Remove Customer %s\n", (position == 2) ? ">>" : "  ", (position == 2) ? "<<" : "  ");
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
					printf("Thank you for using Blue Bucks!\n");
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

void InsertMenu () {
    // Identitas
    char phone [50];
    do {
        printf("\n Nomor Telepon harus 10-13 karakter dan numerik\n");
        printf("Input Nomor Telepon: ");
        scanf(" %[^\n]", phone);
    } while (strlen(phone) < 10 || strlen(phone) > 13 || !isNum(phone));

    char name[50];
    do {
        printf("\n Nama harus 3-25 karakter dan di awali Mr./Mrs.\n");
        printf("Input Name: ");
        scanf(" %[^\n]", name);
    } while (strlen(name) < 5 || strlen(name) > 25 || !isPerson(name));
    
    char email[50];
    do {
        printf("\n Email harus 10-20 karakter dan sesuai format email\n");
        printf("Input Email: ");
        scanf(" %[^\n]", email);
    } while (strlen(name) < 10 || strlen(name) > 20 || isEmail(email));

    Customer* curr = Search(core, phone);
    if (curr == NULL) {
        Generate(core, name, phone, email, 0, 0);
        printf("%s (i) Customer berhasil ditambahkan%s\n", GREEN, RESET);
    } else {
        printf("%s (i) Selamat datang kembali, %s %s\n", GREEN, curr->name, RESET);
    }

    // Order Minuman
    while (true) {
        refreshPoints(curr);
        int free = curr->points / 25;
        printf("Kamu punya %d bonus minuman tersisa\n", free);
        
        char drink[50];
        do {
            printf("\nCafe Latte | Caramel Macchiato | Cappuccino | Cafe Mocha\n");
            printf("Input Drink: ");
            scanf(" %[^\n]", drink);
        } while (!isDrink(drink));

        char input[5];
        do {
            printf("\nKamu punya %d bonus minuman tersisa (%d poin)\n", free, curr->points);
            printf("Ingin menggunakan 25 poin untuk bonus minuman? [Y/N]: ");
            scanf(" %[^\n]", input);
        } while (strcmpi(input, "Y") != 0 && strcmpi(input, "N") != 0);

        if (strcmpi(input, "Y") == 0) {
            curr->points -= 25;
            printf("%s (i) Bonus minuman berhasil ditambahkan%s\n", GREEN, RESET);
        }
        printf("%s (i) Selamat menikmati minuman Anda%s\n", GREEN, RESET);

        // Validasi End
        do {
            printf("Apakah Anda ingin memesan lagi? [Y/N]: ");
            scanf(" %[^\n]", input);
        } while (strcmpi(input, "Y") != 0 && strcmpi(input, "N") != 0);

        if (strcmpi(input, "N") == 0) {
            break;
        }
    }

    printf("Press enter to continue..."); getchar();
    while (getchar() != '\n'); 
}

void ViewMenu () {
    if (core == NULL) {
        printf("Tidak ada pelanggan saat ini!\n");

        printf("Press enter to continue..."); getchar();
        while (getchar() != '\n'); 
        return;
    }
    
    printf("%s(i) Gunakan Full Screen untuk pengalaman terbaik!\n%s", YELLOW, RESET);
    printf("=============================================================================\n");
    printf("| Name                      | Phone Number  | Email                | Points |\n");
    printf("=============================================================================\n");
    
    Inorder(core);

    printf("=============================================================================\n\n");

    printf("Press enter to continue..."); 
    while (getchar() != '\n'); 
}

void DeleteMenu () {
    if (core == NULL) {
        printf("Tidak ada pelanggan saat ini!\n");

        printf("Press enter to continue..."); getchar();
        while (getchar() != '\n'); 
        return;
    }
    
    char phone[50];
    printf("Input Nomor Telepon: ");
    printf(" %[^\n]", phone);

    Customer* curr = Search(core, phone);
    if (curr == NULL) {
        printf("%s (i) Customer tidak ditemukan%s\n", RED, RESET);
    } else {
        Delete(core, curr->name, curr->phone, curr->email, curr->points, curr->spend);
        printf("%s (i) Customer berhasil dihapus%s\n", GREEN, RESET);
    }

    printf("Press enter to continue..."); getchar();
    while (getchar() != '\n');
}