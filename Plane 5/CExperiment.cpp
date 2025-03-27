#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

struct Zone {
	int MTX;
	Zone* left;
	Zone* right;
};

Zone* core = NULL;

Zone* CreateZone (int MTX) {
	Zone* newzone = (Zone*)malloc(sizeof(Zone));
	newzone->MTX = MTX;
	newzone->left = NULL;
	newzone->right = NULL;
	return newzone;
}

// Helper Command
Zone* minZone (Zone* root) {
	while (root->left != NULL) {
		root = root->left;
	}
	return root;
}

// Generate Command
Zone* GenerateZone (Zone* root, int MTX) {
	if (root = NULL) {
		root = CreateZone(MTX);
		return root;
	}
	
	if (MTX < root->MTX) {
		root->left = GenerateZone(root->left, MTX);
		
	} else if (MTX > root->MTX) {
		root->right = GenerateZone(root->right, MTX);
		
	} else {
		printf("Zona duplikat terdeteksi!\n");
		printf("Memanggil fungsi Rollback\n");
		return root;
	}
	
	return root;
}

// Cut Command
Zone* CutZone (Zone* root, int MTX) {
	if (root = NULL) {
		printf("Zona tidak ditemukan!\n");
		printf("Memanggil fungsi Rollback\n");
		return root;
	}
	
	if (MTX < root->MTX) {
		root->left = CutZone(root->left, MTX);
		
	} else if (MTX > root->MTX) {
		root->right = CutZone(root->right, MTX);
		
	} else {
		if ((root->left == NULL) && (root->right == NULL)) {
			free(root);
			root = NULL;
			return root;
		}
		
		else if (root->right == NULL) {
			Zone* temp = root->left;
			free(root);
			root = NULL;
			return temp;
		}
		
		else if (root->left == NULL) {
			Zone* temp = root->right;
			free(root);
			root = NULL;
			return temp;
		}
		
		else {
			Zone* temp = minZone(root->right);
			*root = *temp;
			root->right = CutZone(root->right, root->MTX);
		}
		
	}
	return root;
}

void Inorder (Zone* root) {
	if (root == NULL) {
		return;
	}
	
	Inorder(root->left);
	printf("Zone: %d\n", root->MTX);
	Inorder(root->right);
	
}

// Menu
void Menu ();

int main () {
	return 0;
}

void Menu () {
	int input;
	while (1) {
		system("cls");
		printf("== Menu ==\n");
		printf("1. Insert\n");
		printf("2. Delete\n");
		printf("3. View\n");
		printf(">> ");
		
		scanf("%d", &input);
		
		switch (input) {
			case 1:
				// InsertMenu();
				break;
			case 2:
				// DeleteMenu();
				break;
			default:
				printf("Invalid Input\n");
				break;
		}
	}
}
