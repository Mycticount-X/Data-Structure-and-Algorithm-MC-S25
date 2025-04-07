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
			root->age = temp->age;
            root->MTX = temp->MTX;
            strcpy(root->name, temp->name);
            strcpy(root->alter, temp->alter);
            root->gender = temp->gender;
            root->height = temp->height;
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
            root->age = temp->age;
            root->MTX = temp->MTX;
            strcpy(root->name, temp->name);
            strcpy(root->alter, temp->alter);
            root->gender = temp->gender;
            root->height = temp->height;
            root->right = DeleteMyc(root->right, temp->name, temp->alter);
        }
    }
    
    return root;
}

void InitBalancedTrees() {
    // Sample corefog (BST berdasarkan MTX)
    const char* names_fog[] = {"Zephyr", "Luna", "Kai", "Nova", "Iris", "Orion", "Rhea"};
    int MTX_fog[] = {40, 20, 60, 10, 30, 50, 70};
    double height_fog[] = {150.5, 160.2, 155.8, 140.3, 165.4, 170.0, 158.1};
    bool gender_fog[] = {true, false, true, false, true, false, true};
    int age_fog[] = {25, 21, 29, 19, 23, 27, 31};

    for (int i = 0; i < 7; i++) {
        corefog = GenerateFog(corefog, (char*)names_fog[i], MTX_fog[i], height_fog[i], gender_fog[i], age_fog[i]);
    }

    // Sample coremtx (BST berdasarkan alter)
    const char* names_mtx[] = {"Amber", "Blake", "Cleo", "Dante", "Eira", "Felix", "Gwen"};
    const char* alter_mtx[] = {"amber", "blake", "cleo", "dante", "eira", "felix", "gwen"};
    int MTX_mtx[] = {41, 22, 63, 14, 35, 56, 72};
    double height_mtx[] = {151.1, 159.3, 154.6, 141.2, 162.0, 169.9, 157.7};
    bool gender_mtx[] = {false, true, false, true, false, true, false};
    int age_mtx[] = {24, 20, 28, 18, 22, 26, 30};

    for (int i = 0; i < 7; i++) {
        coremtx = GenerateMyc(coremtx, (char*)names_mtx[i], MTX_mtx[i], height_mtx[i], gender_mtx[i], age_mtx[i], (char*)alter_mtx[i]);
    }

    printf("Init Success!\n");
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
    printf("Height: %.2lf mm\n", root->height);
    printf("MTX: %d\n\n", root->MTX);
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
    printf("MTX: %d\n\n", root->MTX);
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
    printf("MTX: %d\n\n", root->MTX);
}

// Environtment Event
bool gacha(int MTX, double height) {
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
    root->MTX = (int)(root->MTX * (1.0 + (range / 10.0)));
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
void AddFog();
void AddMyx();
void ViewFog();
void ViewMyx();
void DestroyFog();
void DestroyMyx();
void ExportFogMenu();
void ExportMyxMenu();
void HelpMenu();
void ExitMenu();

// Main Function
int main () {
	InitBalancedTrees();
    Menu();
    return 0;
}

// Main Menu
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
                    MyxMenu();
                    break;
                case 2:
				    HelpMenu();
                    break;
                case 3:
					ExitMenu();
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

// Tree Menu
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
		printf("%s 5. Return to Main Menu %s\n", (position == 4) ? ">>" : "  ", (position == 4) ? "<<" : "  ");
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
                    AddFog();
                    break;
                case 1:
                    ViewFog();
                    break;
                case 2:
					DestroyFog();
                    break;
                case 3:
                    ExportFogMenu();
                    break;
                case 4:
					return;
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
                    AddMyx();
                    break;
                case 1:
                    ViewMyx();
                    break;
                case 2:
					DestroyMyx();
                    break;
                case 3:
                    ExportMyxMenu();
                    break;
                case 4:
					return;
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

// Add Menu
void AddFog () {
    char name[100];
    bool gender = false;
    char gender_input[100];
    double height;
    int MTX;
    int age;

    printf("Input Sample Name: ");
    scanf(" %[^\n]", name);

    while (strlen(name) < 2 && strlen(name) > 90) {
        printf("Name must be between 2 and 90 characters!\n");
        printf("Input Sample Name: ");
        scanf(" %[^\n]", name);
    }

    printf("Input Sample Gender [Male/Female]: ");
    scanf(" %[^\n]", gender_input);

    while (strcmpi(gender_input, "male") != 0 && strcmpi(gender_input, "female") != 0) {
        printf("Input Sample Gender [Male/Female]: ");
        scanf(" %[^\n]", gender_input);
    }

    if (strcmpi(gender_input, "male") == 0) {
        gender = true;
    }

    printf("Input Sample Height [mm]: ");
    scanf("%lf", &height);

    while (height <= 0) {
        printf("Sample must be positive!\n");
        printf("Input Sample Height [mm]: ");
        scanf("%lf", &height);
    }

    if (height > 500) {
        printf("Midgetizing Sample must be less than 500 mm!\n");
        printf("Sample rejected!\n");
        printf("Press enter to continue..."); getchar();
	    while (getchar() != '\n');
        return;
    }

    printf("Input Sample MTX: ");
    scanf("%d", &MTX);

    while (MTX <= 0) {
        printf("Sample must be positive!\n");
        printf("Input Sample MTX: ");
        scanf("%d", &MTX);
    }

    printf("Input Sample Age: ");
    scanf("%d", &age);

    while (age <= 0) {
        printf("Sample must be positive!\n");
        printf("Input Sample Age: ");
        scanf("%d", &age);
    }

    corefog = GenerateFog(corefog, name, MTX, height, gender, age);
    printf("Sample %s has been added to Alteration Fog Tree!\n", name);

    printf("Press enter to continue..."); getchar();
	while (getchar() != '\n');
}

void AddMyx () {
    char name[100];
    char alter[100];
    bool gender = false;
    char gender_input[100];
    double height;
    int MTX;
    int age;

    printf("Input Sample Name: ");
    scanf(" %[^\n]", name);

    while (strlen(name) < 2 && strlen(name) > 90) {
        printf("Name must be between 2 and 90 characters!\n");
        printf("Input Sample Name: ");
        scanf(" %[^\n]", name);
    }

    strcpy(alter, name);
    alterlower(alter);

    printf("Input Sample Gender [Male/Female]: ");
    scanf(" %[^\n]", gender_input);

    while (strcmpi(gender_input, "male") != 0 || strcmpi(gender_input, "female") != 0) {
        printf("Input Sample Gender [Male/Female]: ");
        scanf(" %[^\n]", gender_input);
    }

    if (strcmpi(gender_input, "male") == 0) {
        gender = true;
    }

    printf("Input Sample Height [mm]: ");
    scanf("%lf", &height);

    while (height <= 0) {
        printf("Sample must be positive!\n");
        printf("Input Sample Height [mm]: ");
        scanf("%lf", &height);
    }

    if (height > 500) {
        printf("Midgetizing Sample must be less than 500 mm!\n");
        printf("Sample rejected!\n");
        printf("Press enter to continue...");
	    while (getchar() != '\n'); getchar();
        return;
    }

    printf("Input Sample MTX: ");
    scanf("%d", &MTX);

    while (MTX <= 0) {
        printf("Sample must be positive!\n");
        printf("Input Sample MTX: ");
        scanf("%d", &MTX);
    }

    printf("Input Sample Age: ");
    scanf("%d", &age);

    while (age <= 0) {
        printf("Sample must be positive!\n");
        printf("Input Sample Age: ");
        scanf("%d", &age);
    }

    corefog = GenerateMyc(corefog, name, MTX, height, gender, age, alter);
    printf("Sample %s has been added to Myctix Heaven Tree!\n", name);

    printf("Press enter to continue..."); getchar();
	while (getchar() != '\n');
}

// View Menu
void ViewFog () {
    int position = 0;
	char input;
    bool menu = true;
	system("cls");
	while (menu) {
		printf("%s Choose Traversal Ordering%s\n", CYAN, RESET);
		printf("%s 1. Preorder %s\n", (position == 0) ? ">>" : "  ", (position == 0) ? "<<" : "  ");
		printf("%s 2. Inorder %s\n", (position == 1) ? ">>" : "  ", (position == 1) ? "<<" : "  ");
		printf("%s 3. Postorder %s\n", (position == 2) ? ">>" : "  ", (position == 2) ? "<<" : "  ");
		printf("%s 4. Cancel %s\n", (position == 3) ? ">>" : "  ", (position == 3) ? "<<" : "  ");
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
                	if (corefog == NULL) printf("The Alteration Fog Tree is Empty\n");
                    Preorder(corefog);
                    menu = false;
                    break;
                case 1:
                    if (corefog == NULL) printf("The Alteration Fog Tree is Empty\n");
					Inorder(corefog);
                    menu = false;
                    break;
                case 2:
                	if (corefog == NULL) printf("The Alteration Fog Tree is Empty\n");
					Postorder(corefog);
                    menu = false;
                    break;
                case 3:
					menu = false;
                    break;
				default:
					// Buat Penanda kalo ada Error
					printf("Out of Index!\n");
					break;
            }
        }
        
	}
    printf("Press enter to continue...");
    while (getchar() != '\n');
}

void ViewMyx () {
    int position = 0;
	char input;
    bool menu = true;
	system("cls");
	while (menu) {
		printf("%s Choose Traversal Ordering%s\n", CYAN, RESET);
		printf("%s 1. Preorder %s\n", (position == 0) ? ">>" : "  ", (position == 0) ? "<<" : "  ");
		printf("%s 2. Inorder %s\n", (position == 1) ? ">>" : "  ", (position == 1) ? "<<" : "  ");
		printf("%s 3. Postorder %s\n", (position == 2) ? ">>" : "  ", (position == 2) ? "<<" : "  ");
		printf("%s 4. Cancel %s\n", (position == 3) ? ">>" : "  ", (position == 3) ? "<<" : "  ");
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
                    if (coremtx == NULL) printf("The Myctix Heaven Tree is Empty\n");
                    Preorder(coremtx);
                    menu = false;
                    break;
                case 1:
                    if (coremtx == NULL) printf("The Myctix Heaven Tree is Empty\n");
                    Inorder(coremtx);
                    menu = false;
                    break;
                case 2:
					if (coremtx == NULL) printf("The Myctix Heaven Tree is Empty\n");
                    Postorder(coremtx);
                    menu = false;
                    break;
                case 3:
					menu = false;
                    break;
				default:
					// Buat Penanda kalo ada Error
					printf("Out of Index!\n");
					break;
            }
        }
        
	}

    printf("Press enter to continue...");
    while (getchar() != '\n');
}

// Destroy Menu
void DestroyFog () {
    int MTX;
    printf("Input Sample MTX: ");
    scanf("%d", &MTX);

    while (MTX <= 0) {
        printf("Sample must be positive!\n");
        printf("Input Sample MTX: ");
        scanf("%d", &MTX);
    }
    
	Sample* check = SearchFog(MTX);
    if (check == NULL) printf("Sample not found\n");
	else {
	    corefog = DeleteFog(corefog, MTX);
		printf("Sample with MTX %d has been destroyed!\n", MTX);
	}

    printf("Press enter to continue..."); getchar();
    while (getchar() != '\n');
}

void DestroyMyx () {
    char name[100];
    char alter[100];
    printf("Input Sample Name: ");
    scanf(" %[^\n]", name);

    while (strlen(name) < 2 && strlen(name) > 90) {
        printf("Name must be between 2 and 90 characters!\n");
        printf("Input Sample Name: ");
        scanf(" %[^\n]", name);
    }

    strcpy(alter, name);
    alterlower(alter);

    Sample* check = SearchMyc(alter);
    if (check == NULL) printf("Sample not found\n");
	else {
		coremtx = DeleteMyc(coremtx, name, alter);
		printf("Sample with name %s has been destroyed!\n", name);		
	}
    printf("Press enter to continue..."); getchar();
    while (getchar() != '\n');
}

// Export Menu
void ExportFogMenu () {
    ExportFog(corefog);
    corefog = NULL;
    printf("All Sample has been exported to Myctix Heaven Tree!\n");

    printf("Press enter to continue...");
    while (getchar() != '\n');
}

void ExportMyxMenu () {
    ExportMyx(coremtx);
    coremtx = NULL;
    printf("All Sample has been exported to Alteration Fog Tree!\n");

    printf("Press enter to continue...");
    while (getchar() != '\n');
}

// Help Menu
void HelpMenu () {
    FILE* file = fopen("help.txt", "r");
    if (file == NULL) {
        printf("Failed to open help.txt file!\n");
        printf("Press enter to continue...");
        while (getchar() != '\n');
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
    printf("\nPress enter to continue...");
    while (getchar() != '\n');
    
}

// Exit Menu
void ExitMenu () {
	int position = 0;
	char input;
	while (true) {
		printf(" %sAre you sure want to exit?%s\n", BLUE, RESET);
		printf("%s 1. Yes %s\n", (position == 0) ? ">>" : "  ", (position == 0) ? "<<" : "  ");
		printf("%s 2. No %s\n", (position == 1) ? ">>" : "  ", (position == 1) ? "<<" : "  ");
		input = _getch();
		system("cls");
		if (input == 'w' || input == 'W') {
			if (position > 0) {
				position--;
			}
		} else if (input == 's' || input == 'S') {
			if (position < 1) {
				position++;
			}
		} else if (input == '\r') {
			switch (position) {
				case 0:
					printf("Thank you for using Midgetification Vessel Management Server!\n");
					printf("Have a nice day :)\n\n");
					Sleep(1000);

					printf("%sCreator:%s\n", MAGENTA, RESET);
					printf("Name: Michael AS\n");
					printf("Github: Mycticount-X\n");
					printf("Youtube: Mycticount X\n");
					printf("HSR: 825019617\n");
					exit(0);
					break;
				case 1:
					return;
				default:
					// Buat Penanda kalo ada Error
					printf("Out of Index!\n");
					break;
			}
		}
	}

}
