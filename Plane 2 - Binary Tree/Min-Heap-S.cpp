#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Zone {
	int MTX;
	Zone *left, *right, *parent;
};

struct Queue {
	Zone *zone;
	Queue *next;
};

Queue *head = NULL, *tail = NULL;

void Push(Queue *newZone) {
	if (!tail) {
		head = tail = newZone;
	} else {
		tail->next = newZone;
		tail = newZone;
	}
}

void Pop() {
	if (head == tail) {
		free(head);
		head = tail = NULL;
	} else {
		struct Queue *tmp = head;
		head = head->next;
		free(tmp);
	}
}

Queue* Generate(Zone *curr) {
	Queue *newque = (Queue*) malloc(sizeof(Queue));
	newque->zone = curr;
	newque->next = NULL;
	return newque;
}

Zone* GenerateZone(int MTX, Zone *parent) {
	Zone *newZone = (Zone*) malloc(sizeof(Zone));
	newZone->MTX = MTX;
	newZone->left = newZone->right = NULL;
	newZone->parent = parent;
	return newZone;
}

void upHeap(Zone *curr) {
	if (!curr || !curr->parent) return;

	if (curr->MTX < curr->parent->MTX) {
		int tmp = curr->MTX;
		curr->MTX = curr->parent->MTX;
		curr->parent->MTX = tmp;
		upHeap(curr->parent);
	}
}

void downHeap(Zone *curr) {
	if (!curr) return;

	Zone *smallest = curr;

	if (curr->left && curr->left->MTX < smallest->MTX) {
		smallest = curr->left;
	}
	if (curr->right && curr->right->MTX < smallest->MTX) {
		smallest = curr->right;
	}

	if (smallest != curr) {
		int tmp = curr->MTX;
		curr->MTX = smallest->MTX;
		smallest->MTX = tmp;
		downHeap(smallest);
	}
}

Zone* Insert(Zone *curr, int x, Zone *parent) {
	Zone *newZone = GenerateZone(x, NULL);

	if (!curr) {
		newZone->parent = NULL;
		return newZone;
	}

	head = tail = NULL;
	Push(Generate(curr));

	while (head) {
		Zone *temp = head->zone;

		if (!temp->left) {
			temp->left = newZone;
			newZone->parent = temp;
			upHeap(newZone);
			break;
		} else {
			Push(Generate(temp->left));
		}

		if (!temp->right) {
			temp->right = newZone;
			newZone->parent = temp;
			upHeap(newZone);
			break;
		} else {
			Push(Generate(temp->right));
		}

		Pop();
	}

	while (head) Pop();
	return curr;
}

Zone* Delete(Zone *curr) {
	if (!curr) return NULL;

	head = tail = NULL;
	Push(Generate(curr));
	Zone *last = NULL;

	while (head) {
		last = head->zone;
		if (head->zone->left) Push(Generate(head->zone->left));
		if (head->zone->right) Push(Generate(head->zone->right));
		Pop();
	}

	if (last == curr) {
		free(curr);
		return NULL;
	}

	curr->MTX = last->MTX;

	if (last->parent->left == last) {
		last->parent->left = NULL;
	} else {
		last->parent->right = NULL;
	}
	free(last);

	downHeap(curr);
	return curr;
}

void ViewPlane(Zone *curr) {
	if (!curr) {
		printf("Permukaan saat ini kosong\n");
		return;
	}

	head = tail = NULL;
	Push(Generate(curr));

	while (head) {
		printf("Zone: %d\n", head->zone->MTX);
		if (head->zone->left) Push(Generate(head->zone->left));
		if (head->zone->right) Push(Generate(head->zone->right));
		Pop();
	}
}

int main() {
	Zone *root = NULL;

	root = Insert(root, 13, root);
	root = Insert(root, 12, root);
	root = Insert(root, 7, root);
	root = Insert(root, 9, root);
	root = Insert(root, 11, root);

	ViewPlane(root); printf("\n");

	root = Delete(root); ViewPlane(root); printf("\n");
	root = Delete(root); ViewPlane(root); printf("\n");
	root = Delete(root); ViewPlane(root); printf("\n");
	root = Delete(root); ViewPlane(root); printf("\n");
	root = Delete(root); ViewPlane(root); printf("\n");

	return 0;
}
