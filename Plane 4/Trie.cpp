#include <stdio.h>
#include <stdlib.h>

// Global Define
#define ALPHA_SIZE 26

// Kepada anak-anak yg membaca ini untuk AoL:
// Kalian Kopas Kena Nyontek Tanggung Sendiri
// Kode AoL saya beda dengan ini
struct Zone {
    Zone* children[ALPHA_SIZE];
    int MTX;
    bool isEoF;
};

Zone* core = NULL;

Zone* CreateZone () {
    Zone* newZone = (Zone*) malloc (sizeof(Zone));
    newZone->isEoF = false;
    for (int i = 0; i < ALPHA_SIZE; i++) {
        newZone->children[i] = NULL;
    }

    return newZone;
}

// Fruit Command
void FruitZone (Zone* root, const char* name, int MTX) {
    Zone* temp = root;
    
    while (*name) {
        int index = *name - 'a';
        
        if (!temp->children[index]) {
            temp->children[index] = CreateZone();
        }
        temp = temp->children[index];
        name++;
    }
    
    if (temp->isEoF) {
        if (temp->MTX < MTX) {
            temp->MTX = MTX;
            printf("Konsetrasi Myctix pada Zona %s meningkat menjadi %d!\n", name, MTX);
        } else if (temp->MTX > MTX) {
            temp->MTX = MTX;
            printf("Konsetrasi Myctix pada Zona %s menurun menjadi %d!\n", name, MTX);
        } else {
            printf("Zona %s staknan!\n", name);
        }
    } else {
        temp->isEoF = true;
        temp->MTX = MTX;
    }
}

// Search Command
void SearchZone (Zone* root, const char* name) {
    Zone* temp = root;
    
    while (*name) {
        int index = *name - 'a';
        
        if (!temp->children[index]) {
            printf("Zona %s tidak ditemukan!\n", name);
            return;
        }
        temp = temp->children[index];
        name++;
    }
    
    if (temp->isEoF) {
        printf("Zona %s ditemukan dengan konsetrasi Myctix %d!\n", name, temp->MTX);
    } else {
        printf("Zona %s tidak ditemukan!\n", name);
    }
}

// Alter Command
void ClearPlane (Zone* root) {
    if (root == NULL) {
        printf("Permukaan saat ini kosong!\n");
        return;
    }

    for (int i = 0; i < ALPHA_SIZE; i++) {
        ClearPlane(root->children[i]);
    }
    free(root);
}

int main () {
    return 0;
}