#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>

struct Book {
	int code;
	char name[100];
	Book* left;
	Book* right;
};

Book* core = NULL;

Book* Gen (int code, char name[]) {
	Book* book = (Book*) malloc (sizeof(Book));
	book->code = code;
	strcpy(book->name, name);
	book->left = NULL;
	book->right = NULL;
	return book;
}

Book* minBook (Book* root) {
	Book* curr = root;
	while (curr->left) {
		curr = curr->left;
	} return curr;
}

Book* maxBook (Book* root) {
	Book* curr = root;
	while (curr->right) {
		curr = curr->right;
	} return curr;
}

int Height (Book* root) {
	if (root == NULL) {
		return 0;
	}
	
	int left = Height(root->left);
	int right = Height(root->right);
	return 1 + (left > right ? left : right);
}

int Size (Book* root) {
	if (root == NULL) {
		return 0;
	}
	
	int left = Size(root->left);
	int right = Size(root->right);
	return 1 + left + right;
}

Book* Add (Book* root, int code, char name[]) {
	if (root == NULL) {
		root = Gen(code, name);
		return root;
	}
	
	if (code < root->code) {
		root->left = Add(root->left, code, name);
	} else if (code > root->code) {
		root->right = Add(root->right, code, name);
	} else {
		printf("Double Book detected\n");
	}
	
	return root;
}

Book* Delete (Book* root, int code) {
	if (root == NULL) {
		printf("Book not Found\n");
		return root;
	}
	
	if (code < root->code) {
		root->left = Delete(root->left, code);
	} else if (code > root->code) {
		root->right = Delete(root->right, code);
	} else {
		if ((root->left == NULL) || (root->right == NULL)) {
			Book* temp = (root->left == NULL) ? root->right : root->left;
			if (temp == NULL) {
				free(root);
				root = NULL;
			} else {
				*root = *temp;
				free(temp);
			}
		} else {
			Book* temp = minBook(root->right);
			root->code = temp->code;
			strcpy(root->name, temp->name);
			root->right = Delete(root->right, temp->code);
		}
	}
	
	return root;
}

Book* Search (int code) {
	if (core == NULL) {
		return NULL;
	}
	
	Book* curr = core;
	while (curr) {
		if (code < curr->code) {
			curr = curr->left;
		} else if (code > curr->code) {
			curr = curr->right;
		} else {
			return curr;
		}
	}
	
	return NULL;
}

void Preorder (Book* root) {
	if (root == NULL) {
		return;
	}
	
	printf("%s\n", root->name); printf("Code: %d\n\n", root->code);
	Preorder(root->left);
	Preorder(root->right);
}

void Inorder (Book* root) {
	if (root == NULL) {
		return;
	}
	
	Inorder(root->left);
	printf("%s\n", root->name); printf("Code: %d\n\n", root->code);
	Inorder(root->right);
}

void Postorder (Book* root) {
	if (root == NULL) {
		return;
	}
	
	Postorder(root->left);
	Postorder(root->right);
	printf("%s\n", root->name); printf("Code: %d\n\n", root->code);
}

// Menu Command
void Menu();

int main () {
	return 0;
}

void Menu () {
	int choice = -1;
	while (true) {
		system("cls");
		printf("1. Insert Book\n");
		printf("2. Search Book\n");
		printf("3. View Book\n");
		printf("4. Delete Book\n");
		printf("5. Oldest Book\n");
		printf("6. Latest Book\n");
		printf("7. Book Count\n");
		printf("8. Tree Height\n");
		printf("0. Exit\n>> ");
		
		scanf("%d", &choice);
		switch (choice) {
			case 0:
				return;
			case 1:
//				InsertMenu();
				break;
			case 2:
//				SearchMenu();
				break;
			case 3:
//				SearchMenu();
				break;
			case 4:
//				SearchMenu();
				break;
			case 5:
//				SearchMenu();
				break;
			case 6:
//				SearchMenu();
				break;
			case 7:
				
				break;
			case 8:
				
				break;
			default:
				printf("Invalid Input!\n"); getchar();
				printf("Press [Enter] to continue...");
				while (getchar() != '\n');
		}
	}
}
