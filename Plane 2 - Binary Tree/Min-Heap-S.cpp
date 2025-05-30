#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Zone Structure
typedef struct Zone {
    int MTX;
    Zone* left;
    Zone* right;
    Zone* parent;
} Zone;

// Heap Structure
typedef struct {
    Zone* root;
    int size;
} MinHeap;

Zone* GenerateZone(int MTX) {
    Zone* newz = (Zone*)malloc(sizeof(Zone));
    newz->MTX = MTX;
    newz->left = NULL;
    newz->right = NULL;
    newz->parent = NULL;
    return newz;
}

MinHeap* GenerateHeap() {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->root = NULL;
    heap->size = 0;
    return heap;
}

// Support Function
void swapValues(Zone* a, Zone* b) {
    int temp = a->MTX;
    a->MTX = b->MTX;
    b->MTX = temp;
}

void HeapifyUp(Zone* zone) {
    if (zone->parent == NULL) return;
    
    if (zone->MTX < zone->parent->MTX) {
        swapValues(zone, zone->parent);
        HeapifyUp(zone->parent);
    }
}

void HeapifyDown(Zone* zone) {
    while (zone != NULL) {
        Zone* smallest = zone;

        if (zone->left && zone->left->MTX < smallest->MTX)
            smallest = zone->left;
        if (zone->right && zone->right->MTX < smallest->MTX)
            smallest = zone->right;

        if (smallest == zone)
            break;

        swapValues(zone, smallest);
        zone = smallest;
    }
}

int getMin(MinHeap* heap) {
    if (heap->root == NULL) {
        printf("Heap is empty!\n");
        return -1;
    }
    return heap->root->MTX;
}

Zone* ParentNewZone(MinHeap* heap) {
    if (heap->size == 0) return NULL;

    int index = heap->size + 1;
    int level = (int)log2(index);
    int steps[level]; 

    int temp = index;
    for (int i = level - 2; i >= 0; i--) {
        steps[i] = temp % 2;  // 0 = kiri, 1 = kanan
        temp /= 2;
    }

    Zone* current = heap->root;
    for (int i = 0; i < level - 1; i++) {
        if (steps[i] == 0)
            current = current->left;
        else
            current = current->right;

        if (current == NULL) return NULL;  // safety check
    }

    return current;
}

Zone* ZonebyIndex(MinHeap* heap, int index) {
    if (index == 1) return heap->root;

    int level = (int)log2(index);
    // steps: 0 = left, 1 = right
    int steps[level];
    int temp = index;

    // Backtrack
    for (int i = level - 1; i >= 0; i--) {
        steps[i] = temp % 2;  // 0 = left, 1 = right
        temp /= 2;
    }

    // Navigasi
    Zone* current = heap->root;
    for (int i = 0; i < level; i++) {
        if (steps[i] == 0) {
            current = current->left;
        } else {
            current = current->right;
        }
        if (current == NULL) return NULL;  // Invalid path
    }

    return current;
}

// Insert Command
void InsertZone(MinHeap* heap, int MTX) {
    Zone* newNode = GenerateZone(MTX);
    heap->size++;
    
    if (heap->root == NULL) {
        heap->root = newNode;
        return;
    }
    
    Zone* parent = ParentNewZone(heap);
    
    if (parent->left == NULL) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
    newNode->parent = parent;
    
    HeapifyUp(newNode);
}

// Extract Command
int ExtractMin(MinHeap* heap) {
    if (heap->root == NULL) {
        printf("Heap is empty!\n");
        return -1;
    }
    
    int minValue = heap->root->MTX;
    
    if (heap->size == 1) {
        free(heap->root);
        heap->root = NULL;
        heap->size = 0;
        return minValue;
    }
    
    Zone* lastNode = ZonebyIndex(heap, heap->size);
    Zone* lastNodeParent = lastNode->parent;
    heap->root->MTX = lastNode->MTX;
    
    // Delete the last Zone
    if (lastNodeParent->right != NULL) {
        free(lastNodeParent->right);
        lastNodeParent->right = NULL;
    } else {
        free(lastNodeParent->left);
        lastNodeParent->left = NULL;
    }
    
    heap->size--;
    HeapifyDown(heap->root);
    return minValue;
}

// Alter Command
void AlterSupport(Zone* node) {
    if (node == NULL) return;
    
    AlterSupport(node->left);
    AlterSupport(node->right);
    free(node);
}

void ClearPlane(MinHeap* heap) {
    AlterSupport(heap->root);
    free(heap);
}

void ViewSupport(Zone* node, int level) {
    if (node == NULL) return;
    
    for (int i = 0; i < level; i++) printf("  ");
    printf("%d\n", node->MTX);
    
    ViewSupport(node->left, level + 1);
    ViewSupport(node->right, level + 1);
}

void ViewPlane(MinHeap* heap) {
    printf("Min Heap (size: %d):\n", heap->size);
    ViewSupport(heap->root, 0);
    printf("\n");
}

int main() {
    MinHeap* heap = GenerateHeap();
    
    InsertZone(heap, 5);
    InsertZone(heap, 3);
    InsertZone(heap, 8);
    InsertZone(heap, 1);
    InsertZone(heap, 4);
    InsertZone(heap, 7);
    
    ViewPlane(heap);
    
    printf("Extracted min: %d\n", ExtractMin(heap));
    ViewPlane(heap);
    
    printf("Current min: %d\n", getMin(heap));
    
    InsertZone(heap, 2);
    ViewPlane(heap);
    
    ClearPlane(heap);
    return 0;
}