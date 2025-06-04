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
// AutoCompVled

typedef struct Zone {
    char Word[101];
    Zone *left;
    Zone *right;
    int height;
} Zone;

Zone *Core = NULL;

Zone *CreateZone(char Word[]) {
    Zone *newZone = (Zone*) malloc(sizeof(Zone));
    strcpy(newZone->Word, Word);
    newZone->left = NULL;
    newZone->right = NULL;
    newZone->height = 1; // Tinggi sebuah Zona diukur dari jumlah Celah menuju Core
    return newZone;
}

// Spesific Global Variable
char bestMatch[101];
bool foundMatch = false;

char longestWord[101];
int longestLength = -1;

int autocompleteCount = 0;


// Standart AVL
int height(struct Zone* root) {
    return (root == NULL) ? 0 : root->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int getBalance(struct Zone* root) {
    return (root != NULL) ? height(root->left) - height(root->right) : 0;
}

Zone *minZone(Zone *root) {
    Zone *current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

bool StartsWith(const char *str, const char *prefix) {
    return strncmp(str, prefix, strlen(prefix)) == 0;
}


// Standart Rotation
Zone *rotateRight(Zone* root) {
    Zone* child = root->left;
    Zone* grandchild = child->right;

    child->right = root;
    root->left = grandchild;

    root->height = max(height(root->left), height(root->right)) + 1;
    child->height = max(height(child->left), height(child->right)) + 1;

    return child;
}

Zone *rotateLeft(Zone* root) {
    Zone* child = root->right;
    Zone* grandchild = child->left;

    child->left = root;
    root->right = grandchild;

    root->height = max(height(root->left), height(root->right)) + 1;
    child->height = max(height(child->left), height(child->right)) + 1;

    return child;
}

// Generate Zone
Zone *GenerateZone (Zone *root, char Word[]) {
    if (root == NULL) {
        root = CreateZone(Word);
        return root;
    }

    int cmp = strcmp(Word, root->Word);
    if (cmp < 0) {
        root->left = GenerateZone(root->left, Word);
    } else if (cmp > 0) {
        root->right = GenerateZone(root->right, Word);
    } else {
        printf("Zona Duplikat terdeteksi!\n");
        return root;
    }

    // Tinggi Zona
    root->height = max(height(root->left), height(root->right)) + 1;

    // Faktor Keseimbangan
    int balance = getBalance(root);

    // Kasus Left Left
    if (balance > 1 && strcmp(Word, root->left->Word) < 0) {
        return rotateRight(root);
    }

    // Kasus Right Right
    if (balance < -1 && strcmp(Word, root->right->Word) > 0) {
        return rotateLeft(root);
    }

    // Kasus Left Right
    if (balance > 1 && strcmp(Word, root->left->Word) > 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Kasus Right Left
    if (balance < -1 && strcmp(Word, root->right->Word) < 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

Zone *DeleteZone(Zone *root, char Word[]) {
    if (root == NULL) return root;

    // Search Zone
    int cmp = strcmp(Word, root->Word);
    if (cmp < 0) {
        root->left = DeleteZone(root->left, Word);
    } else if (cmp > 0) {
        root->right = DeleteZone(root->right, Word);
    } else {
        // Zona ditemukan
        if ((root->left == NULL) || (root->right == NULL)) {
            // Zona Anak Satu
            Zone *temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            // Zona Anak Dua
            Zone *temp = minZone(root->right);
            strcpy(root->Word, temp->Word);
            root->right = DeleteZone(root->right, temp->Word);
        }
    }

    if (root == NULL) return root;

    // Tinggi Zona
    root->height = max(height(root->left), height(root->right)) + 1;

    // Faktor Keseimbangan
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
Zone* SearchZone(Zone* root, char Word[]) {
    while (root != NULL) {
        int cmp = strcmp(Word, root->Word);
        if (cmp == 0) {
            return root;
        } else if (cmp < 0) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    return NULL;
}

// Alter Command
void ClearPlane(Zone *root) {
    if (root == NULL) return;
    ClearPlane(root->left);
    ClearPlane(root->right);
    free(root);
}


// Traversal Map
void Preorder (Zone *root) {
    if (root == NULL) {
        return;
    }
    
    printf("  %s \n", root->Word);
    Preorder(root->left);
    Preorder(root->right);
}

void Inorder (Zone *root) {
    if (root == NULL) {
        return;
    }
    
    Inorder(root->left);
    printf("  %s \n", root->Word);
    Inorder(root->right);
}

void Postorder (Zone *root) {
    if (root == NULL) {
        return;
    }
    
    Postorder(root->left);
    Postorder(root->right);
    printf("  %s \n", root->Word);
}

// Spesific Need
bool IsPrefixExist(Zone *root, const char *prefix) {
    if (root == NULL) return false;
    if (StartsWith(root->Word, prefix)) return true;
    return IsPrefixExist(root->left, prefix) || IsPrefixExist(root->right, prefix);
}

void Preorder_Prefix(Zone *root, const char *prefix) {
    if (root == NULL) return;

    if (StartsWith(root->Word, prefix)) {
        printf("  %s\n", root->Word);
    }

    Preorder_Prefix(root->left, prefix);
    Preorder_Prefix(root->right, prefix);
}

void Inorder_Prefix(Zone *root, const char *prefix) {
    if (root == NULL) return;

    Inorder_Prefix(root->left, prefix);

    if (StartsWith(root->Word, prefix)) {
        printf("  %s\n", root->Word);
    }

    Inorder_Prefix(root->right, prefix);
}

void Postorder_Prefix(Zone *root, const char *prefix) {
    if (root == NULL) return;

    Postorder_Prefix(root->left, prefix);
    Postorder_Prefix(root->right, prefix);

    if (StartsWith(root->Word, prefix)) {
        printf("  %s\n", root->Word);
    }
}

void BestMatching(Zone *root, const char *prefix) {
    if (root == NULL) return;

    // Cek kiri
    BestMatching(root->left, prefix);

    // Cek current node
    if (StartsWith(root->Word, prefix)) {
        if (!foundMatch || strcmp(root->Word, bestMatch) < 0) {
            strcpy(bestMatch, root->Word);
            foundMatch = true;
        }
    }

    // Cek kanan
    BestMatching(root->right, prefix);
}

void FindLongest(Zone *root, const char *prefix) {
    if (root == NULL) return;

    FindLongest(root->left, prefix);

    if (StartsWith(root->Word, prefix)) {
        printf("  %s\n", root->Word);

        int len = strlen(root->Word);
        if (len > longestLength) {
            longestLength = len;
            strcpy(longestWord, root->Word);
        }
    }

    FindLongest(root->right, prefix);
}

void CountAuto(Zone *root, const char *prefix) {
    if (root == NULL) return;

    CountAuto(root->left, prefix);

    if (StartsWith(root->Word, prefix)) {
        printf("  %s\n", root->Word);
        autocompleteCount++;
    }

    CountAuto(root->right, prefix);
}


void ExitMenu () {
    printf("Thank you for using AutoCompVled!\n");
    printf("Have a nice day :)\n\n");
    Sleep(1000);

    printf("%sCreator:%s\n", MAGENTA, RESET);
    printf("Name: Michael AS\n");
    printf("Github: Mycticount-X\n");
    printf("Youtube: Mycticount X\n");
    printf("HSR: 825019617\n");
}



// Menu Function
void Menu() {
    system("cls");
    printf("%s==============================%s\n", CYAN, RESET);
    printf("%s      AutoCompVleD Menu       %s\n", CYAN, RESET);
    printf("%s==============================%s\n", CYAN, RESET);

    printf("%sLoading...%s\n", MAGENTA, RESET);
    Sleep(1000);
    printf("%sStep 1 -> Insert Words%s\n", YELLOW, RESET);
    int wcount;
    do {
        printf("Enter number of words: ");
        scanf("%d", &wcount);
        if (wcount <= 0) {
            printf("%sNumber of words must be greater than 0!%s\n", RED, RESET);
        }
    } while (wcount <= 0);

    printf("Insert %d words:\n", wcount);
    for (int i = 0; i < wcount; i++) {
        char word[101];
        while (1) {
            printf("Word %d: ", i + 1);
            scanf(" %[^\n]", word);
            if (SearchZone(Core, word) == NULL) {
                Core = GenerateZone(Core, word);
                break;
            } else {
                printf("%sWord \"%s\" already exists. Please enter a different word.%s\n", RED, word, RESET);
            }
        }
    }
    printf("\n");

    // 2
    printf("%sLoading...%s\n", MAGENTA, RESET);
    Sleep(1000);
    printf("%sStep 2 -> Show All AutoComplete Word%s\n", YELLOW, RESET);
    char prefix[101];
    printf("Enter prefix: ");
    scanf(" %[^\n]", prefix);
    bool validator = !IsPrefixExist(Core, prefix);

    // Validasi prefix tidak boleh kosong
    if (strlen(prefix) == 0) {
        printf("%sPrefix tidak boleh kosong!%s\n\n", RED, RESET);
    } else if (validator) {
        printf("%sTidak ada kata yang cocok dengan prefix \"%s\".%s\n\n", RED, prefix, RESET);
    } else {
        printf("\nPreorder: \n");
        Preorder_Prefix(Core, prefix);
        printf("\nInorder: \n");
        Inorder_Prefix(Core, prefix);
        printf("\nPostorder: \n");
        Postorder_Prefix(Core, prefix);
        printf("\n");
    }

    // 3
    printf("%sLoading...%s\n", MAGENTA, RESET);
    Sleep(1000);
    printf("%sStep 3 -> Insert new word%s\n", YELLOW, RESET);
    char newWord[101];
    while (1) {
        printf("Enter new word: ");
        scanf(" %[^\n]", newWord);
        if (SearchZone(Core, newWord) == NULL) {
            Core = GenerateZone(Core, newWord);
            printf("Word \"%s\" inserted successfully.\n\n", newWord);
            break;
        } else {
            printf("%sWord \"%s\" already exists. Please enter a different word.%s\n", RED, newWord, RESET);
        }
    }

    // 4
    printf("%sLoading...%s\n", MAGENTA, RESET); Sleep(1000);
    printf("%sStep 4 -> Show Top 1 Autocomplete (lexicographically smallest)%s\n", YELLOW, RESET);
    printf("Enter prefix: ");
    scanf(" %[^\n]", prefix);

    foundMatch = false;
    BestMatching(Core, prefix);

    if (foundMatch) {
        printf("Best match for prefix \"%s\" is: %s\n", prefix, bestMatch);
    } else {
        printf("No autocomplete suggestions found for \"%s\"\n", prefix);
    }
    
    
    // 5
    printf("%s\nLoading...%s\n", MAGENTA, RESET);
    Sleep(1000);
    printf("%sStep 5 -> Delete a word%s\n", YELLOW, RESET);
    char deleteWord[101];
    printf("Enter word to delete: ");
    scanf(" %[^\n]", deleteWord);
    while (1) {
        if (SearchZone(Core, deleteWord) == NULL) {
            printf("%sWord \"%s\" not found. Cannot delete.%s\n", RED, deleteWord, RESET);
            printf("Enter word to delete: ");
            scanf(" %[^\n]", deleteWord);
        } else {
            Core = DeleteZone(Core, deleteWord);
            printf("Word \"%s\" deleted successfully.\n\n", deleteWord);
            break;
        }
    }
    
    // 6
    printf("%sLoading...%s\n", MAGENTA, RESET); Sleep(1000);
    printf("%sStep 6 -> Return longest autocomplete%s\n", YELLOW, RESET);
    printf("Enter prefix: ");
    scanf(" %[^\n]", prefix);

    longestLength = -1;
    FindLongest(Core, prefix);

    if (longestLength == -1) {
        printf("No suggestions found for \"%s\"\n", prefix);
    } else {
        printf("\nLongest : %s\n", longestWord);
    }


    // 7
    printf("%s\nLoading...%s\n", MAGENTA, RESET); Sleep(1000);
    printf("%sStep 7 -> Count Autocomplete%s\n", YELLOW, RESET);

    printf("Enter prefix: ");
    scanf(" %[^\n]", prefix);

    autocompleteCount = 0;
    CountAuto(Core, prefix);

    printf("\nTotal suggestions: %d\n\n", autocompleteCount);

    // 8
    printf("%sLoading...%s\n", MAGENTA, RESET); Sleep(1000);
    printf("%sEnding -> Exit Program%s\n", RED, RESET);
    ExitMenu();
    printf("%s==============================%s\n", CYAN, RESET);
}


// Main Function
int main() {
    Menu();
    return 0;
}

