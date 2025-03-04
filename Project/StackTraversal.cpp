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

struct Zone {
    char MTX;
    Zone *next;
    Zone *prev;
};

Zone *head = NULL, *tail = NULL;

char Infix[1000];

Zone *CreateZone(char MTX) {
    Zone *newZone = (Zone*) malloc(sizeof(Zone));
    newZone->MTX = MTX;
    newZone->next = NULL;
    newZone->prev = NULL;
    return newZone;
}

// Push Command
void Push (char MTX) {
	Zone *newZone = CreateZone(MTX);
    if (head == NULL) {
        head = tail = newZone;
    } else {
        newZone->next = head;
        head->prev = newZone;
        head = newZone;
    }
}

// Pop Command
void Pop() {
    if (head == NULL) {
//        printf("Permukaan saat ini kosong!\n");
        return;
    }
    
    Zone *temp = head;
    head = head->next;
    if (head == NULL) {
        tail = NULL;
    } else {
        head->prev = NULL;
    }
    
    free(temp);
}

// Peek / Peep Command
char Peek() {
	if (head == NULL) {
        printf("Permukaan saat ini kosong!\n");
        return 0;
    }
    
    return head->MTX;
}

// Alter Command
void ClearPlane() {
    int clear = 0;
    while (head != NULL) {
        Zone *temp = head;
        head = head->next;
        free(temp);
        clear++;
    }
    head = tail = NULL;
    printf("Berhasil membersihkan %d Zona!\n", clear);
}

// Leveling
int level (char c) {
    if (c == '^')
        return 3;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;

    else return 0; // Spasi dan Operator tidak jelas
}

int isOperand (char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

// Stack Traversal
char* InfixtoPostfix (char* infix) {
    char* postfix = (char*) malloc(sizeof(char) * 100);
    int i = 0, j = 0;

    while (infix[i] != '\0') {
        // Operand
        if (isOperand(infix[i])) {
            postfix[j++] = infix[i];
        }
        
        // Parenthesis
        else if (infix[i] == '(') {
            Push(infix[i]);
        }
        
        else if (infix[i] == ')') {
            while (head != NULL && Peek() != '(') {
                postfix[j++] = Peek();
                Pop();
            }
            Pop();
        }
        
        // Operator
        else {
            if (level(infix[i]) > 0) {
                while (head != NULL && (level(Peek()) >= level(infix[i])) ) {
                    postfix[j++] = Peek();
                    Pop();
                }
                Push(infix[i]);
            }
        }

        i++;
    }

    // Bersih-bersih
    while (head != NULL) {
        postfix[j++] = Peek();
        Pop();
    }

    postfix[j] = '\0';
    return postfix;
}


void revstr (char* str) {
    int len = strlen(str);
    for (int i = 0; i < len/2; i++) {
        char c = str[i];
        str[i] = str[len-1-i];
        str[len-1-i] = c;
    }
    
    for (int i = 0; i < len; i++) {
        if (str[i] == '(')
        	str[i] = ')';
        else if (str[i] == ')')
        	str[i] = '(';
    } 
}

char* InfixtoPrefix(char* infix) {
    char* temp = (char*) malloc(sizeof(char) * 100);
    strcpy(temp, infix);
    
	// Reverse
	revstr(temp);
    
	// Postfix
	char* prefix = (char*) malloc(sizeof(char) * 100);
    int i = 0, j = 0;

    while (temp[i] != '\0') {
        // Operand
        if (isOperand(temp[i])) {
            prefix[j++] = temp[i];
        }
        
        // Parenthesis
        else if (temp[i] == '(') {
            Push(temp[i]);
        }
        
        else if (temp[i] == ')') {
            while (head != NULL && Peek() != '(') {
                prefix[j++] = Peek();
                Pop();
            }
            Pop();
        }
        
        // Operator
        else {
            if (level(temp[i]) > 0) {
                while (head != NULL && (level(Peek()) > level(temp[i])) ) {
                    prefix[j++] = Peek();
                    Pop();
                }
                Push(temp[i]);
            }
        }

        i++;
    }

    // Bersih-bersih
    while (head != NULL) {
        prefix[j++] = Peek();
        Pop();
    }

    prefix[j] = '\0';
    
	// Reverse
	revstr(prefix);
	
    return prefix;
}

// Prototype Menu Function
void Menu();
void InsertMenu();
void PostfixMenu();
void PrefixMenu();
void ExitMenu();

int main() {
    system("cls");
    char input[100];
    printf("%sMasukan Infix: %s", MAGENTA, RESET);
    scanf(" %[^\n]", input);
    printf("Infix: %s\n", input);

    char* postfix = InfixtoPostfix(input);
    char* prefix = InfixtoPrefix(input);

    printf("Postfix: %s\n", postfix);
    printf("Prefix: %s\n", prefix);

    free(postfix);
    free(prefix);
    return 0;
}


// Menu Function
void Menu () {
	int position = 0;
	char input;
	system("cls");
	while (true) {
		printf("%s Stack Traversal%s\n", CYAN, RESET);
		printf("%s 1. Insert Infix %s\n", (position == 0) ? ">>" : "  ", (position == 0) ? "<<" : "  ");
		printf("%s 2. View Postfix %s\n", (position == 1) ? ">>" : "  ", (position == 1) ? "<<" : "  ");
		printf("%s 3. View Prefix %s\n", (position == 2) ? ">>" : "  ", (position == 2) ? "<<" : "  ");
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
                    PostfixMenu();
                    break;
                case 2:
                    PrefixMenu();
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
    char input[100];
    printf("%sMasukan Infix: %s", MAGENTA, RESET);
    scanf(" %[^\n]", input);

    if (strcmpi(input, "exit") == 0 || strcmpi(input, "cancel") == 0) {
        printf("%s(i) Insert canceled! %s\n", YELLOW, RESET);

        printf("Press enter to continue...");
	    while (getchar() != '\n');
    }

    strcpy(Infix, input);
    printf("Infix: %s\n", Infix);
    printf("%s(i) Insert success! %s\n\n", GREEN, RESET);

    printf("Press enter to continue...");
    while (getchar() != '\n');
}