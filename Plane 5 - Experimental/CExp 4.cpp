#include <stdio.h>
#include <stdlib.h>

// Zone Structure
struct Zone {
	int MTX;
	Zone* left = NULL;
	Zone* right = NULL;
	int height;
};

Zone* core = NULL;

Zone* Generate (int MTX) {
	Zone* newz = (Zone*) malloc (sizeof(Zone));
	newz->MTX = MTX;
	newz->left = NULL;
	newz->right = NULL;
	newz->height = 1;
	return newz;
}

// Support Command
int Height (Zone* root) {
	return (root == NULL) ? 0 : root->height;
}

int Balance (Zone* root) {
	return (root == NULL) ? 0 : (Height(root->left) - Height(root->right));
}

int max (int a, int b) {
	return (a > b) ? a : b;
}

Zone* minZone (Zone* root) {
	Zone* curr = root;
	while (curr->left != NULL) {
		curr = curr->left;
	} return curr;
}

// Standard Rotation
Zone* rotateLeft (Zone* a) {
	Zone* b = a->right;
	Zone* c = b->left;
	
	b->left = a;
	a->right = c;
	
	a->height = max(Height(a->left), Height(a->right)) + 1;
	b->height = max(Height(b->left), Height(b->right)) + 1;
	
	return b;
}

Zone* rotateRight (Zone* a) {
	Zone* b = a->left;
	Zone* c = b->right;
	
	b->right = a;
	a->left = c;
	
	a->height = max(Height(a->left), Height(a->right)) + 1;
	b->height = max(Height(b->left), Height(b->right)) + 1;
	
	return b;
}

// Main Command
Zone* InsertZone (Zone* root, int MTX) {
	if (root == NULL) {
		root = Generate(MTX);
		return root;
	}	
	
	if (MTX < root->MTX) {
		root->left = InsertZone(root->left, MTX);
	} else if (MTX > root->MTX) {
		root->right = InsertZone(root->right, MTX);
	} else {
		printf("Zona Duplikat terdeteksi!\n");
		return root;
	}
	
	root->height = max(Height(root->left), Height(root->right)) + 1;
	int balance = Balance(root);
	
	// Kasus LL
	if (balance > 1 && MTX < root->left->MTX) {
		return rotateRight(root);
	} 
	
	// Kasus RR
	if (balance < -1 && MTX > root->right->MTX) {
		return rotateLeft(root);
	}
	
	// Kasus LR
	if (balance > 1 && MTX > root->left->MTX) {
		root->left = rotateLeft(root->left);
		return rotateRight(root);
	} 
	
	// Kasus RL
	if (balance < -1 && MTX < root->right->MTX) {
		root->right = rotateRight(root->right);
		return rotateLeft(root);
	}
	
	return root;
}

Zone* DeleteZone (Zone* root, int MTX) {
	if (root == NULL) {
		printf("Zona tidak ditemukan!\n");
		return NULL;
	}
	
	if (MTX < root->MTX) {
		root->left = DeleteZone(root->left, MTX);
	} else if (MTX > root->MTX) {
		root->right = DeleteZone(root->right, MTX);
	} else {
		if ((root->left == NULL) || (root->right == NULL)) {
			Zone* temp = root->left ? root->left : root->right;
			if (temp == NULL) {
				temp = root;
				root = NULL;
			} else {
				*root = *temp;
			}
			free(temp);
			temp = NULL;
		} else {
			Zone* temp = minZone(root->right);
			root->MTX = temp->MTX;
			root->right = DeleteZone(root->right, temp->MTX);
		}
	}
	
	if (root == NULL) return root;
	
	root->height = max(Height(root->left), Height(root->right)) + 1;
	int balance = Balance(root);
	
	// Kasus LL
	if (balance > 1 && MTX < root->left->MTX) {
		return rotateRight(root);
	} 
	
	// Kasus RR
	if (balance < -1 && MTX > root->right->MTX) {
		return rotateLeft(root);
	}
	
	// Kasus LR
	if (balance > 1 && MTX > root->left->MTX) {
		root->left = rotateLeft(root->left);
		return rotateRight(root);
	} 
	
	// Kasus RL
	if (balance < -1 && MTX < root->right->MTX) {
		root->right = rotateRight(root->right);
		return rotateLeft(root);
	}
	
	return root;
}

int main () {
	return 0;
}

