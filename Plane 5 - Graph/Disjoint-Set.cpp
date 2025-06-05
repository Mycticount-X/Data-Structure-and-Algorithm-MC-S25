#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Zone Structure
int parent[MAX];
int rank[MAX];

// Init Command
void makeSet(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

// Find Command
int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]); 
    }
    return parent[x];
}

// Union Command
void unionSets(int x, int y) {
    int xRoot = find(x);
    int yRoot = find(y);

    if (xRoot == yRoot) return; 

    if (rank[xRoot] < rank[yRoot]) {
        parent[xRoot] = yRoot;
    } else if (rank[xRoot] > rank[yRoot]) {
        parent[yRoot] = xRoot;
    } else {
        parent[yRoot] = xRoot;
        rank[xRoot]++;
    }
}

void ViewParents(int n) {
    printf("Element : Parent\n");
    for (int i = 0; i < n; i++) {
        printf("   %d    :   %d\n", i, parent[i]);
    }
}

void ViewRanks(int n) {
    printf("Element : Rank\n");
    for (int i = 0; i < n; i++) {
        printf("   %d    :   %d\n", i, rank[i]);
    }
}

void Solver () {
    int C, R;
    scanf("%d %d", &C, &R);

    makeSet(C);

    for (int i = 0; i < R; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        unionSets(a, b);
    }

    // Hitung root unik
    int count = 0;
    for (int i = 0; i < C; i++) {
        if (find(i) == i) {
            count++;
        }
    }

    printf("%d\n", count);
}

int main() {
    int n = 10;
    makeSet(n);

    unionSets(1, 2);
    unionSets(2, 3);
    unionSets(4, 5);
    unionSets(6, 7);
    unionSets(5, 6);
    unionSets(3, 7); 

    ViewParents(n);

    // Cek apakah 1 dan 7 berada di set yang sama
    if (find(1) == find(7)) {
        printf("1 dan 7 berada dalam satu set.\n");
    } else {
        printf("1 dan 7 berada dalam set yang berbeda.\n");
    }

    return 0;
}