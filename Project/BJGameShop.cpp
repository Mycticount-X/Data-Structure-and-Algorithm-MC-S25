#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>

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
// Bluejack GShop

struct Game {
    char name[50];
    int genre;
    int stock; // 0 = Action, 1 = RPG, 2 = Adventure, 3 = Card Game
    Game* left;
    Game* right;
    int height;
};

Game* core = NULL;

Game* createGame(char name[], int genre, int stock) {
    Game* newGame = (Game*)malloc(sizeof(Game));
    strcpy(newGame->name, name);
    newGame->genre = genre;
    newGame->stock = stock;
    newGame->left = NULL;
    newGame->right = NULL;
    newGame->height = 1;
    return newGame;
}

// Standart AVL
int height(Game* root) {
    return (root == NULL) ? 0 : root->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getBalance(Game* root) {
    return (root != NULL) ? height(root->left) - height(root->right) : 0;
}

Game* minZone(Game* root) {
    Game* current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Standart Rotation
Game* rotateRight(Game* root) {
    Game* child = root->left;
    Game* grandchild = child->right;

    child->right = root;
    root->left = grandchild;

    root->height = max(height(root->left), height(root->right)) + 1;
    child->height = max(height(child->left), height(child->right)) + 1;

    return child;
}

Game* rotateLeft(Game* root) {
    Game* child = root->right;
    Game* grandchild = child->left;

    child->left = root;
    root->right = grandchild;

    root->height = max(height(root->left), height(root->right)) + 1;
    child->height = max(height(child->left), height(child->right)) + 1;

    return child;
}

// Insert Command
Game* Generate (Game* root, char name[], int genre, int stock) {
    if (root == NULL) {
        return createGame(name, genre, stock);
    }

    if (strcmp(name, root->name) < 0) {
        root->left = Generate(root->left, name, genre, stock);
    } else if (strcmp(name, root->name) > 0) {
        root->right = Generate(root->right, name, genre, stock);
    } else {
        return root;
    }

    // Height and Balance
    root->height = max(height(root->left), height(root->right)) + 1;
    int balance = getBalance(root);

    // Kasus Left Left
    if (balance > 1 && strcmp(name, root->left->name) < 0) {
        return rotateRight(root);
    }

    // Kasus Right Right
    if (balance < -1 && strcmp(name, root->right->name) > 0) {
        return rotateLeft(root);
    }

    // Kasus Left Right
    if (balance > 1 && strcmp(name, root->left->name) > 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Kasus Right Left
    if (balance < -1 && strcmp(name, root->right->name) < 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Delete Command
Game* Delete (Game* root, char name[]) {
    if (root == NULL) {
        return root;
    }

    if (strcmp(name, root->name) < 0) {
        root->left = Delete(root->left, name);
    } else if (strcmp(name, root->name) > 0) {
        root->right = Delete(root->right, name);
    } else {
        // Ketemu
        if ((root->left == NULL) || (root->right == NULL)) {
            Game* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            Game* temp = minZone(root->right);
            strcpy(root->name, temp->name);
            root->right = Delete(root->right, temp->name);
        }
    }

    if (root == NULL) return root;

    // Height and Balance
    root->height = max(height(root->left), height(root->right)) + 1;
    int balance = getBalance(root);

    // Kasus Left Left
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rotateRight(root);
    }

    // Kasus Right Right
    if (balance < -1 && getBalance(root->right) <= 0) {
        return rotateLeft(root);
    }

    // Kasus Left Right
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Kasus Right Left
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// Search Command
Game* Search (char name[]) {
    Game* root = core;
    
    while (root != NULL) {
        if (strcmp(name, root->name) == 0) {
            return root;
        } else if (strcmp(name, root->name) < 0) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return NULL;
}

// Update Command
bool Update (char name[], int stock) {
    Game* game = Search(name);
    if (game != NULL) {
        game->stock = stock;
        return true;
    } else {
        return false;
    }
}

// Traversal Command
void Inorder (Game* root) {
    if (root == NULL) {
        return;
    }
    
    Inorder(root->left);
    printf("| %-25s | %-10s | %-5d |\n", root->name, (root->genre == 0) ? "Action" : (root->genre == 1) ? "RPG" : (root->genre == 2) ? "Adventure" : "Card Game", root->stock);
    Inorder(root->right);
}

// Clear Command
void Clear (Game* root) {
    if (root == NULL) return;
    Clear(root->left);
    Clear(root->right);
    free(root);
}

// Menu Function
void Menu();
void InsertMenu();
void ViewMenu();
void UpdateMenu();
void ExitMenu();

// Helper Function
char tolower (char c);
void lowercopy(char *to, const char *from);
int mtxcompi(const char *a, const char *b); // Pengganti strcmpi


int main () {
	Menu();
    return 0;
}

// Menu Function
void Menu () {
	int position = 0;
	char input;
	system("cls");
	while (true) {
		printf("%s Bluejack GShop %s\n", CYAN, RESET);
		printf("%s %s 1. Insert Game %s %s\n", (position == 0) ? YELLOW : "", (position == 0) ? ">>" : "  ", (position == 0) ? "<<" : "  ", (position == 0) ? RESET : "");
		printf("%s %s 2. View Game %s %s\n", (position == 1) ? YELLOW : "", (position == 1) ? ">>" : "  ", (position == 1) ? "<<" : "  ", (position == 1) ? RESET : "");
		printf("%s %s 3. Update Game %s %s\n", (position == 2) ? YELLOW : "", (position == 2) ? ">>" : "  ", (position == 2) ? "<<" : "  ", (position == 2) ? RESET : "");
		printf("%s %s 4. Exit %s %s\n", (position == 3) ? YELLOW : "", (position == 3) ? ">>" : "  ", (position == 3) ? "<<" : "  ", (position == 3) ? RESET : "");
        printf("\nGunakan %s[W]%s dan %s[S]%s untuk Navigasi", GREEN, RESET, GREEN, RESET);
		input = _getch();
		system("cls");
        if (input == 'w' || input == 'W') {
            if (position > 0) {
                position--;
            }
        } else if (input == 's' || input == 'S') {
            if (position < 4 - 1) {
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
					UpdateMenu();
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
    char name[50];
    char genre[20]; int genreCode = 0;
    int stock;

    do {
        printf("%s(i) Judul Game harus antara 5-25 karakter!%s\n", YELLOW, RESET);
        printf("Input Game Title: ");
        scanf(" %[^\n]", name);
    } while (strlen(name) < 5 || strlen(name) > 25); printf("\n");

    do {
        printf("%s(i) Genre Game: | Action | RPG | Adventure | Card Game | %s\n", YELLOW, RESET);
        printf("Input Game Genre: ");
        scanf(" %[^\n]", genre);
    } while (mtxcompi(genre, "Action") != 0 && mtxcompi(genre, "RPG") != 0 && mtxcompi(genre, "Adventure") != 0 && mtxcompi(genre, "Card Game") != 0);
    printf("\n");

    if (mtxcompi(genre, "Action") == 0) {
        genreCode = 0;
    } else if (mtxcompi(genre, "RPG") == 0) {
        genreCode = 1;
    } else if (mtxcompi(genre, "Adventure") == 0) {
        genreCode = 2;
    } else if (mtxcompi(genre, "Card Game") == 0) {
        genreCode = 3;
    }

    do {
        printf("%s(i) Stock Game harus antara 1-50!%s\n", YELLOW, RESET);
        printf("Input Game Stock: ");
        scanf("%d", &stock);
    } while (stock <= 0 || stock > 50); printf("\n");

    core = Generate(core, name, genreCode, stock);
    printf("%s(i) Game %s berhasil ditambahkan!%s\n", GREEN, name, RESET);

    printf("Press [Enter] to continue...\n"); getchar();
    while (getchar() != '\n');
}

void ViewMenu () {
    if (core == NULL) {
        printf("%s(i) Belum ada game yang ditambahkan!%s\n", RED, RESET);
        printf("Press [Enter] to continue...\n");
        while (getchar() != '\n');
        return;
    }
    
    printf("%s Bluejack GShop %s\n", CYAN, RESET);
    printf("--------------------------------------------------\n");
    printf("| %-25s | %-10s | %-5s |\n", "Game Title", "Genre", "Stock");
    printf("--------------------------------------------------\n");
    Inorder(core);
    printf("--------------------------------------------------\n");
    printf("Press [Enter] to continue...\n");
    while (getchar() != '\n');
}

void UpdateMenu () {
    if (core == NULL) {
        printf("%s(i) Belum ada game yang ditambahkan!%s\n", RED, RESET);
        printf("Press [Enter] to continue...\n");
        while (getchar() != '\n');
        return;
    }

	char name[50];
    do {
        printf("%s(i) Judul Game harus antara 5-25 karakter!%s\n", YELLOW, RESET);
        printf("Input Game Title: ");
        scanf(" %[^\n]", name);
    } while (strlen(name) < 5 || strlen(name) > 25);

    Game* game = Search(name);
    if (game == NULL) {
        printf("%s\n(i) Game %s tidak ditemukan!%s\n", RED, name, RESET);
        printf("Press [Enter] to continue...\n"); getchar();
        while (getchar() != '\n');
        return;
    }
	
    printf("%s\n(i) Game Info: %s\n", GREEN, RESET);
    printf("Title: %s\n", game->name);
    printf("Genre: %s\n", (game->genre == 0) ? "Action" : (game->genre == 1) ? "RPG" : (game->genre == 2) ? "Adventure" : "Card Game");
    printf("Stock: %d\n\n", game->stock);
	
	char input[50];
    
    do {
        printf("%s(i) Update Type: ( Add | Remove ) !%s\n", YELLOW, RESET);
        printf("Input Update Type: ");
        scanf(" %[^\n]", input);
    } while (mtxcompi(input, "Add") != 0 && mtxcompi(input, "Remove") != 0);

    if (mtxcompi(input, "Add") == 0) {
        int addStock;
        do {
            printf("%s(i) Stock Game yang ditambahkan harus antara 1-50!%s\n", YELLOW, RESET);
            printf("Input Game Stock: ");
            scanf("%d", &addStock);
        } while (addStock <= 0 || addStock > 50);
        game->stock += addStock;
    } else if (mtxcompi(input, "Remove") == 0) {
        int removeStock;
        do {
            printf("%s(i) Stock Game yang diambil harus antara 1-50!%s\n", YELLOW, RESET);
            printf("Input Game Stock: ");
            scanf("%d", &removeStock);
        } while (removeStock <= 0 || removeStock > 50);
        game->stock -= removeStock;
    }

    printf("%s\n(i) Game %s berhasil diupdate!%s\n", GREEN, name, RESET);
    if (game->stock <= 0) {
        printf("%s\n(i) Stock Game %s sudah habis!%s\n", YELLOW, name, RESET);
        printf("Game %s akan dihapus!\n", name);
        core = Delete(core, name);
    } else if (game->stock > 50) {
        printf("%s\n(i) Stock Game %s sudah lebih dari 50!%s\n", YELLOW, name, RESET);
        printf("Stok berlebih akan disingkirkan!\n");
        game->stock = 50;
    }

    printf("\nPress [Enter] to continue...\n"); getchar();
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
					printf("Thank you for using Bluejack Game Shop!\n");
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

// Helper Function
char tolower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + 32;
    }
    return c;
}

void lowercopy(char *to, const char *from) {
    int i = 0;
    while (from[i]) {
        to[i] = tolower(from[i]);
        i++;
    }
    to[i] = '\0';
}

int mtxcompi(const char *a, const char *b) {
    char tempA[1000];
    char tempB[1000];
    lowercopy(tempA, a);
    lowercopy(tempB, b);
    return strcmp(tempA, tempB);
}
