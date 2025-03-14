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
        return CreateCustomer(name, phone, email, points, spend);
    }

    if (strcmp(curr->phone, phone) > 0) {
        curr->left = Generate(curr->left, name, phone, email, points, spend);
    } else if (strcmp(curr->phone, phone) < 0) {
        curr->right = Generate(curr->right, name, phone, email, points, spend);
    }

    return curr;
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

    int at = -1, dot = -1; // @ dan .
    int at_count = 0;

    for (int i = 0; i < len; i++) {
        if (email[i] == '@') {
            at = i;
            at_count++;
        } else if (email[i] == '.' && dot == -1) {
            dot = i;
        }
    }

    if (at_count != 1 || at <= 0 || at >= len - 1) return false;
    
    if (dot <= at) return false;
    // printf("%s\n", email + dot);
    
    if (strcmp(email + dot, ".com") == 0 || strcmp(email + dot, ".co.id") == 0) {
        return true;
    }
    // printf("Debugg\n");

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
void OrderMenu(Customer* curr);
void ViewMenu();
void DeleteMenu();
void ExitMenu();

int main () {
    Menu ();
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
        printf("\n%s(i) Nomor Telepon harus 10-13 karakter dan numerik%s\n", YELLOW, RESET);
        printf("Input Nomor Telepon: ");
        scanf(" %[^\n]", phone);
    } while (strlen(phone) < 10 || strlen(phone) > 13 || !isNum(phone));

    Customer* curr = Search(core, phone);

    if (curr == NULL) {  // Pelanggan baru, buat baru
        char name[50];
        do {
            printf("\n%s(i) Nama harus 3-25 karakter dan diawali Mr./Mrs.%s\n", YELLOW, RESET);
            printf("Input Name: ");
            scanf(" %[^\n]", name);
        } while (strlen(name) < 3 || strlen(name) > 25 || !isPerson(name));

        char email[50];
        do {
            printf("\n%s(i) Email harus 10-20 karakter dan sesuai format email%s\n", YELLOW, RESET);
            printf("Input Email: ");
            scanf(" %[^\n]", email);
        } while (!isEmail(email));

        core = Generate(core, name, phone, email, 10, 0);  
        curr = Search(core, phone); 

        if (curr == NULL) { 
            // Tes bug
            printf("%s\n (i) ERROR: Gagal menambahkan pelanggan!%s\n", RED, RESET);
            return;
        } else {
            printf("%s\n (i) Selamat datang, %s %s\n", GREEN, curr->name, RESET);
        }
    } else {
        printf("%s\n (i) Selamat datang kembali, %s %s\n", GREEN, curr->name, RESET);
    }

    // Order Minuman
    OrderMenu(curr);

    printf("Press enter to continue..."); getchar();
    while (getchar() != '\n'); 
}

void OrderMenu (Customer* curr) {
    // Daftar minuman
    char* drinks[] = {"Cafe Latte", "Caramel Macchiato", "Cappuccino", "Cafe Mocha"};
    int ordercc[4] = {0, 0, 0, 0};
    
    int tspend = 0;
    int tbonus_used = 0;
    
    while (true) {
        refreshPoints(curr);
        int free = curr->points / 25;

        // Order minuman
        char drink[50];
        int drink_index = -1;
        do {
            printf("\nCafe Latte | Caramel Macchiato | Cappuccino | Cafe Mocha\n");
            printf("Input Drink: ");
            scanf(" %[^\n]", drink);
            
            for (int i = 0; i < 4; i++) {
                if (strcmpi(drink, drinks[i]) == 0) {
                    drink_index = i;
                    break;
                }
            }
        } while (drink_index == -1);

        // Input Quantity
        int quantity;
        do {
            printf("Masukan jumlah minuman: ");
            scanf("%d", &quantity);
        } while (quantity < 1);

        // Validasi Bonus
        char input[5];
        int bonus = 0;
        if (free) {
            do {
                printf("\nKamu punya %d bonus minuman tersisa (%d poin)\n", free, curr->points);
                printf("Ingin menggunakan 25 poin untuk bonus minuman? [Y/N]: ");
                scanf(" %[^\n]", input);
            } while (strcmpi(input, "Y") != 0 && strcmpi(input, "N") != 0);
            
            if (strcmpi(input, "Y") == 0) {
                do {
                    printf("\nPoin: %d\n", curr->points);
                    printf("Masukkan jumlah poin yang ingin ditukar [25 poin / bonus]: ");
                    scanf("%d", &bonus);
                    
                    if (bonus % 25 != 0 || bonus / 25 > free) {
                        printf("%s\n (i) Bonus tidak valid, coba lagi!%s\n", RED, RESET);
                    }
                } while (bonus % 25 != 0 || bonus / 25 > free);
                
                // Hitung bonus
                int bonus_used = bonus / 25;
                bonus_used = (bonus_used > quantity) ? quantity : bonus_used;

                int paid_drinks = quantity - bonus_used;
                
                if (paid_drinks > 0) {
                    curr->spend += paid_drinks * 30000;
                    tspend += paid_drinks * 30000;
                }
                
                tbonus_used += bonus_used;
                curr->points -= bonus_used * 25;
                ordercc[drink_index] += quantity;
                printf("%s\n (i) Bonus minuman berhasil ditambahkan%s\n", GREEN, RESET);
            }

        } else {
            ordercc[drink_index] += quantity;
            tspend += quantity * 30000;
            curr->spend += quantity * 30000;
        }
        printf("%s\n (i) Selamat menikmati minuman Anda%s\n", GREEN, RESET);

        // Validasi End
        do {
            printf("Apakah Anda ingin memesan lagi? [Y/N]: ");
            scanf(" %[^\n]", input);
        } while (strcmpi(input, "Y") != 0 && strcmpi(input, "N") != 0);

        if (strcmpi(input, "N") == 0) {
            break;
        }
    }

    // Summary
    printf("\n== Summary Order ==\n");
    for (int i = 0; i < 4; i++) {
        if (ordercc[i] > 0) {
            printf("%s - %d\n", drinks[i], ordercc[i]);
        }
    }

    int bonus_val = tbonus_used * 30000; 
    int total_pay = tspend - bonus_val;

    printf("---------------------------------------------------\n");
    printf("Subtotal       : Rp %d\n", tspend);
    printf("Bonus Used     : %d (Rp %d)\n", tbonus_used, bonus_val);
    printf("Total Payment  : Rp %d\n", total_pay);
    
    int bonus_obtained = (total_pay / 50000) * 3;
    curr->points += bonus_obtained;
    
    printf("Bonus Obtained : %d\n", bonus_obtained);
    printf("===================================================\n\n");

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