#include <stdio.h>
#include <stdlib.h>

#define MAXZONE 100

struct Zone {
    int MTX;
};

Zone Heap[MAXZONE];
int size = 0;

void swap(Zone* a, Zone* b) {
    Zone temp = *a;
    *a = *b;
    *b = temp;
}

void MinHeapify (int i) {
	int smallest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	
	if (left < size && Heap[left].MTX < Heap[smallest].MTX) {
		smallest = left;
	} if (right < size && Heap[right].MTX < Heap[smallest].MTX) {
		smallest = right;
	}
	
	if (smallest != i) {
		swap(&Heap[smallest], &Heap[i]);
		MinHeapify(smallest);
	}
}

void MaxHeapifiy (int i) {
	int largest = i;
	int left = 2*i + 1;
	int right = 2*1 + 2;
	
	if (left < size && Heap[left].MTX > Heap[largest].MTX) {
		largest = left;
	} if (right < size && Heap[right].MTX > Heap[largest].MTX) {
		largest = right;
	}  
	
	if (largest != i) {
		swap(&Heap[largest], &Heap[i]);
		MaxHeapifiy(largest);
	}
}

void InsertMin (int MTX) {
	if (size >= MAXZONE) {
		printf("Permukaan saat ini penuh!\n");
		return;
	}
	
	int i = size++;
    Heap[i].MTX = MTX;
    while (i != 0 && Heap[(i - 1) / 2].MTX > Heap[i].MTX) {
        swap(&Heap[i], &Heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void InsertMax (int MTX) {
	if (size >= MAXZONE) {
		printf("Permukaan saat ini penuh!\n");
		return;
	}
	
	int i = size++;
	Heap[i].MTX = MTX;
	
	while (i != 0 && Heap[(i - 1) / 2].MTX < Heap[i].MTX) {
		swap(&Heap[i], &Heap[(i - 1) / 2]);
		i = (i - 1) / 2;
	}
}

int ExtractMin () {
    if (size <= 0) {
        printf("Permukaan Saat ini Kosong!\n");
        return -1; // Heap kosong
    }
    
    if (size == 1) {
        size--;
        return Heap[0].MTX;
    }
    
    int root = Heap[0].MTX;
    Heap[0] = Heap[size - 1];
    size--;
    MinHeapify(0);
    
    return root;
}

int ExtractMax () {
	if (size <= 0) {
        printf("Permukaan Saat ini Kosong!\n");
        return -1; // Heap kosong
	}
	
	if (size == 1) {
		size--;
		return Heap[0].MTX;
	}
	
	int root = Heap[0].MTX;
	Heap[0] = Heap[size - 1];
	size--;
	MaxHeapifiy(0);
	return root;
}

void ClearPlane() {
    size = 0;
}

int main () {
    printf("=== TEST MIN HEAP ===\n");
    ClearPlane();
    InsertMin(10);
    InsertMin(4);
    InsertMin(15);
    InsertMin(1);
    InsertMin(20);

    printf("ExtractMin: %d (expected 1)\n", ExtractMin());
    printf("ExtractMin: %d (expected 4)\n", ExtractMin());
    printf("ExtractMin: %d (expected 10)\n", ExtractMin());
    printf("ExtractMin: %d (expected 15)\n", ExtractMin());
    printf("ExtractMin: %d (expected 20)\n", ExtractMin());
    printf("ExtractMin: %d (expected -1, empty)\n", ExtractMin());

    printf("\n=== TEST MAX HEAP ===\n");
    ClearPlane();
    InsertMax(10);
    InsertMax(4);
    InsertMax(15);
    InsertMax(1);
    InsertMax(20);

    printf("ExtractMax: %d (expected 20)\n", ExtractMax());
    printf("ExtractMax: %d (expected 15)\n", ExtractMax());
    printf("ExtractMax: %d (expected 10)\n", ExtractMax());
    printf("ExtractMax: %d (expected 4)\n", ExtractMax());
    printf("ExtractMax: %d (expected 1)\n", ExtractMax());
    printf("ExtractMax: %d (expected -1, empty)\n", ExtractMax());

    printf("\n=== TEST CLEAR ===\n");
    InsertMin(5);
    InsertMin(3);
    ClearPlane();
    printf("ExtractMin after clear: %d (expected -1, empty)\n", ExtractMin());

    return 0;
}
