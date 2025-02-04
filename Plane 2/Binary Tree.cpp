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

// Secondary Function
Zone* MinZone (Zone* root) {
	while (root->left) {
		root = root->left;
	}
	
	return root;
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

// Delete Command
Zone* DeleteZone (Zone* root, int MTX) {
	if (Core == NULL) {
		printf("Permukaan ini kosong!\n");
		return NULL;
	}
	
	// Search Zone
	if (MTX < root->MTX) {
		root->left = DeleteZone(root->left, MTX);
	} else if (MTX > root->MTX) {
		root->right = DeleteZone(root->right, MTX);		
	} else {
		// Kasus 1: Target adalah daun
		if (root->left == NULL && root->right == NULL) {
			free(root);
			root = NULL;
			return root;
		}
		
		// Kasus 2: Zona anak satu
		else if (root->left == NULL) {
            Zone *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Zone *temp = root->left;
            free(root);
            return temp;
        }
        
        // Kasus 3: Zona anak kembar
        else {
        	Zone* temp = MinZone(root->right);
        	root->MTX = temp->MTX;
        	root->right = DeleteZone(root->right, root->MTX);
		}
		
	}
	
	return root;
}

// Helper Function
void Delete (int MTX) {
	Core = DeleteZone(Core, MTX);
}

// Alter Command
void ClearTree(Zone *root) {
    if (root == NULL) return;

    // Postorder Traversal
    ClearTree(root->left);
    ClearTree(root->right);

    printf("Menghapus node: %d\n", root->MTX);
    free(root);
}

void ClearPlane() {
    if (Core == NULL) {
        printf("Permukaan sudah kosong!\n");
        return;
    }

    ClearTree(Core);
    Core = NULL;
    printf("Seluruh zona telah dihapus.\n");
}

// Traversal Ordering
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

// Main Function
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
    ClearPlane();
    
    
    
    // TEST CASE 1: Menghapus tree dengan beberapa node
    printf("\n=== TEST CASE 1: Menghapus tree dengan beberapa node ===\n");
    GenerateZone(8000);
    GenerateZone(7500);
    GenerateZone(8500);
    GenerateZone(7000);
    GenerateZone(7700);

    printf("Inorder Sebelum ClearPlane: ");
    Inorder(Core);
    printf("\n");

    ClearPlane(); // Menghapus tree pertama

    printf("Inorder Setelah ClearPlane: ");
    Inorder(Core); // Harus kosong
    printf("\n");

    // TEST CASE 2: Menghapus tree kosong
    printf("\n=== TEST CASE 2: Menghapus tree kosong ===\n");
    ClearPlane(); // Harus menampilkan pesan "Permukaan sudah kosong!"

    // TEST CASE 3: Menambahkan node setelah ClearPlane
    printf("\n=== TEST CASE 3: Menambahkan node setelah ClearPlane ===\n");
    GenerateZone(9000);
    GenerateZone(8500);
    GenerateZone(9500);

    printf("Inorder Setelah Menambahkan Kembali: ");
    Inorder(Core);
    printf("\n");


    return 0;
}

