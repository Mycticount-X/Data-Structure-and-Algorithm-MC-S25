#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct Sample {
	int MTX;
	double height;
	char name[100];
	char alter[100];
	bool gender;
    Sample* left;
    Sample* right;
};

Sample* corefog = NULL;
Sample* coremtx = NULL;

// Sample Function
void alterlower (char name[]) {
    for (int i = 0; name[i]!='\0'; i++) {
        if (name[i] >= 'A' && name[i] <= 'Z') {
            name[i] += 32;
        }
    }
}

Sample* Create (char name[], int MTX, double height, bool gender) {
    Sample* sample = (Sample*)malloc(sizeof(Sample));
    sample->MTX = MTX;
    sample->height = height;
    
    strcpy(sample->name, name);
    strcpy(sample->alter, name);
    alterlower(sample->alter);
    
    sample->gender = gender;
    sample->left = NULL;
    sample->right = NULL;
    return sample;
}

// Generate Function
Sample* GenerateFog (Sample* root, char name[], int MTX, double height, bool gender) {
    if (root == NULL) {
        root = Create(name, MTX, height, gender);
        return root;
    }

    if (MTX < root->MTX) {
        root->left = GenerateFog(root->left, name, MTX, height, gender);
    } else if (MTX > root->MTX) {
        root->right = GenerateFog(root->right, name, MTX, height, gender);
    } else {
        // Duplicate = Extra Midgetize
        MTX--;
        root->left = GenerateFog(root->left, name, MTX, height, gender);
    }

    return root;
}

Sample* GenerateMyc (Sample* root, char name[], int MTX, double height, bool gender, char alter[]) {
    if (root == NULL) {
        root = Create(name, MTX, height, gender);
        return root;
    }

    if (strcmp(alter, root->alter) < 0) {
        root->left = GenerateMyc(root->left, name, MTX, height, gender, alter);
    } else if (strcmp(alter, root->alter) > 0) {
        root->right = GenerateMyc(root->right, name, MTX, height, gender, alter);
    } else {
        printf("Duplicate Detected!\n");
    }

    return root;
}

// Search Function
Sample* SearchFog (int MTX) {
    while (corefog != NULL) {
        if (MTX == corefog->MTX) {
            return corefog;
        } else if (MTX < corefog->MTX) {
            corefog = corefog->left;
        } else {
            corefog = corefog->right;
        }
    }
}

Sample* SearchMyc (char alter[]) {
    while (coremtx != NULL) {
        if (strcmp(alter, coremtx->alter) == 0) {
            return coremtx;
        } else if (strcmp(alter, coremtx->alter) < 0) {
            coremtx = coremtx->left;
        } else {
            coremtx = coremtx->right;
        }
    }
}

int main () {
	return 0;
}
