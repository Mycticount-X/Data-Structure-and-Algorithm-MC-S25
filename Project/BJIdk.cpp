#include <stdio.h>
#include <stdlib.h>

struct Zone {
    int MTX;
    Zone* left;
    Zone* right;
};

Zone* core = NULL;

Zone* CreateZone(int MTX) {
    Zone* newZone = (Zone*) malloc(sizeof(Zone));
    newZone->MTX = MTX;
    newZone->left = NULL;
    newZone->right = NULL;
    return newZone;
}

// Helper Function
Zone *minZone(Zone *root) {
    Zone *current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

// Tree Function
Zone* Generate (int MTX) {
    if (core == NULL) {
        core = CreateZone(MTX);
        return core;
    }

    Zone* curr = core;
    if (MTX < curr->MTX) {
        curr->left = Generate(MTX);
    } else if (MTX > curr->MTX) {
        curr->right = Generate(MTX);
    } else {
        printf("Duplicate Zone detected!\n");
        return NULL;
    }
}

Zone* Delete (Zone* curr, int MTX) {
    if (curr == NULL) {
        printf("Zone not found!\n");
        return NULL;
    }

    if (MTX < curr->MTX) {
        curr->left = Delete(curr->left, MTX);
    } else if (MTX > curr->MTX) {
        curr->right = Delete(curr->right, MTX);
    } else {
        // Tanpa Anak
        if (curr->left == NULL && curr->right == NULL) {
            free(curr);
            curr = NULL;
        }
        
        // Anak Satu
        else if (curr->left == NULL) {
            Zone* temp = curr;
            curr = curr->right;
            free(temp);
        } else if (curr->right == NULL) {
            Zone* temp = curr;
            curr = curr->left;
            free(temp);
        }

        // Anak Dua
        else {
            Zone* temp = minZone(curr->right);
            curr->MTX = temp->MTX;
            curr->right = Delete(curr->right, temp->MTX);
        }
    }
}


int main () {
    core = Generate(8000);

    return 0;
}