#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
	int val;
	Node* left;
	Node* right;
};

Node* core = NULL;

Node* Create (int val) {
	Node* node = (Node*) malloc (sizeof(Node));
	node->val = val;
	node->left = NULL;
	node->right = NULL;
	return node;
}

// Helper Function
Node* minNode (Node* root) {
	Node* curr = root;
	while (curr->left) {
		curr = curr->left;
	}
	
	return curr;
}

Node* Generate (Node* root, int val) {
	if (root == NULL) {
		root = Create(val);
		return root;
	}
	
	if (val < root->val) {
		root->left = Generate(root->left, val);
	} else if (val > root->val) {
		root->right = Generate(root->right, val);
	} else {
		printf("Node yang sama terdeteksi!\n");
		printf("Menjalankan fungsi rollback!\n");
	}
	
	return root;
}

Node* Delete (Node* root, int val) {
	if (root == NULL) {
		printf("Node tidak ditemukan!\n");
		printf("Menjalankan fungsi rollback!\n");
		return NULL;
	}
	
	if (val < root->val) {
		root->left = Delete(root->left, val);
	} else if (val > root->val) {
		root->right = Delete(root->right, val);
	} else {
		// Target ditemukan
		
		// Node Tanpa Anak
		if ((root->left == NULL) && (root->right == NULL)) {
			free(root);
			root = NULL;
		}
		
		// Node Anak Satu
		else if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
		
		// Node Anak Dua (KB)
		else {
			Node* succesor = minNode(root->right);
			root->val = succesor->val;
			root->right = Delete(root->right, succesor->val);
		}
		
//		
//		// Node Dengan Satu Anak (Kiri atau Kanan)
//        else if (root->left == NULL) {
//            Node* temp = root->right;
//            free(root);
//            return temp;
//        } else if (root->right == NULL) {
//            Node* temp = root->left;
//            free(root);
//            return temp;
//        }
//
//        // Node Dengan Dua Anak
//        else {
//            Node* succesor = minNode(root->right);  // Cari pengganti dari subtree kanan
//            root->val = succesor->val;  // Salin nilai suksesor ke root
//            root->right = Delete(root->right, succesor->val);  // Hapus suksesor dari subtree kanan
//        }
		
	}
	
	return root;
}

void Inorder (Node* curr) {
	if (curr == NULL) {
		return;
	}
	
	Inorder (curr->left);
	printf("Node: %d\n", curr->val);
	Inorder (curr->right);
}

void Preorder (Node* curr) {
	if (curr == NULL) {
		return;
	}
	
	printf("Node: %d\n", curr->val);
	Preorder (curr->left);
	Preorder (curr->right);
}

void Postorder (Node* curr) {
	if (curr == NULL) {
		return;
	}
	
	Postorder (curr->left);
	Postorder (curr->right);
	printf("Node: %d\n", curr->val);
}
 

int main () {
	// Case 1
	core = Generate(core, 25);
	core = Generate(core, 50);
	core = Generate(core, 75);
	core = Generate(core, 125);
	
	Inorder(core);
	printf("\n");
	
	// Case 2
	core = Generate(core, 125);
	core = Delete(core, 125);
	core = Generate(core, 125);
	
	Preorder(core);
	printf("\n");
	
	// Case 3
	core = Generate(core, 40);
	core = Generate(core, 60);
	core = Delete(core, 50);
	
	Postorder(core);
	printf("\n");
	
	return 0;
}
