//Napisati program koji prvo proèita koliko redaka ima datoteka, tj.koliko ima studenata
//zapisanih u datoteci.Nakon toga potrebno je dinamièki alocirati prostor za niz struktura
//studenata(ime, prezime, bodovi) i uèitati iz datoteke sve zapise.Na ekran ispisati ime,
//prezime, apsolutni i relativni broj bodova.
//Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
//relatvan_br_bodova = br_bodova / max_br_bodova * 100


#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define FILE_NOT_OPENED (-1)
#define EXIT_PROGRAM (-1)
#define MAX_LINE (1024)
#define MAX_SIZE (50)
#define MAX_POINTS (50)

typedef struct students {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	double points;
}Students;

int rowCounter(char*);
Students* readStudents(int, char*);
int printStudents(Students*, int);

int main() {
	Students* stud = NULL;
	char* filePointer = "students.txt"; //stvaramo pointer kojem saljemo datoteku students.txt
	int noStudents = rowCounter(filePointer);
	if (noStudents <= 0) {
		printf("File is empty!\n");
		return EXIT_PROGRAM;
	}
	if (noStudents > 0) {
		stud = readStudents(noStudents, filePointer);
		int printed = printStudents(stud, noStudents);
		free(stud);
	}
	return 0;
}
//Funkcija za brojanje redova,tj. broja studenata u datoteci
int rowCounter(char* fileName) {
	int noRows = 0;
	char buffer[MAX_LINE] = { 0 };
	FILE* fp = NULL;
	fp = fopen(fileName, "r");
	if (!fp) {
		printf("Error with opening the file!\n");
		return FILE_NOT_OPENED;
	}
	while (fgets(buffer, MAX_LINE, fp)) {
		noRows++;
	}
	fclose(fp);
	return noRows;
}
//Funkcija koja ucitava studente iz datoteke i vraca pokazivac na prvi element niza Student
Students* readStudents(int noStud, char* fileName) {
	FILE* fp = NULL;
	fp = fopen(fileName, "r");
	if (!fp) {
		printf("Greska pri otvaranju datoteke!\n");
		return NULL;
	}
	Students* stud = (Students*)malloc(noStud*sizeof(Students)); //alokacije memorije i njena provjera
	if (!stud) {
		printf("Error with allocating the memory!\n");
		return NULL;
	}
	for (int i = 0; i < noStud; i++) {
		fscanf(fp, "%s %s %lf", (stud + i)->name, (stud+i)->surname, &(stud + i)->points);
	}
	fclose(fp);
	return stud;
}
//funkcija za ispis studenata i njihovih podataka te postignutih bodova
int printStudents(Students* stud, int noStud) {
	for (int i = 0; i < noStud; i++) {
		double average = ((stud + i)->points / MAX_POINTS) * 100;
		printf("Student %s %s scored %.2lf points, which is equal to %.2lf percentage.\n", (stud+i)->name, (stud + i)->surname, (stud + i)->points, average);
	}
	return 1;
}