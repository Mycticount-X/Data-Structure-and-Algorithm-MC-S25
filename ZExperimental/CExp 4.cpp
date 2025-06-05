#include <stdio.h>
#include <stdlib.h>

// Time Start: 3:35

struct Zone {
	int MTX;
	Zone* left;
	Zone* right;
	int height;
};

Zone* core = NULL;

Zone* Generate (int MTX) {
	Zone* newz = (Zone*) malloc(sizeof(Zone));
	newz->MTX = MTX;
	newz->left = NULL;
	newz->right = NULL;
	newz->height = 1;
	return newz;
}

// Standart AVl
int height (Zone* root) {
	return (root == NULL) ? 0 : root->height;
}

int balance (Zone* root) {
	return (root == NULL) ? 0 : (height(root->left) - height(root->right));
}

int findHeight (Zone* root) {
	return 1 + ((height(root->left) > height(root->right)) ? height(root->left) : height(root->right));
}

Zone* minZone (Zone* root) {
	Zone* curr = root;
	while (curr->left != NULL) {
		curr = curr->left;
	} return curr;
}

// Standard Rotation
Zone* rotateLeft (Zone* root) {
	Zone* child = root->right;
	Zone* grand = child->left;
	
	child->left = root;
	root->right = grand;
	
	root->height = findHeight(root);
	child->height = findHeight(child);
	
	return child;
}

Zone* rotateRight (Zone* root) {
	Zone* child = root->left;
	Zone* grand = child->right;
	
	child->left = root;
	root->right = grand;
	
	root->height = findHeight(root);
	child->height = findHeight(child);
	
	return child;
}

// Main Command
Zone* Insert (Zone* root, int MTX) {
	if (root == NULL) {
		root = Generate(MTX);
		return root;
	}
	
	if (MTX < root->MTX) {
		root->left = Insert(root->left, MTX);
	} else if (MTX > root->MTX) {
		root->right = Insert(root->right, MTX);
	} else {
		printf("Zona Duplikat Terdeteksi!\n");
		return root;
	}
	
	// AVL Here
	root->height = findHeight(root);
	int bal = balance(root);
	
	// LL
	if (bal > 1 && MTX < root->left->MTX) {
		return rotateRight(root);
	}
	
	// RR
	if (bal < -1 && MTX > root->right->MTX) {
		return rotateLeft(root);
	}
	
	// LR
	if (bal > 1 && MTX > root->left->MTX) {
		root->left = rotateLeft(root->left);
		return rotateRight(root);
	}
	
	// RL
	if (bal < -1 && MTX < root->left->MTX) {
		root->right = rotateRight(root->right);
		return rotateLeft(root);
	}
	
	return root;
}

Zone* Delete (Zone* root, int MTX) {
	if (root == NULL) {
		printf("Zona tidak ditemukan!\n");
		return root;
	}
	
	if (MTX < root->MTX) {
		root->left = Delete(root->left, MTX);
	} else if (MTX > root->MTX) {
		root->right = Delete(root->right, MTX);
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
		} else {
			Zone* temp = minZone(root->right);
			root->MTX = temp->MTX;
			root->right = Delete(root->right, temp->MTX);
		}
	}
	
	// AVL Here
	if (root == NULL) return root;
	root->height = findHeight(root);
	int bal = balance(root);
	
	// LL
	if (bal > 1 && balance(root->left) >= 0) {
		return rotateRight(root);
	}
	
	// RR
	if (bal < -1 && balance(root->right) >= 0) {
		return rotateLeft(root);
	}
	
	// LR
	if (bal > 1 && balance(root->left) < 0) {
		root->left = rotateLeft(root->left);
		return rotateRight(root);
	}
	
	// RL
	if (bal < -1 && balance(root->right) < 0) {
		root->right = rotateRight(root->right);
		return rotateLeft(root);
	}
	
	return root;
}

void Inorder (Zone* root) {
	if (root == NULL) return;
	Inorder(root->left);
	printf("Zone  : %d \n", root->MTX);
	printf("Height: %d\n\n", root->height);
	Inorder(root->right);
} 

int main () {
	core = Insert(core, 0);
	core = Insert(core, 25);
	core = Insert(core, 40);
	core = Insert(core, 50);
	core = Insert(core, 60);
	core = Insert(core, 75);
	core = Insert(core, 100);
	core = Insert(core, 50);
	
	Inorder(core);
	
	core = Delete(core, 50);
	core = Delete(core, 100);
	core = Delete(core, 25);
	core = Delete(core, 50);
	
	Inorder(core);
	return 0;
}

// Time End: 4:10 (35 min)
