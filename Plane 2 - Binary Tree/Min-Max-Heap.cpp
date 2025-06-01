#include <stdio.h>
#include <stdio.h>
#include <math.h>

#define MAX_SIZE 100

int Heap[MAX_SIZE];
int size = 0;

// Support Functions
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int getLevel(int index) {
    return (int)log2(index + 1);
}

int getParent(int index) {
    return (index - 1) / 2;
}

int getGrandParent(int index) {
    return (index - 1) / 2 / 2;
}

// Push Command
void PushUpMin (int index) {
    int gp = getGrandParent(index);
    if (gp >= 0 && Heap[index] < Heap[gp]) {
        swap(&Heap[index], &Heap[gp]);
        PushUpMin(gp);
    }
}

void PushUpMax(int index) {
    int gp = getGrandParent(index);
    if (gp >= 0 && Heap[index] > Heap[gp]) {
        swap(&Heap[index], &Heap[gp]);
        PushUpMax(gp);
    }
}

// Insert Command
void InsertZone (int MTX) {
    if (size >= MAX_SIZE) {
        printf("Permukaan saat ini penuh!\n");
        return;
    }

    Heap[size] = MTX;
    int i = size;
    int parent = getParent(i);
    int level = getLevel(i);

    if (i == 0) {
        // Root
    } else if (level % 2 == 0) {
        // Min level
        if (Heap[i] > Heap[parent]) {
            swap(&Heap[i], &Heap[parent]);
            PushUpMax(parent);
        } else {
            PushUpMin(i);
        }
    } else {
        // Max level
        if (Heap[i] < Heap[parent]) {
            swap(&Heap[i], &Heap[parent]);
            PushUpMin(parent);
        } else {
            PushUpMax(i);
        }
    }

    size++;
}

void ViewPlane () {
    printf("Min-Max Heap: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", Heap[i]);
    }
    printf("\n");
}

int main () {
    InsertZone(10);
    InsertZone(5);
    InsertZone(20);
    InsertZone(3);
    InsertZone(8);
    InsertZone(15);
    InsertZone(30);

    ViewPlane();
    return 0;
}