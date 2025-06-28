#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

// Responsi BSQ cuma segini doangk nih
struct User {
	char name[51];
	char hobby[201];
	int height;
	User* left;
	User* right;
};

User* core = NULL;

User* Generate (char name[], char hobby[]) {
	User* newu = (User*) malloc(sizeof(User));
	strcpy(newu->name, name);
	strcpy(newu->hobby, hobby);
	newu->left = NULL;
	newu->right = NULL;
	newu->height = 1;
	return newu;
}

// Support Command
int maxx (int a, int b) {
	return (a > b) ? a : b;
}

int Height (User* u) {
	return (u == NULL) ? 0 : u->height;
}

int calcHeight (User* u) {
	if (u == NULL) return 0;
	return maxx(Height(u->left), Height(u->right)) + 1;
}

int Balance (User* u) {
	return (u == NULL) ? 0 : (Height(u->left) - Height(u->right));
}

User* MinUser (User* u) {
	User* c = u;
	while (c->left) {
		c = c->left;
	} return c;
}

// Standard Rotation
User* RotateLeft (User* u) {
	User* c = u->right;
	User* gc = c->left;
	
	c->left = u;
	u->right = gc;
	
	u->height = calcHeight(u);
	c->height = calcHeight(c);
	
	return c;
}

User* RotateRight (User* u) {
	User* c = u->left;
	User* gc = c->right;
	
	c->right = u;
	u->left = gc;
	
	u->height = calcHeight(u);
	c->height = calcHeight(c);
	
	return c;
}

// Master Command
User* Insert (User* u, char name[], char hobby[]) {
	if (u == NULL) {
		u = Generate(name, hobby);
		return u; 
	}
	
	if (strcmp(name, u->name) < 0) {
		u->left = Insert(u->left, name, hobby);
	} else if (strcmp(name, u->name) > 0) {
		u->right = Insert(u->right, name, hobby);
	} else {
		printf("User yang sama terdeteksi!\n");
		return u;
	}
	
	u->height = calcHeight(u);
	int bal = Balance(u);
	
	// LL
	if (bal > 1 && Balance(u->left) >= 0) {
		return RotateRight(u);
	}
	
	// RR
	if (bal < -1 && Balance(u->right) <= 0) {
		return RotateLeft(u);
	}
	
	// LR
	if (bal > 1 && Balance(u->left) < 0) {
		u->left = RotateLeft(u->left);
		return RotateRight(u);
	}
	
	// RL
	if (bal < -1 && Balance(u->right) > 0) {
		u->right = RotateRight(u->right);
		return RotateLeft(u);
	}
	
	return u;
}

User* Delete (User* u, char name[]) {
	if (u == NULL) {
		printf("User tidak ditemukan!\n");
		return u; 
	}
	
	if (strcmp(name, u->name) < 0) {
		u->left = Delete(u->left, name);
	} else if (strcmp(name, u->name) > 0) {
		u->right = Delete(u->right, name);
	} else {
		printf("User %s berhasil dihapus!\n", u->name);
		if (u->left == NULL || u->right == NULL) {
			User* temp = u->left ? u->left : u->right;
			if (temp == NULL) {
				temp = u;
				u = NULL;
			} else {
				*u = *temp;
			}
			free(temp);
		} else {
			User* temp = MinUser(u->right);
			strcpy(u->hobby, temp->hobby);
			strcpy(u->name, temp->name);
			u->right = Delete(u->right, temp->name);
		}
		
	}
	
	if (u == NULL) {
		return u;
	}
	
	u->height = calcHeight(u);
	int bal = Balance(u);
	
	// LL
	if (bal > 1 && Balance(u->left) >= 0) {
		return RotateRight(u);
	}
	
	// RR
	if (bal < -1 && Balance(u->right) <= 0) {
		return RotateLeft(u);
	}
	
	// LR
	if (bal > 1 && Balance(u->left) < 0) {
		u->left = RotateLeft(u->left);
		return RotateRight(u);
	}
	
	// RL
	if (bal < -1 && Balance(u->right) > 0) {
		u->right = RotateRight(u->right);
		return RotateLeft(u);
	}
	
	return u;
}

// Other Command
User* SearchUser (char name[]) {
	User* u = core;
	while (true) {
		if (u == NULL) {
			printf("User tidak ditemukan!\n");
			return u; 
		}
		
		if (strcmp(name, u->name) < 0) {
			u = u->left;
		} else if (strcmp(name, u->name) > 0) {
			u = u->right;
		} else {
			return u;
		}
	} return u;
}

void Inorder (User* u) {
	if (u == NULL) return;
	Inorder(u->left);
	printf("%-15s - %s\n", u->name, u->hobby);
	Inorder(u->right);
}

void ViewPlane () {
	if (core == NULL) {
		printf("No Data\n");
		return;
	}
	printf("          User - Hobbies \n");
	Inorder(core);
}

void InsertUser (char name[], char hobby[]) {
	int key = rand() % 1000;
	char result[51];
	sprintf(result, "%s%03d", name, key);
	core = Insert(core, result, hobby);
	printf(">> Insert Operation of %s Completed <<\n\n", result);
}

bool Manage (char input[]) {
	char name[51], hobby[201];
	if (strcmp(input, "insert") == 0) {
		scanf("  %[^-]-%[^\n]", name, hobby);
		InsertUser(name, hobby);
		
	} else if (strcmp(input, "show_all") == 0) {
		ViewPlane();
		printf(">> Show All Operation Completed <<\n\n");
		
	} else if (strcmp(input, "show") == 0) {
		scanf(" %s", name);
		User* u = SearchUser(name);
		if (u != NULL) {
			printf("Hobbies: %s\n", u->hobby);
		}
		printf(">> Show Operation Completed <<\n\n");
		
	} else if (strcmp(input, "delete") == 0) {
		scanf(" %s", name);
		core = Delete(core, name);
		printf(">> Delete Operation Completed <<\n\n");
		
	} else if (strcmp(input, "exit") == 0) {
		printf(">> Salam dari Mycticount-X <<\n\n");
		return true;
		
	} else {
		printf("!! Invalid Input !!\n");
	} return false;
}

void Menu () {
	char input[101];
	bool exit = false;
	printf(" == Selamat Datang di BSQ Sosmed == \n");
	while (true) {
		scanf("%s", input);
//		printf("Output: ");
		exit = Manage (input);
		if (exit) break;
	}
}

int main () {
	srand(time(NULL));
    Menu ();
	return 0;
}


