#include <stdio.h>
#include <stdlib.h>

struct Zone {
	int MTX;
	Zone* left;
	Zone* right;
};

Zone* core = NULL;

Zone* createZone(int MTX) {
	Zone* zone = (Zone*) malloc (sizeof(Zone));
	zone->MTX = MTX;
	zone->left = NULL;
	zone->right = NULL;
	return zone;
}

Zone* minZone (Zone* root) {
	Zone* curr = root;
	while (curr->left) {
		curr = curr->left;
	}
	
	return curr;
}

Zone* generate (Zone* root, int MTX) {
	if (root == NULL) {
		root = createZone(MTX);
		return root;
	}
	
	if (MTX < root->MTX) {
		root->left = generate(root->left, MTX);
	} else if (MTX > root->MTX) {
		root->right = generate(root->right, MTX);
	} else {
		printf("Error: Same Zone detected\n");
		return root;
	}
	
	return root;
}

Zone* Search (int MTX) {
	Zone* root = core;
	
	while (root) {
		if (MTX < root->MTX) {
			root = root->left;
		} else if (MTX > root->MTX) {
			root = root->right;
		} else {
			return root;
		}
	}
	
	return NULL;
}

Zone* Delete (Zone* root, int MTX) {
	if (root == NULL) {
		printf("Zone not found\n");
		return root;
	}
	
	if (MTX < root->MTX) {
		root->left = Delete(root->left, MTX);
	} else if (MTX > root->MTX) {
		root->right = Delete(root->right, MTX);
	} else {
		if ((root->left == NULL) || (root->right == NULL)) {
			Zone* temp = (root->left == NULL) ? root->right : root->left;
			if (temp == NULL) {
				free(root);
				root = NULL;
			} else {
				// Anak Satu
				*root = *temp;
				printf("Zona anak 1\n");
			}
			free(temp);
			
		} else {
			// Anak Dua
			Zone* temp = minZone (root->right);
			root->MTX = temp->MTX;
			root->right = Delete(root->right, temp->MTX);
		}
	}
	
	return root;
}

void Preorder (Zone* root) {
	if (root == NULL) {
		return;
	}
	
	printf("Zone: %d\n", root->MTX);
	Preorder(root->left);
	Preorder(root->right);
}

void Inorder (Zone* root) {
	if (root == NULL) {
		return;
	}
	
	Inorder(root->left);
	printf("Zone: %d\n", root->MTX);
	Inorder(root->right);
}

void Postorder (Zone* root) {
	if (root == NULL) {
		return;
	}
	
	Postorder(root->left);
	Postorder(root->right);
	printf("Zone: %d\n", root->MTX);
}


void Clear (Zone* root) {
	if (root == NULL) {
		return;
	}
	
	Clear(root->left);
	Clear(root->right);
	free(root);
	root = NULL;
}


void ClearPlane () {
	Clear(core);
	core = NULL;
}

int main () {
	core = generate(core, 50);
	core = generate(core, 20);
	core = generate(core, 10);
	core = generate(core, 30);
	
	core = generate(core, 5);
	core = generate(core, 15);
	core = generate(core, 25);
	core = generate(core, 35);
	
	core = generate(core, 80);
	core = generate(core, 70);
	core = generate(core, 90);
	core = generate(core, 65);
	core = generate(core, 75);
	core = generate(core, 85);
	core = generate(core, 95);
	
	Inorder(core);
	
//	core = Delete(core, 95);
//	core = Delete(core, 30);
//	core = Delete(core, 80);
	
	core = Delete(core, 90);
	core = Delete(core, 95);
	core = Delete(core, 85);
	core = Delete(core, 80);
	core = Delete(core, 65);
	
//	ClearPlane();
	
	printf("\n\n");
	
	Inorder(core);
	
	return 0;
}
