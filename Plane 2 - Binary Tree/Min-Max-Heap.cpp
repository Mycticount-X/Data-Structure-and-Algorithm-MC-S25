#include <stdio.h>
#include <stdio.h>
#include <math.h>

#define MAX_SIZE 100

int tree[MAX_SIZE];
int size = 0;

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

int main () {
    return 0;
}