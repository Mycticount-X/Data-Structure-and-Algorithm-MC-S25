#include <stdio.h>
#include <stdlib.h>

typedef struct Zone {
    int MTX;
    Zone *left;
    Zone *right;
    int height;
} Zone;

Zone *Core = NULL;

Zone *CreateZone(int MTX) {
    Zone *newZone = (Zone*) malloc(sizeof(Zone));
    newZone->MTX = MTX;
    newZone->left = NULL;
    newZone->right = NULL;
    newZone->height = 1; // Tinggi sebuah Zona diukur dari jumlah Celah menuju Core
    return newZone;
}

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
Zone *GenerateZone (Zone *root, int MTX) {
	if (root == NULL) {
		root = CreateZone(MTX);
		return root;
	}
	
	if (MTX < root->MTX) {
		root->left = GenerateZone(root->left, MTX);
	} else if (MTX > root->MTX) {
		root->right = GenerateZone(root->right, MTX);
	} else {
		printf("Zona Duplikat terdeteksi!\n");
		return root;
	}
	
	// Tinggi Zona
	root->height = max(height(root->left), height(root->right)) + 1;
	
	// Faktor Keseimbangan
	int balance = getBalance(root);
	
	// Kasus Left Left
    if (balance > 1 && MTX < root->left->MTX) {
        return rotateRight(root);
    }

    // Kasus Right Right
    if (balance < -1 && MTX > root->right->MTX) {
        return rotateLeft(root);
    }

    // Kasus Left Right
    if (balance > 1 && MTX > root->left->MTX) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Kasus Right Left
    if (balance < -1 && MTX < root->right->MTX) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

Zone *DeleteZone(Zone *root, int target) {
    if (root == NULL) return root;

    // Search Zone
    if (target < root->MTX) {
        root->left = DeleteZone(root->left, target);
    } else if (target > root->MTX) {
        root->right = DeleteZone(root->right, target);
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
            root->MTX = temp->MTX;
            root->right = DeleteZone(root->right, temp->MTX);
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

// Search Command - Return Height
Zone* SearchZone (Zone* root, int MTX) {
	if (root == NULL) {
		printf("Zona dengan MTX %d tidak ditemukan!\n", MTX);
		return NULL;
	}
	
	if (MTX == root->MTX) {
		printf("Zona dengan MTX %d ditemukan!\n", MTX);
		printf("Height: %d\n", root->height);
		return NULL;
	}
	
	if (MTX < root->MTX) {
        return SearchZone(root->left, MTX);
    } else {
        return SearchZone(root->right, MTX);
    }
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
    Core = GenerateZone(Core, 8000);
    Core = GenerateZone(Core, 7500);
    Core = GenerateZone(Core, 8500);
    Core = GenerateZone(Core, 7000);
    Core = GenerateZone(Core, 7700);
    
    printf("Preorder: ");
    Preorder(Core);
    printf("\n");

    printf("Inorder: ");
    Inorder(Core);
    printf("\n");

    printf("Postorder: ");
    Postorder(Core);
    printf("\n\n");
    
	Core = SearchZone(Core, 7500);
	Core = SearchZone(Core, 9900);	
    printf("\n\n");
    
    
    printf("Menghapus Zona 7500...\n");
	Core = DeleteZone(Core, 7500);
	
	printf("Preorder (after): ");
	Preorder(Core);
	printf("\n");
	
	ClearPlane(Core);
	Core = NULL;
	
	printf("Preorder (empty): ");
	Preorder(Core);
	printf("\n\n");

    return 0;
}

