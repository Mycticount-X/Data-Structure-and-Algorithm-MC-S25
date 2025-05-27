#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Node Structure
typedef struct Zone {
    int value;
    struct Zone* left;
    struct Zone* right;
    struct Zone* parent;
} Zone;

// Heap Structure
typedef struct {
    Zone* root;
    int size;
} MinHeap;

Zone* createNode(int value) {
    Zone* newNode = (Zone*)malloc(sizeof(Zone));
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    return newNode;
}

MinHeap* createMinHeap() {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->root = NULL;
    heap->size = 0;
    return heap;
}

// Support Function
void swapValues(Zone* a, Zone* b) {
    int temp = a->value;
    a->value = b->value;
    b->value = temp;
}

void heapifyUp(Zone* node) {
    if (node->parent == NULL) return;
    
    if (node->value < node->parent->value) {
        swapValues(node, node->parent);
        heapifyUp(node->parent);
    }
}

void heapifyDown(Zone* node) {
    if (node == NULL) return;
    
    Zone* smallest = node;
    
    if (node->left != NULL && node->left->value < smallest->value) {
        smallest = node->left;
    }
    
    if (node->right != NULL && node->right->value < smallest->value) {
        smallest = node->right;
    }
    
    if (smallest != node) {
        swapValues(node, smallest);
        heapifyDown(smallest);
    }
}

Zone* findParentForNewNode(MinHeap* heap) {
    if (heap->size == 0) return NULL;
    
    int size = heap->size + 1;
    Zone* current = heap->root;
    
    // Cari posisi parent berdasarkan representasi biner dari size
    unsigned mask = 1 << (31 - __builtin_clz(size));
    mask >>= 1;
    
    while (mask > 1) {
        if (size & mask) {
            current = current->right;
        } else {
            current = current->left;
        }
        mask >>= 1;
    }
    
    return current;
}

// Insert Command
void insert(MinHeap* heap, int value) {
    Zone* newNode = createNode(value);
    heap->size++;
    
    if (heap->root == NULL) {
        heap->root = newNode;
        return;
    }
    
    Zone* parent = findParentForNewNode(heap);
    
    if (parent->left == NULL) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
    newNode->parent = parent;
    
    heapifyUp(newNode);
}

// Extract Command
int extractMin(MinHeap* heap) {
    if (heap->root == NULL) {
        printf("Heap is empty!\n");
        return -1;
    }
    
    int minValue = heap->root->value;
    
    if (heap->size == 1) {
        free(heap->root);
        heap->root = NULL;
        heap->size = 0;
        return minValue;
    }
    
    // Temukan node terakhir
    Zone* lastNodeParent = findParentForNewNode(heap);
    Zone* lastNode = (lastNodeParent->right != NULL) ? lastNodeParent->right : lastNodeParent->left;
    
    // Pindahkan nilai node terakhir ke root
    heap->root->value = lastNode->value;
    
    // Hapus node terakhir
    if (lastNodeParent->right != NULL) {
        free(lastNodeParent->right);
        lastNodeParent->right = NULL;
    } else {
        free(lastNodeParent->left);
        lastNodeParent->left = NULL;
    }
    
    heap->size--;
    
    // Lakukan heapify down
    heapifyDown(heap->root);
    
    return minValue;
}

// Fungsi untuk mendapatkan nilai minimum tanpa menghapus
int getMin(MinHeap* heap) {
    if (heap->root == NULL) {
        printf("Heap is empty!\n");
        return -1;
    }
    return heap->root->value;
}

// Fungsi untuk mencetak heap (pre-order traversal)
void printHeapHelper(Zone* node, int level) {
    if (node == NULL) return;
    
    for (int i = 0; i < level; i++) printf("  ");
    printf("%d\n", node->value);
    
    printHeapHelper(node->left, level + 1);
    printHeapHelper(node->right, level + 1);
}

void printHeap(MinHeap* heap) {
    printf("Min Heap (size: %d):\n", heap->size);
    printHeapHelper(heap->root, 0);
    printf("\n");
}

// Fungsi untuk menghapus heap dan membebaskan memori
void freeHeapHelper(Zone* node) {
    if (node == NULL) return;
    
    freeHeapHelper(node->left);
    freeHeapHelper(node->right);
    free(node);
}

void freeMinHeap(MinHeap* heap) {
    freeHeapHelper(heap->root);
    free(heap);
}

int main() {
    MinHeap* heap = createMinHeap();
    
    insert(heap, 5);
    insert(heap, 3);
    insert(heap, 8);
    insert(heap, 1);
    insert(heap, 4);
    insert(heap, 7);
    
    printHeap(heap);
    
    printf("Extracted min: %d\n", extractMin(heap));
    printHeap(heap);
    
    printf("Current min: %d\n", getMin(heap));
    
    insert(heap, 2);
    printHeap(heap);
    
    freeMinHeap(heap);
    return 0;
}