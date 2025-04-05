#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
	int key;
	struct node *left;
	struct node *right;
} *root;

bool search(struct node *curr, int find){
	//COMPLETE THE CODE!
	node* temp = curr;
	while (temp) {
		if (find < temp->key) {
			temp = temp->left;
		} else if (find > temp->key) {
			temp = temp->right;
		} else {
			return true;
		}
	}
	return false;
}

int heightBinaryTree(struct node *node){
	//COMPLETE THE CODE!
	if (node == NULL) {
		return 0;
	}
	
	int left = heightBinaryTree(node->left);
	int right = heightBinaryTree(node->right);
	return 1 + (left > right ? left : right);
}

int main () {
	return 0;
}
