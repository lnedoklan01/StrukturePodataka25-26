#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Item {
    char name[50];
    double quantity;
    double price;
    struct Item* next;
} Item;

typedef struct Receipt {
    char date[11]; // YYYY-MM-DD
    Item* items;
    struct Receipt* next;
} Receipt;

/* ----------------------------------------------------------
   Ubacivanje artikla sortirano po nazivu
---------------------------------------------------------- */
void insert_item_sorted(Item** head, const char* name, double quantity, double price) {
    Item* newItem = (Item*)malloc(sizeof(Item));
    strcpy(newItem->name, name);
    newItem->quantity = quantity;
    newItem->price = price;
    newItem->next = NULL;

    if (*head == NULL || strcmp(name, (*head)->name) < 0) {
        newItem->next = *head;
        *head = newItem;
        return;
    }

    Item* curr = *head;
    while (curr->next && strcmp(name, curr->next->name) > 0)
        curr = curr->next;

    newItem->next = curr->next;
    curr->next = newItem;
}

/* ----------------------------------------------------------
   Ubacivanje raèuna sortirano po datumu
---------------------------------------------------------- */
void insert_receipt_sorted(Receipt** head, Receipt* newReceipt) {
    if (*head == NULL || strcmp(newReceipt->date, (*head)->date) < 0) {
        newReceipt->next = *head;
        *head = newReceipt;
        return;
    }

    Receipt* curr = *head;
    while (curr->next && strcmp(newReceipt->date, curr->next->date) > 0)
        curr = curr->next;

    newReceipt->next = curr->next;
    curr->next = newReceipt;
}

/* ----------------------------------------------------------
   Uèitavanje pojedine datoteke raèuna
---------------------------------------------------------- */
Receipt* load_receipt(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        printf("Ne mogu otvoriti %s\n", filename);
        return NULL;
    }

    Receipt* receipt = (Receipt*)malloc(sizeof(Receipt));
    receipt->items = NULL;
    receipt->next = NULL;

    fgets(receipt->date, 11, f);
    receipt->date[10] = '\0';

    char line[200];
    while (fgets(line, sizeof(line), f)) {
        char name[50];
        double qty, price;

        if (sscanf(line, " %[^,], %lf, %lf", name, &qty, &price) == 3) {
            insert_item_sorted(&receipt->items, name, qty, price);
        }
    }

    fclose(f);
    return receipt;
}

/* ----------------------------------------------------------
   Uèitavanje svih raèuna iz racuni.txt
---------------------------------------------------------- */
Receipt* load_all_receipts(const char* listFile) {
    FILE* f = fopen(listFile, "r");
    if (!f) {
        printf("Ne mogu otvoriti %s\n", listFile);
        return NULL;
    }

    Receipt* list = NULL;
    char filename[100];

    while (fgets(filename, sizeof(filename), f)) {
        filename[strcspn(filename, "\n")] = '\0';
        Receipt* r = load_receipt(filename);

        if (r)
            insert_receipt_sorted(&list, r);
    }

    fclose(f);
    return list;
}

/* ----------------------------------------------------------
   Upit korisnika za ukupnu potrošnju na artikl u periodu
---------------------------------------------------------- */
void query(Receipt* list) {
    char itemName[50];
    char dateFrom[11], dateTo[11];

    printf("Unesi naziv artikla: ");
    scanf(" %[^\n]", itemName);

    printf("Unesi poèetni datum (YYYY-MM-DD): ");
    scanf("%s", dateFrom);

    printf("Unesi završni datum (YYYY-MM-DD): ");
    scanf("%s", dateTo);

    double totalQty = 0, totalSpent = 0;

    for (Receipt* r = list; r; r = r->next) {
        if (strcmp(r->date, dateFrom) >= 0 && strcmp(r->date, dateTo) <= 0) {
            for (Item* it = r->items; it; it = it->next) {
                if (strcmp(it->name, itemName) == 0) {
                    totalQty += it->quantity;
                    totalSpent += it->quantity * it->price;
                }
            }
        }
    }

    printf("\n-------------------------------------\n");
    printf("Artikl: %s\n", itemName);
    printf("Ukupna kolièina: %.2f\n", totalQty);
    printf("Ukupna potrošnja: %.2f EUR\n", totalSpent);
    printf("-------------------------------------\n");
}

/* ----------------------------------------------------------
   Glavni program
---------------------------------------------------------- */
int main() {
    Receipt* receipts = load_all_receipts("racuni.txt");

    if (!receipts) {
        printf("Nema uèitanih raèuna.\n");
        return 0;
    }

    query(receipts);

    return 0;
}
