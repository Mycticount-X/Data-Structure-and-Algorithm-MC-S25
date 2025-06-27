/*
 * Implementasi Max Heap dan Min Heap di C
 * Dilengkapi fungsi insert, extract, heapify, dan contoh penggunaan
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

/* Utility: tukar dua elemen */
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* =====================
 *       MAX HEAP
 * =====================
 */

/* Memperbaiki heap ke bawah (heapify) pada index i untuk Max Heap */
void maxHeapify(int heap[], int size, int i) {
    int largest = i;
    int left  = 2 * i + 1;
    int right = 2 * i + 2;

    // Cari anak terbesar
    if (left < size && heap[left] > heap[largest])
        largest = left;
    if (right < size && heap[right] > heap[largest])
        largest = right;

    // Jika bukan root, tukar dan heapify rekursif
    if (largest != i) {
        swap(&heap[i], &heap[largest]);
        maxHeapify(heap, size, largest);
    }
}

/* Sisipkan kunci baru ke Max Heap */
void insertMaxHeap(int heap[], int *size, int key) {
    if (*size >= MAX_SIZE) {
        printf("Heap penuh, tidak dapat menambahkan %d\n", key);
        return;
    }
    // Tambah di akhir
    int i = (*size)++;
    heap[i] = key;

    // Naikkan elemen hingga properti heap terpenuhi
    while (i != 0 && heap[(i - 1) / 2] < heap[i]) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

/* Extract maksimum (root) dari Max Heap */
int extractMax(int heap[], int *size) {
    if (*size <= 0) return -1;  // Heap kosong
    if (*size == 1) {
        (*size)--;
        return heap[0];
    }

    int root = heap[0];
    heap[0] = heap[--(*size)];
    maxHeapify(heap, *size, 0);

    return root;
}

/* =====================
 *       MIN HEAP
 * =====================
 */

/* Memperbaiki heap ke bawah (heapify) pada index i untuk Min Heap */
void minHeapify(int heap[], int size, int i) {
    int smallest = i;
    int left  = 2 * i + 1;
    int right = 2 * i + 2;

    // Cari anak terkecil
    if (left < size && heap[left] < heap[smallest])
        smallest = left;
    if (right < size && heap[right] < heap[smallest])
        smallest = right;

    // Jika bukan root, tukar dan heapify rekursif
    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        minHeapify(heap, size, smallest);
    }
}

/* Sisipkan kunci baru ke Min Heap */
void insertMinHeap(int heap[], int *size, int key) {
    if (*size >= MAX_SIZE) {
        printf("Heap penuh, tidak dapat menambahkan %d\n", key);
        return;
    }
    // Tambah di akhir
    int i = (*size)++;
    heap[i] = key;

    // Naikkan elemen hingga properti heap terpenuhi
    while (i != 0 && heap[(i - 1) / 2] > heap[i]) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

/* Extract minimum (root) dari Min Heap */
int extractMin(int heap[], int *size) {
    if (*size <= 0) return -1;  // Heap kosong
    if (*size == 1) {
        (*size)--;
        return heap[0];
    }

    int root = heap[0];
    heap[0] = heap[--(*size)];
    minHeapify(heap, *size, 0);

    return root;
}

/* Cetak isi heap */
void printHeap(int heap[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", heap[i]);
    printf("\n");
}

int main() {
    int maxHeap[MAX_SIZE], maxSize = 0;
    int minHeap[MAX_SIZE], minSize = 0;

    // Contoh Max Heap
    printf("== Max Heap ==\n");
    int data1[] = { 3, 1, 5, 2, 4 };
    for (int i = 0; i < 5; i++) insertMaxHeap(maxHeap, &maxSize, data1[i]);
    printf("Heap setelah insert: "); printHeap(maxHeap, maxSize);
    printf("Extract max: %d\n", extractMax(maxHeap, &maxSize));
    printf("Heap setelah extract: "); printHeap(maxHeap, maxSize);

    // Contoh Min Heap
    printf("\n== Min Heap ==\n");
    int data2[] = { 3, 1, 5, 2, 4 };
    for (int i = 0; i < 5; i++) insertMinHeap(minHeap, &minSize, data2[i]);
    printf("Heap setelah insert: "); printHeap(minHeap, minSize);
    printf("Extract min: %d\n", extractMin(minHeap, &minSize));
    printf("Heap setelah extract: "); printHeap(minHeap, minSize);

    return 0;
}
