#include <stdio.h>

#define MAX 1000

int Heap[MAX];
int zone = 0;

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void Generate (int MTX) {
    if (zone >= MAX) {
        printf("Zone limit reached.\n");
        return;
    }

    Heap[zone] = MTX;
    int curr = zone;
    zone++;

    while (curr > 0 && Heap[curr] > Heap[(curr - 1) / 2]) {
        swap(&Heap[curr], &Heap[(curr - 1) / 2]);
        curr = (curr - 1) / 2;
    }
}

int ExtractMax () {
    if (zone == 0) {
        printf("Heap is empty.\n");
        return -1;
    }

    int max = Heap[0];
    Heap[0] = Heap[zone - 1];
    zone--;

    int curr = 0;
    while (curr < zone) {
        int left = 2 * curr + 1;
        int right = 2 * curr + 2;
        int largest = curr;

        if (left < zone && Heap[left] > Heap[largest]) {
            largest = left;
        }
        if (right < zone && Heap[right] > Heap[largest]) {
            largest = right;
        }
        if (largest != curr) {
            swap(&Heap[curr], &Heap[largest]);
            curr = largest;
        } else {
            break;
        }
    }

    return max;
}

int Search (int MTX) {
    for (int i = 0; i < zone; i++) {
        if (Heap[i] == MTX) {
            return i;
        }
    }
    return -1; // Not found
}

void Delete (int MTX) {
    int index = Search(MTX);
    if (index == -1) {
        printf("Element %d not found in the heap.\n", MTX);
        return;
    }

    Heap[index] = Heap[zone - 1];
    zone--;

    int curr = index;
    while (curr < zone) {
        int left = 2 * curr + 1;
        int right = 2 * curr + 2;
        int largest = curr;

        if (left < zone && Heap[left] > Heap[largest]) {
            largest = left;
        }
        if (right < zone && Heap[right] > Heap[largest]) {
            largest = right;
        }
        if (largest != curr) {
            swap(&Heap[curr], &Heap[largest]);
            curr = largest;
        } else {
            break;
        }
    }
}

void PrintHeap () {
    if (zone == 0) {
        printf("Heap is empty.\n");
        return;
    }

    printf("Max Heap: ");
    for (int i = 0; i < zone; i++) {
        printf("%d ", Heap[i]);
    }
    printf("\n");
}

int main () {
    Generate(888);
    Generate(10);
    Generate(20);
    Generate(5);
    Generate(30);
    PrintHeap();
    printf("Extracted Max: %d\n", ExtractMax());
    return 0;
}