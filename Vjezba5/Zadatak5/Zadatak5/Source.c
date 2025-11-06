#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct cvor* Pozicija;
typedef struct cvor {
    double broj;
    Pozicija next;
} Cvor;

int push(Pozicija, double);
double pop(Pozicija);
int izracunajPostfixIzDatoteke(char*);
int operacija(double, double, char);

int main() {
    char* datoteka = "polinomi.txt";

    printf("Racunanje postfix izraza iz datoteke '%s':\n", datoteka);
    izracunajPostfixIzDatoteke(datoteka);

    return 0;
}

// Dodaje broj na vrh stoga
int push(Pozicija p, double broj) {
    Pozicija q = (Pozicija)malloc(sizeof(Cvor));
    if (!q) {
        printf("Greska pri alokaciji memorije!\n");
        return -1;
    }
    q->broj = broj;
    q->next = p->next;
    p->next = q;
    return 0;
}

// Skida broj s vrha stoga
double pop(Pozicija p) {
    Pozicija temp = p->next;
    if (!temp) {
        printf("Stog je prazan!\n");
        return 0;
    }

    double broj = temp->broj;
    p->next = temp->next;
    free(temp);
    return broj;
}

// Funkcija koja èita i raèuna postfix izraz iz datoteke
int izracunajPostfixIzDatoteke(char* imeDatoteke) {
    FILE* fp = fopen(imeDatoteke, "r");
    if (!fp) {
        printf("Greska pri otvaranju datoteke!\n");
        return -1;
    }

    Cvor head = { .broj = 0, .next = NULL };
    char buffer[1024];
    char* token = NULL;

    fgets(buffer, 1024, fp);
    fclose(fp);

    token = strtok(buffer, " ");
    while (token != NULL) {
        if (isdigit(token[0])) {
            double broj = atof(token);
            push(&head, broj);
        }
        else {
            double b = pop(&head);
            double a = pop(&head);
            double rezultat = operacija(a, b, token[0]);
            push(&head, rezultat);
        }
        token = strtok(NULL, " ");
    }

    double konacniRezultat = pop(&head);
    printf("Rezultat izraza: %.2lf\n", konacniRezultat);
    return 0;
}

// Obavlja osnovne operacije +, -, *, /
int operacija(double a, double b, char op) {
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/':
        if (b == 0) {
            printf("Greska: dijeljenje s nulom!\n");
            return 0;
        }
        return a / b;
    default:
        printf("Nepoznata operacija '%c'!\n", op);
        return 0;
    }
}
