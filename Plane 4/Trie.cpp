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
    
    temp->isEoF = true;
}

int main () {
    return 0;
}