#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN 10
#define MAX 90

//Struktura binarnog stabla 
struct _tree;
typedef struct _tree* Position;
typedef struct _tree {
    int value;
    Position left;
    Position right;
} Tree;

//Prototipovi
Position insert(Position root, int value);
int inorderPrint(Position root);
int inorderToFile(Position root, FILE* fp);
int replaceWithSum(Position root);
int generateRandomTree(Position* root, int n);


int main()
{
    Position root = NULL;
    int array[] = { 2,5,7,8,11,1,4,2,3,7 };
    int n = 10;
    int choice = 0;
    FILE* fp = NULL;

    srand((unsigned)time(NULL));

    printf("1 - Predefinirani niz\n");
    printf("2 - Slucajni brojevi\n");
    scanf("%d", &choice);

    if (choice == 1) {
        for (int i = 0; i < n; i++)
            root = insert(root, array[i]);
    }
    else {
        printf("Koliko elemenata zelite? ");
        scanf("%d", &n);
        generateRandomTree(&root, n);
    }

    printf("\nINORDER nakon umetanja:\n");
    inorderPrint(root);

    fp = fopen("inorder.txt", "w");
    if (!fp) {
        printf("Greska pri otvaranju datoteke!\n");
        return -1;
    }

    fprintf(fp, "INORDER nakon umetanja:\n");
    inorderToFile(root, fp);

    replaceWithSum(root);

    printf("\n\nINORDER nakon replace:\n");
    inorderPrint(root);

    fprintf(fp, "\nINORDER nakon replace:\n");
    inorderToFile(root, fp);

    fclose(fp);

    return 0;
}



// Umetanje u BST 
Position insert(Position root, int value)
{
    if (root == NULL) {
        root = (Position)malloc(sizeof(Tree));
        root->value = value;
        root->left = NULL;
        root->right = NULL;
    }
    else if (value <= root->value) {
        root->left = insert(root->left, value);
    }
    else {
        root->right = insert(root->right, value);
    }

    return root;
}

// Inorder ispis 
int inorderPrint(Position root)
{
    if (root == NULL)
        return 0;

    inorderPrint(root->left);
    printf("%d ", root->value);
    inorderPrint(root->right);

    return 0;
}

// Inorder zapis u datoteku
int inorderToFile(Position root, FILE* fp)
{
    if (root == NULL)
        return 0;

    inorderToFile(root->left, fp);
    fprintf(fp, "%d ", root->value);
    inorderToFile(root->right, fp);

    return 0;
}

// Zamjena vrijednosti èvora sumom potomaka 
int replaceWithSum(Position root)
{
    int leftSum = 0, rightSum = 0;
    int oldValue = 0;

    if (root == NULL)
        return 0;

    leftSum = replaceWithSum(root->left);
    rightSum = replaceWithSum(root->right);

    oldValue = root->value;
    root->value = leftSum + rightSum;

    return root->value + oldValue;
}

// Generiranje stabla sa rand() 
int generateRandomTree(Position* root, int n)
{
    int value = 0;

    for (int i = 0; i < n; i++) {
        value = MIN + rand() % (MAX - MIN + 1);
        *root = insert(*root, value);
    }

    return 0;
}
