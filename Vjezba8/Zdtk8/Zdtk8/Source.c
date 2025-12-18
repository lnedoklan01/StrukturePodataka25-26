#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define SUCCESS (0)
#define PROGRAM_EXIT (-1)
#define ALLOC_FAIL_POZ (NULL)

/* Definicija pokazivaèa na strukturu stabla */
typedef struct treeNode* Position;

/* Struktura èvora binarnog stabla pretraživanja */
struct treeNode {
    int value;          /* Vrijednost u èvoru */
    Position left;      /* Lijevo dijete */
    Position right;     /* Desno dijete */
};

typedef struct treeNode TreeNode;

/* Prototipi funkcija */
Position createNode();
Position insertNode(Position, Position);
Position searchNode(Position, int);
Position deleteNode(Position, int);
Position findMax(Position);
Position findMin(Position);

int treeDepth(Position);
int printLevel(Position, int);
int printLevelOrder(Position);

int inorderTraversal(Position);
int preorderTraversal(Position);
int postorderTraversal(Position);

int main() {
    Position root = NULL;
    Position q = NULL;
    int operation = 0;
    int element = 0;

    printf("Unesite root element: ");
    q = createNode();
    if (q == NULL)
        return PROGRAM_EXIT;

    scanf("%d", &q->value);
    root = insertNode(root, q);

    while (1) {
        printf("\n--------- MENI --------");
        printf("\n1) Unos novog elementa");
        printf("\n2) Level-order ispis");
        printf("\n3) Inorder / Preorder / Postorder ispis");
        printf("\n4) Pronalaženje elementa");
        printf("\n5) Brisanje elementa");
        printf("\n6) Izlaz");
        printf("\nOdaberite operaciju: ");

        scanf("%d", &operation);

        switch (operation) {

        case 1:
            q = createNode();
            if (q == NULL)
                return PROGRAM_EXIT;

            printf("Unesite element: ");
            scanf("%d", &q->value);
            root = insertNode(root, q);
            break;

        case 2:
            printLevelOrder(root);
            break;

        case 3:
            printf("\nInorder: ");
            inorderTraversal(root);
            printf("\nPreorder: ");
            preorderTraversal(root);
            printf("\nPostorder: ");
            postorderTraversal(root);
            printf("\n");
            break;

        case 4:
            printf("Koji element zelite pronaci: ");
            scanf("%d", &element);
            if (searchNode(root, element))
                printf("Element je pronaden!\n");
            else
                printf("Element ne postoji u stablu!\n");
            break;

        case 5:
            printf("Koji element zelite izbrisati: ");
            scanf("%d", &element);
            root = deleteNode(root, element);
            break;

        case 6:
            printf("Hvala na koristenju!\n");
            return SUCCESS;

        default:
            printf("Nepostojeca operacija!\n");
        }
    }
}

/* Alokacija i inicijalizacija novog èvora */
Position createNode() {
    Position p = (Position)malloc(sizeof(TreeNode));
    if (p == NULL) {
        printf("Greska pri alociranju memorije!\n");
        return ALLOC_FAIL_POZ;
    }

    p->left = NULL;
    p->right = NULL;
    return p;
}

/* Rekurzivni unos elementa u BST */
Position insertNode(Position root, Position newNode) {
    if (root == NULL)
        return newNode;

    if (newNode->value < root->value)
        root->left = insertNode(root->left, newNode);
    else if (newNode->value > root->value)
        root->right = insertNode(root->right, newNode);
    else {
        printf("Element vec postoji!\n");
        free(newNode);
    }

    return root;
}

/* Pretraživanje elementa u BST-u */
Position searchNode(Position root, int value) {
    if (root == NULL || root->value == value)
        return root;

    if (value < root->value)
        return searchNode(root->left, value);

    return searchNode(root->right, value);
}

/* Brisanje elementa iz BST-a */
Position deleteNode(Position root, int value) {
    if (root == NULL)
        return NULL;

    if (value < root->value)
        root->left = deleteNode(root->left, value);
    else if (value > root->value)
        root->right = deleteNode(root->right, value);
    else {
        if (root->left) {
            Position temp = findMax(root->left);
            root->value = temp->value;
            root->left = deleteNode(root->left, temp->value);
        }
        else if (root->right) {
            Position temp = findMin(root->right);
            root->value = temp->value;
            root->right = deleteNode(root->right, temp->value);
        }
        else {
            free(root);
            return NULL;
        }
    }
    return root;
}

/* Pronalazak maksimalnog elementa */
Position findMax(Position root) {
    while (root->right != NULL)
        root = root->right;
    return root;
}

/* Pronalazak minimalnog elementa */
Position findMin(Position root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

/* Izraèun dubine stabla */
int treeDepth(Position root) {
    if (root == NULL)
        return 0;

    int l = treeDepth(root->left);
    int r = treeDepth(root->right);

    return (l > r ? l : r) + 1;
}

/* Ispis elemenata na odreðenoj razini */
int printLevel(Position root, int level) {
    if (root == NULL)
        return SUCCESS;

    if (level == 0)
        printf("%d ", root->value);
    else {
        printLevel(root->left, level - 1);
        printLevel(root->right, level - 1);
    }

    return SUCCESS;
}

/* Level-order ispis */
int printLevelOrder(Position root) {
    int depth = treeDepth(root);

    for (int i = 0; i < depth; i++) {
        printf("Level %d: ", i + 1);
        printLevel(root, i);
        printf("\n");
    }
    return SUCCESS;
}

/* Inorder ispis */
int inorderTraversal(Position root) {
    if (root == NULL)
        return SUCCESS;

    inorderTraversal(root->left);
    printf("%d ", root->value);
    inorderTraversal(root->right);

    return SUCCESS;
}

/* Preorder ispis */
int preorderTraversal(Position root) {
    if (root == NULL)
        return SUCCESS;

    printf("%d ", root->value);
    preorderTraversal(root->left);
    preorderTraversal(root->right);

    return SUCCESS;
}

/* Postorder ispis */
int postorderTraversal(Position root) {
    if (root == NULL)
        return SUCCESS;

    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d ", root->value);

    return SUCCESS;
}
