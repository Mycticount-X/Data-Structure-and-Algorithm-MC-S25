#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
        printf("Permukaan saat ini kosong!\n");
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
        // printf("Permukaan saat ini kosong!\n");
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
    if (c == '(' || c == ')')
        return 4;
    else if (c == '^')
        return 3;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;

    else return 0; // Spasi dan Operator tidak jelas
}

// Stack Traversal
char* InfixtoPostfix (char* infix) {
    char* postfix = (char*) malloc(sizeof(char) * 100);
    int i = 0, j = 0;

    while (infix[i] != '\0') {
        // Operand
        if (infix[i] >= 'A' && infix[i] <= 'Z') {
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
}

char* InfixtoPrefix(char* infix) {
    char* reversed = (char*) malloc(sizeof(char) * 100);
    strcpy(reversed, infix);
    revstr(reversed);
    char* prefix = InfixtoPostfix(reversed);
    revstr(prefix);
    free(reversed);
    return prefix;
}



int main() {
    system("cls");
    char input[100];
    printf("%sMasukan Infix: %s", MAGENTA, RESET);
    scanf(" %[^\n]", input);

    char* postfix = InfixtoPostfix(input);
    char* prefix = InfixtoPrefix(input);

    printf("Postfix: %s\n", postfix);
    printf("Prefix: %s\n", prefix);

    free(postfix);
    free(prefix);
    return 0;
}