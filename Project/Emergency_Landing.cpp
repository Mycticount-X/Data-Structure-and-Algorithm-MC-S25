#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Start Time: 6:00 
struct Plane {
	char id[51];
	double fuel;
	int dist;
	
	Plane* left;
	Plane* right;
	int height;
};

Plane* core = NULL;

Plane* Generate (char id[], double fuel, int dist) {
	Plane* newz = (Plane*) malloc (sizeof(Plane));
	strcpy(newz->id, id);
	newz->dist = dist;
	newz->fuel = fuel;
	newz->left = NULL;
	newz->right = NULL;
	newz->height = 1;
 return newz;
}

bool compare (Plane* a, double fuel, int dist) {
	if (a->fuel != fuel) {
		return (a->fuel > fuel);
	} else {
		return (a->dist > dist);
	}
}

int height (Plane* root) {
	return (root == NULL) ? 0 : root->height;
}

int balance (Plane* root) {
	return (root == NULL) ? 0 : (height(root->left) - height(root->right));
}

int findHeight (Plane* root) {
	if (root == NULL) return 0;
	return 1 + (((height(root->left) > height(root->right)) ? height(root->left) : height(root->right)));
}

Plane* minPlane (Plane* root) {
	Plane* curr = root;
	while (curr->left != NULL) {
		curr = curr->left;
	} return curr;
}

Plane* maxPlane (Plane* root) {
	Plane* curr = root;
	while (curr->right != NULL) {
		curr = curr->right;
	} return curr;
}

// Rotation
Plane* rotateLeft (Plane* root) {
	Plane* child = root->right;
	Plane* grand = child->left;
	
	child->left = root;
	root->right = grand;
	
	root->height = findHeight(root);
	child->height = findHeight(child);
	
	return child;
}

Plane* rotateRight (Plane* root) {
	Plane* child = root->left;
	Plane* grand = child->right;
	
	child->right = root;
	root->left = grand;
	
	root->height = findHeight(root);
	child->height = findHeight(child);
	
	return child;
}


Plane* Insert (Plane* root, char id[], double fuel, int dist) {
	if (root == NULL) {
		root = Generate(id, fuel, dist);
		return root;
	}
	
	if (root->fuel == fuel && root->dist == dist) {
		printf("Pesawat Duplikat terdeteksi!\n");
		return root;
	}
	
	if (compare(root, fuel, dist)) {
		root->left = Insert(root->left, id, fuel, dist);
	} else {
		root->right = Insert(root->right, id, fuel, dist);
	}
	
	// AVL
	root->height = findHeight(root);
	int bal = balance(root);
	
	// Rot
	
	// LL
	if (bal > 1 && balance(root->left) >= 0) {
		return rotateRight(root);
	}
	
	if (bal < -1 && balance(root->right) <= 0) {
		return rotateLeft(root);
	}
	
	if (bal > 1 && balance(root->left) > 0) {
		root->left = rotateLeft(root->left);
		return rotateRight(root);
	}
	
	if (bal < -1 && balance(root->right) < 0) {
		root->right = rotateRight(root->right);
		return rotateLeft(root);
	}
	return root;
}


Plane* Extract (Plane* root) {
	if (root == NULL) {
		printf("Pesawat tidak ditemukan!\n");
		return root;
	}
	
	if (root->left == NULL) {
		Plane* temp = root->right;
		free(root);
		return temp;
	}
	
	root->left = Extract(root->left);
	
	// AVL
	root->height = findHeight(root);
	int bal = balance(root);
	
	// Rot
	
	// LL
	if (bal > 1 && balance(root->left) >= 0) {
		return rotateRight(root);
	}
	
	if (bal < -1 && balance(root->right) <= 0) {
		return rotateLeft(root);
	}
	
	if (bal > 1 && balance(root->left) < 0) {
		root->left = rotateLeft(root->left);
		return rotateRight(root);
	}
	
	if (bal < -1 && balance(root->right) > 0) {
		root->right = rotateRight(root->right);
		return rotateLeft(root);
	}
	return root;
}

void Manage (char order[]) {
	char id[50];
	int dist;
	double fuel;
	int size;
	
	if (strcmpi(order, "I") == 0) {
		scanf("%s %lf %d", id, &fuel, &dist);
		core = Insert(core, id, fuel, dist);
		
	} else if (strcmpi(order, "E") == 0) {
		scanf("%d", &size);
		for (int i = 0; i < size; i++) core = Extract(core);
	} else {
		printf("Invalid Input!\n");
	}
	
	
}

void Inorder (Plane* root) {
	if (root == NULL) return;
	Inorder(root->left);
	printf("%s ", root->id);
	Inorder(root->right);
}

void Solver () {
	int command = 0;
	char order[50];
	printf("Command Size: ");
	scanf("%d", &command);
	
	for (int i = 1; i <= command; i++) {
		printf("Command #%d: ", i);
		scanf(" %s ", order);
		Manage(order);
	}
	
	Inorder(core);
}

// Quizz 1
int main () {
	Solver();
    return 0;
}
