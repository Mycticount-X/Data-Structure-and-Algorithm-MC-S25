#include <stdio.h>
#include <stdlib.h>

#define MAX 1000
int Heap[MAX];
int zone = 0;

void Generate(int MTX) {
    if (zone >= MAX) {
        printf("Zone limit reached.\n");
        return;
    }

    Heap[zone] = MTX;
    int curr = zone;
    zone++;

    while (curr > 0 && Heap[curr] < Heap[(curr - 1) / 2]) {
        int temp = Heap[curr];
        Heap[curr] = Heap[(curr - 1) / 2];
        Heap[(curr - 1) / 2] = temp;
        curr = (curr - 1) / 2;
    }
}

int ExtractMin() {
    if (zone == 0) {
        printf("Heap is empty.\n");
        return -1;
    }

    int min = Heap[0];
    Heap[0] = Heap[zone - 1];
    zone--;

    int curr = 0;
    while (curr < zone) {
        int left = 2 * curr + 1;
        int right = 2 * curr + 2;
        int smallest = curr;

        if (left < zone && Heap[left] < Heap[smallest]) {
            smallest = left;
        }
        if (right < zone && Heap[right] < Heap[smallest]) {
            smallest = right;
        }
        if (smallest != curr) {
            int temp = Heap[curr];
            Heap[curr] = Heap[smallest];
            Heap[smallest] = temp;
            curr = smallest;
        } else {
            break;
        }
    }

    return min;
}

void PrintHeap() {
    if (zone == 0) {
        printf("Heap is empty.\n");
        return;
    }

    printf("Min Heap: ");
    for (int i = 0; i < zone; i++) {
        printf("%d ", Heap[i]);
    }
    printf("\n");
}

int main () {
    return 0;
}