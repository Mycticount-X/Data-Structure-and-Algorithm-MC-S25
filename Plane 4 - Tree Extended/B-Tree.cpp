#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ORDE 3

typedef struct Zone {
    int *keys;
    int t;     // Minimum degree (defines the range for number of keys)
    struct Zone **children;
    int n;     // Current number of keys
    bool leaf;
} Zone;

Zone* core = NULL;

Zone* Generate(int t, bool leaf) {
    Zone* newZone = (Zone*)malloc(sizeof(Zone));
    newZone->t = t;
    newZone->leaf = leaf;
    newZone->n = 0;
    newZone->keys = (int*)malloc((2 * t - 1) * sizeof(int));
    newZone->children = (Zone**)malloc(2 * t * sizeof(Zone*));
    
    // Initialize children to NULL
    for (int i = 0; i < 2 * t; i++) {
        newZone->children[i] = NULL;
    }
    
    return newZone;
}

void SplitChild(Zone* parent, int i, Zone* child) {
    Zone* newChild = Generate(child->t, child->leaf);
    newChild->n = child->t - 1;

    // Pindahkan keys terbesar dari child ke newChild
    for (int j = 0; j < child->t - 1; j++)
        newChild->keys[j] = child->keys[j + child->t];

    // Jika bukan leaf, pindahkan children juga
    if (!child->leaf) {
        for (int j = 0; j < child->t; j++)
            newChild->children[j] = child->children[j + child->t];
    }

    // Kurangi jumlah key di child
    child->n = child->t - 1;
    
    // Geser children parent untuk menyisipkan newChild
    for (int j = parent->n; j > i; j--)
        parent->children[j + 1] = parent->children[j];

    parent->children[i + 1] = newChild;

    // Geser keys parent dan sisipkan key tengah dari child
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

        i++;
        
        if (zone->children[i]->n == 2 * zone->t - 1) {
            SplitChild(zone, i, zone->children[i]);
            if (key > zone->keys[i])
                i++;
        }
        InsertNonFull(zone->children[i], key);
    }
}

Zone* Insert(Zone* root, int key) {
    if (root->n == 2 * root->t - 1) {
        Zone* newRoot = Generate(root->t, false);
        newRoot->children[0] = root;
        SplitChild(newRoot, 0, root);
        
        if (key < newRoot->keys[0])
            InsertNonFull(newRoot->children[0], key);
        else
            InsertNonFull(newRoot->children[1], key);
            
        return newRoot;
    } else {
        InsertNonFull(root, key);
        return root;
    }
}

void Traverse(Zone* zone) {
    if (!zone) return;
    
    int i;
    for (i = 0; i < zone->n; i++) {
        if (!zone->leaf)
            Traverse(zone->children[i]);
        printf("%d ", zone->keys[i]);
    }
    if (!zone->leaf)
        Traverse(zone->children[i]);
}

void FreeTree(Zone* zone) {
    if (!zone) return;
    
    if (!zone->leaf) {
        for (int i = 0; i <= zone->n; i++) {
            FreeTree(zone->children[i]);
        }
    }
    
    free(zone->keys);
    free(zone->children);
    free(zone);
}

int main() {
    int t = ORDE;
    core = Generate(t, true);

    int testData[] = {10, 20, 5, 6, 12, 30, 7, 17};
    int n = sizeof(testData) / sizeof(testData[0]);

    for (int i = 0; i < n; i++) {
        core = Insert(core, testData[i]);
    }

    printf("Traversal of constructed B-tree:\n");
    Traverse(core);
    printf("\n");
    
    FreeTree(core);
    return 0;
}