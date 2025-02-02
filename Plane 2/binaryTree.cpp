#include <stdio.h>
#include <stdlib.h>

typedef struct Zone {
    int MTX;
    Zone *left;
    Zone *right;
} Zone;

Zone *Core = NULL;

Zone *CreateZone(int MTX) {
    Zone *newZone = (Zone*) malloc(sizeof(Zone));
    newZone->MTX = MTX;
    newZone->left = NULL;
    newZone->right = NULL;
    return newZone;
}

// Generate Function
void GenerateZone (int MTX) {
	Zone *newZone = CreateZone(MTX);
	
	if (Core == NULL) {
		Core = newZone;
		return;
	}
	
	Zone *par = NULL;
	Zone *cur = Core;
	
	while (cur != NULL) {
		par = cur;
		if (MTX < cur->MTX) {
			cur = cur->left;
		} else {
			cur = cur->right;
		}
	}
	
	if (MTX < par->MTX) {
		par->left = newZone;
	} else {
		par->right = newZone;		
	}
}

// Ordering Map
void Preorder (Zone *root) {
	if (root == NULL) {
		return;
	}
	
	printf("%d ", root->MTX);
	Preorder(root->left);
	Preorder(root->right);
}

void Inorder (Zone *root) {
	if (root == NULL) {
		return;
	}
	
	Inorder(root->left);
	printf("%d ", root->MTX);
	Inorder(root->right);
}

void Postorder (Zone *root) {
	if (root == NULL) {
		return;
	}
	
	Postorder(root->left);
	Postorder(root->right);
	printf("%d ", root->MTX);
}

int main() {
    GenerateZone(8000);
    GenerateZone(7500);
    GenerateZone(8500);
    GenerateZone(7000);
    GenerateZone(7700);
    
    printf("Preorder: ");
    Preorder(Core);
    printf("\n");

    printf("Inorder: ");
    Inorder(Core);
    printf("\n");

    printf("Postorder: ");
    Postorder(Core);
    printf("\n");

    return 0;
}

