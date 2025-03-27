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

Sample* minSample (Sample* root) {
	Sample* curr = root;
	while (curr->left) {
		curr = curr->left;
	}
	return curr;
}

// Generate Command
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
        MTX = (MTX < 0) ? 0 : MTX - 1;
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

// Search Command
Sample* SearchFog (int MTX) {
    Sample* curr = corefog;
    while (curr != NULL) {
        if (MTX == curr->MTX) {
            return curr;
        } else if (MTX < curr->MTX) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }

    return NULL;
}

Sample* SearchMyc (char alter[]) {
    Sample* curr = coremtx;
    while (curr != NULL) {
        if (strcmp(alter, curr->alter) == 0) {
            return curr;
        } else if (strcmp(alter, curr->alter) < 0) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }

    return NULL;
}

// Delete Command
Sample* DeleteFog (Sample* root, int MTX) {
	if (root == NULL) {
		printf("Sampel dengan nilai stats %d MTX tidak ditemukan!\n", MTX);
        return root;
	}

	if (MTX < root->MTX) {
		root->left = DeleteFog(root->left, MTX);
	} else if (MTX > root->MTX) {
		root->right = DeleteFog(root->right, MTX);
	} else {
		if ((root->left == NULL) || (root->right == NULL)) {
			Sample* temp = root->left ? root->left : root->right;
			if (temp == NULL) {
				temp = root;
				root = NULL;
			} else {
				root->MTX = temp->MTX;
                root->height = temp->height;
                strcpy(root->name, temp->name);
                strcpy(root->alter, temp->alter);
                root->gender = temp->gender;
			}
			free(temp);
		} else {
			Sample* temp = minSample(root->right);
			root->MTX = temp->MTX;
            root->height = temp->height;
            strcpy(root->name, temp->name);
            strcpy(root->alter, temp->alter);
            root->gender = temp->gender;
			root->right = DeleteFog(root->right, temp->MTX);
		}
	}
	
	return root;
}

Sample* DeleteMyc (Sample* root, char name[], char alter[]) {
    if (root == NULL) {
        printf("Sampel dengan nama %s tidak ditemukan!\n", name);
        return root;
    }

    if (strcmp(alter, root->alter) < 0) {
        root->left = DeleteMyc(root->left, name, alter);
    } else if (strcmp(alter, root->alter) > 0) {
        root->right = DeleteMyc(root->right, name, alter);
    } else {
        if ((root->left == NULL) || (root->right == NULL)) {
            Sample* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else {
                root->MTX = temp->MTX;
                root->height = temp->height;
                strcpy(root->name, temp->name);
                strcpy(root->alter, temp->alter);
                root->gender = temp->gender;
            }
            free(temp);
        } else {
            Sample* temp = minSample(root->right);
            root->MTX = temp->MTX;
            root->height = temp->height;
            strcpy(root->name, temp->name);
            strcpy(root->alter, temp->alter);
            root->gender = temp->gender;
            root->right = DeleteMyc(root->right, temp->name, temp->alter);
        }
    }
    
    return root;
}

// Traversal Command
void Preorder (Sample* root) {
    if (root == NULL) {
        return;
    }
    
    printf("%s (%s)\n", root->name, root->gender ? "Male" : "Female");
    printf("Height: %.2lf mm", root->height);
    printf("MTX: %d\n", root->MTX);
    Preorder(root->left);
    Preorder(root->right);
}

void Inorder(Sample* root) {
    if (root == NULL) {
        return;
    }

    Inorder(root->left);
    printf("%s (%s)\n", root->name, root->gender ? "Male" : "Female");
    printf("Height: %.2lf mm\n", root->height);
    printf("MTX: %d\n", root->MTX);
    Inorder(root->right);
}

void Postorder(Sample* root) {
    if (root == NULL) {
        return;
    }

    Postorder(root->left);
    Postorder(root->right);
    printf("%s (%s)\n", root->name, root->gender ? "Male" : "Female");
    printf("Height: %.2lf mm\n", root->height);
    printf("MTX: %d\n", root->MTX);
}

// Environtment Event
void WhisperingFog () {
    
}

// Main Function
int main () {
	corefog = GenerateFog(corefog, "Alpha", 50, 170.5, true);
    corefog = GenerateFog(corefog, "Beta", 30, 160.0, false);
    corefog = GenerateFog(corefog, "Gamma", 70, 180.2, true);
    corefog = GenerateFog(corefog, "Delta", 60, 165.8, false);
    corefog = GenerateFog(corefog, "Epsilon", 90, 175.3, true);

    printf("=== Inorder Traversal ===\n");
    Inorder(corefog);

    printf("\n=== Searching Sample ===\n");
    Sample* found = SearchFog(60);
    if (found) {
        printf("Found: %s with MTX: %d\n", found->name, found->MTX);
    } else {
        printf("Sample not found!\n");
    }

    printf("\n=== Deleting MTX 60 ===\n");
    corefog = DeleteFog(corefog, 60);
    Inorder(corefog);

    printf("\n=== Deleting Non-existent MTX 100 ===\n");
    corefog = DeleteFog(corefog, 100);
    Inorder(corefog);
	return 0;
}
