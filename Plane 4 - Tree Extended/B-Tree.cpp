#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ORDE 3

// Zone Structure
struct Zone {
    int *keys;
    int t;     // Minimum degree (defines the range for number of keys)
    Zone **children;
    int n;     // Current number of keys
    bool leaf;
};

Zone* core = NULL;

Zone* Generate (int t, bool leaf) {
    Zone* newZone = (Zone*)malloc(sizeof(Zone));
    newZone->t = t;
    newZone->leaf = leaf;
    newZone->n = 0;
    newZone->keys = (int*)malloc((2 * t - 1) * sizeof(int));
    newZone->children = (Zone**)malloc(2 * t * sizeof(Zone*));
    return newZone;
}

// B-Tree Standard Command
void SplitChild(Zone* parent, int i, Zone* child) {
    Zone* newChild = Generate(child->t, child->leaf);
    newChild->n = child->t - 1;

    for (int j = 0; j < child->t - 1; j++)
        newChild->keys[j] = child->keys[j + child->t];

    if (!child->leaf) {
        for (int j = 0; j < child->t; j++)
            newChild->children[j] = child->children[j + child->t];
    }

    child->n = child->t - 1;
    for (int j = parent->n; j >= i + 1; j--)
        parent->children[j + 1] = parent->children[j];

    parent->children[i + 1] = newChild;

    for (int j = parent->n - 1; j >= i; j--)
        parent->keys[j + 1] = parent->keys[j];
    parent->keys[i] = child->keys[child->t - 1];
    parent->n++;
}

void InsertNonFull(Zone* zone, int key) {
    int i = zone->n - 1;

    if (zone->leaf) {
        while (i >= 0 && key < zone->keys[i]) {
            zone->keys[i + 1] = zone->keys[i];
            i--;
        }
        zone->keys[i + 1] = key;
        zone->n++;
    } else {
        while (i >= 0 && key < zone->keys[i])
            i--;

        if (zone->children[i + 1]->n == 2 * zone->t - 1) {
            SplitChild(zone, i + 1, zone->children[i + 1]);
            if (key > zone->keys[i + 1])
                i++;
        }
        InsertNonFull(zone->children[i + 1], key);
    }
}

void Insert(Zone* root, int key) {
    if (root->n == 2 * root->t - 1) {
        Zone* newRoot = Generate(root->t, false);
        newRoot->children[0] = root;
        SplitChild(newRoot, 0, root);
        InsertNonFull(newRoot, key);
    } else {
        InsertNonFull(root, key);
    }
}

// Traversal Command
void Traverse(Zone* zone) {
    int i;
    for (i = 0; i < zone->n; i++) {
        if (!zone->leaf)
            Traverse(zone->children[i]);
        printf("%d ", zone->keys[i]);
    }
    if (!zone->leaf)
        Traverse(zone->children[i]);
}


int main() {
    return 0;
}
