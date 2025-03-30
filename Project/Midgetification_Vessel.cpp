#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

// Atribut ANSI
#define RESET   "\033[0m"  // Buat reset akhiran
#define RED     "\033[31m"       
#define GREEN   "\033[32m"  
#define YELLOW  "\033[33m"   
#define BLUE    "\033[34m"   
#define MAGENTA "\033[35m"   
#define CYAN    "\033[36m"  
#define WHITE   "\033[37m" 

struct Sample {
	int MTX;
    int age;
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

Sample* Create (char name[], int MTX, double height, bool gender, int age) {
    Sample* sample = (Sample*)malloc(sizeof(Sample));
    sample->MTX = MTX;
    sample->height = height;
    sample->age = age;
    
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
Sample* GenerateFog (Sample* root, char name[], int MTX, double height, bool gender, int age) {
    if (root == NULL) {
        root = Create(name, MTX, height, gender, age);
        return root;
    }

    if (MTX < root->MTX) {
        root->left = GenerateFog(root->left, name, MTX, height, gender, age);
    } else if (MTX > root->MTX) {
        root->right = GenerateFog(root->right, name, MTX, height, gender, age);
    } else {
        // Duplicate = Extra Midgetize
        MTX = (MTX < 0) ? 0 : MTX - 1;
        root->left = GenerateFog(root->left, name, MTX, height, gender, age);
    }

    return root;
}

Sample* GenerateMyc (Sample* root, char name[], int MTX, double height, bool gender, int age, char alter[]) {
    if (root == NULL) {
        root = Create(name, MTX, height, gender, age);
        return root;
    }

    if (strcmp(alter, root->alter) < 0) {
        root->left = GenerateMyc(root->left, name, MTX, height, gender, age, alter);
    } else if (strcmp(alter, root->alter) > 0) {
        root->right = GenerateMyc(root->right, name, MTX, height, gender, age, alter);
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
    alterlower(alter);
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
				*root = *temp;
			}
			free(temp);
		} else {
			Sample* temp = minSample(root->right);
			*root = *temp;
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
                *root = *temp;
            }
            free(temp);
        } else {
            Sample* temp = minSample(root->right);
            *root = *temp;
            root->right = DeleteMyc(root->right, temp->name, temp->alter);
        }
    }
    
    return root;
}

// Tree Height Command
int Height (Sample* root) {
    if (root == NULL) {
        return 0;
    }

    int left = Height(root->left);
    int right = Height(root->right);
    return (left > right) ? left + 1 : right + 1;
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
bool gacha(int MTX, int height) {
    if (MTX <= 0 || height <= 0) {
        return true;
    }
    
    const double c = 1000.0;
    double probability = c / (MTX + height + c);
    
    return ((double)rand() / RAND_MAX) < probability;
}

void Fog (Sample* root) {
    if (root == NULL) {
        return;
    }

    Sleep(20);
    Fog(root->left);
    Fog(root->right);

    root->age++;
    if (gacha(root->MTX, root->height)) {
        root->gender = !root->gender;
        printf("Sample %s terkena efek Whispering Fog! Gender berubah menjadi %s.\n", 
               root->name, root->gender ? "[Male]" : "[Female]");
    }
}

void WhisperingFog () {
    if (corefog == NULL) {
        printf("Plane is Empty!\n");
        return;
    }

    printf("Whispering Fog is coming!\n");
    srand(time(NULL));
    Sleep(200);
    Fog (corefog);
}

void Myx (Sample* root) {
	if (root == NULL) {
		return;
	}
	
	Sleep(20);
    Myx(root->left);
    Myx(root->right);

    root->age++;
    int range = rand() % 18 + 8;
    root->MTX *= (1+range/10);
    printf("Sample %s terkena efek Myctix Expansion!\n", root->name);
    printf("MTX meingkat %d%%!\n", range*10);
    printf("MTX: %d\n", root->MTX);
}

void MyctixExpansion () {
    if (coremtx == NULL) {
        printf("Plane is Empty!\n");
        return;
    }

    printf("Myctix Expansion is coming!\n");
    srand(time(NULL));
    Sleep(200);
    Myx (coremtx);
}

// Export Function
void ExportFog (Sample* root) {
    if (root == NULL) {
        return;
    }

    coremtx = GenerateMyc(coremtx, root->name, root->MTX, root->height, root->gender, root->age, root->alter);
    ExportFog(root->left);
    ExportFog(root->right);
    free(root);
}

void ExportMyx (Sample* root) {
    if (root == NULL) {
        return;
    }

    corefog = GenerateFog(corefog, root->name, root->MTX, root->height, root->gender, root->age);
    ExportMyx(root->left);
    ExportMyx(root->right);
    free(root);
}

// Menu Function
void Menu();
void FogMenu();
void MyxMenu();

// Main Function
int main () {
    Menu();
    return 0;
}

void Menu () {
	int position = 0;
	char input;
	system("cls");
	while (true) {
		printf("%s Midgetification Vessel Management Server%s\n", CYAN, RESET);
		printf("%s 1. Alteration Fog Tree %s\n", (position == 0) ? ">>" : "  ", (position == 0) ? "<<" : "  ");
		printf("%s 2. Myctix Heaven Tree %s\n", (position == 1) ? ">>" : "  ", (position == 1) ? "<<" : "  ");
		printf("%s 3. Help %s\n", (position == 2) ? ">>" : "  ", (position == 2) ? "<<" : "  ");
		printf("%s 4. Exit %s\n", (position == 3) ? ">>" : "  ", (position == 3) ? "<<" : "  ");
        printf("\nGunakan [W] dan [S] untuk Navigasi");
		input = _getch();
		system("cls");
        if (input == 'w' || input == 'W') {
            if (position > 0) {
                position--;
            }
        } else if (input == 's' || input == 'S') {
            if (position < 4 - 1) {
                position++;
            }
        } else if (input == '\r') {
            switch (position) {
                case 0:
                    FogMenu();
                    break;
                case 1:
                    // ViewMenu();
                    break;
                case 2:
					// PopMenu();
                    break;
                case 3:
					// ExitMenu();
					break;
				default:
					// Buat Penanda kalo ada Error
					printf("Out of Index!\n");
					break;
            }
        }
        
        system("cls");
	}
}

void FogMenu () {
	int position = 0;
	char input;
	system("cls");
	while (true) {
		printf("%s Alteration Fog Tree%s\n", CYAN, RESET);
		printf("%s 1. Add Sample %s\n", (position == 0) ? ">>" : "  ", (position == 0) ? "<<" : "  ");
		printf("%s 2. View Sample %s\n", (position == 1) ? ">>" : "  ", (position == 1) ? "<<" : "  ");
		printf("%s 3. Destroy Sample %s\n", (position == 2) ? ">>" : "  ", (position == 2) ? "<<" : "  ");
		printf("%s 4. Export Sample to Myctix Heaven Tree %s\n", (position == 3) ? ">>" : "  ", (position == 3) ? "<<" : "  ");
		printf("%s 5. Exit %s\n", (position == 4) ? ">>" : "  ", (position == 4) ? "<<" : "  ");
        printf("\nGunakan [W] dan [S] untuk Navigasi");
		input = _getch();
		system("cls");
        if (input == 'w' || input == 'W') {
            if (position > 0) {
                position--;
            }
        } else if (input == 's' || input == 'S') {
            if (position < 5 - 1) {
                position++;
            }
        } else if (input == '\r') {
            switch (position) {
                case 0:
                    // InsertMenu();
                    break;
                case 1:
                    // ViewMenu();
                    break;
                case 2:
					// PopMenu();
                    break;
                case 3:
					// ExitMenu();
					break;
				default:
					// Buat Penanda kalo ada Error
					printf("Out of Index!\n");
					break;
            }
        }
        
        system("cls");
	}
}


void MyxMenu () {
	int position = 0;
	char input;
	system("cls");
	while (true) {
		printf("%s Myctix Heaven Tree%s\n", CYAN, RESET);
		printf("%s 1. Add Sample %s\n", (position == 0) ? ">>" : "  ", (position == 0) ? "<<" : "  ");
		printf("%s 2. View Sample %s\n", (position == 1) ? ">>" : "  ", (position == 1) ? "<<" : "  ");
		printf("%s 3. Destroy Sample %s\n", (position == 2) ? ">>" : "  ", (position == 2) ? "<<" : "  ");
		printf("%s 4. Export Sample to Alteration Fog Tree %s\n", (position == 3) ? ">>" : "  ", (position == 3) ? "<<" : "  ");
		printf("%s 5. Exit %s\n", (position == 4) ? ">>" : "  ", (position == 4) ? "<<" : "  ");
        printf("\nGunakan [W] dan [S] untuk Navigasi");
		input = _getch();
		system("cls");
        if (input == 'w' || input == 'W') {
            if (position > 0) {
                position--;
            }
        } else if (input == 's' || input == 'S') {
            if (position < 5 - 1) {
                position++;
            }
        } else if (input == '\r') {
            switch (position) {
                case 0:
                    // InsertMenu();
                    break;
                case 1:
                    // ViewMenu();
                    break;
                case 2:
					// PopMenu();
                    break;
                case 3:
					// ExitMenu();
					break;
				default:
					// Buat Penanda kalo ada Error
					printf("Out of Index!\n");
					break;
            }
        }
        
        system("cls");
	}
}
