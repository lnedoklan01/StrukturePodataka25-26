//Prethodnom zadatku dodati funkcije :
//A.dinamièki dodaje novi element iza odreðenog elementa,
//B.dinamièki dodaje novi element ispred odreðenog elementa,
//C.sortira listu po prezimenima osoba,
//D.upisuje listu u datoteku,
//E.èita listu iz datoteke.




#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE (50)
#define CAN_NOT_ALLOCATE_MEMMORY (-1)

typedef struct person* Position;
typedef struct person {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birth_year;
	Position next;
}Person;

int menu(Position);
int addAtBeggining(Position);
int printList(Position);
int addAtEnd(Position);
Position findBySurname(Position, char*);
int deleteBySurname(Position, char*);
int addAfter(Position head);
int addBefore(Position head);
int sortList(Position head);
int readFromFile(Position head,char* filename);
int writeToFile(Position first,char* filename);


int main() {
	Person head = {
	.name = "",
	.surname = "",
	.birth_year = 0,
	.next = NULL
	};
	menu(&head);
	return 0;
}

//Funkcija za menu koji daje korisnik mogucnost unosa!
int menu(Position head) {
	int choice = 0;
	char surname[MAX_SIZE];
	Position found = NULL;
	while (1) {
		printf("Choose an option:\n");
		printf("1-Add at beggining\n");
		printf("2-Print list\n");
		printf("3-Add at the end\n");
		printf("4-Find by surname\n");
		printf("5-Delete by surname\n");
		printf("6-Exit the program!\n");
		printf("7-Add after person\n");
		printf("8-Add before person\n");
		printf("9-Sort list by surname\n");
		printf("10-Save list to file\n");
		printf("11-Read list from file\n");

		printf("Your choice is: ");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			addAtBeggining(head);
			break;
		case 2:
			printList(head->next);
			break;
		case 3:
			addAtEnd(head);
			break;
		case 4:
			if (head->next == NULL) {
				printf("Lista je prazna!\n");
				break;
			}
			printf("Unesite trazeno prezime:\n");
			scanf("%s", surname);
			found = findBySurname(head->next, surname);
			if (found) {
				printf("Pronaden: %s %s (%d)\n", found->name, found->surname, found->birth_year);
			}
			else {
				printf("Osoba s prezimenom %s nije pronadena!\n", surname);
			}
			break;
		case 5:
			if (head->next == NULL) {
				printf("Lista je prazna!\n");
				break;
			}
			printf("Unesite prezime osobe koje zelite izbrisati:");
			scanf("%s", surname);
			if (deleteBySurname(head, surname)) {
				printf("Osoba s prezimenom %s je uspjesno izbrisana!\n", surname);
				printf("Azurirana lista:\n");
				printList(head->next);
			}
			else
				printf("Osoba s prezimenom %s nije pronadena!\n", surname);
			break;
		case 6:
			printf("Izlaz iz programa!");
			return 0;
		case 7:
			addAfter(head);
			break;
		case 8:
			addBefore(head);
			break;
		case 9:
			sortList(head);
			printList(head->next);
			break;
		case 10:
			writeToFile(head->next, "osobe.txt");
			break;
		case 11:
			readFromFile(head, "osobe.txt");
			break;
		default:
			printf("Krivi unos, pokusajte ponovno!\n");
		}
	}
}

//Funkcija koja dodaje osobu na pocetak liste
int addAtBeggining(Position head) {
	Position newPerson;
	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson) {
		printf("Neuspjela alokacije memorije!\n");
		return CAN_NOT_ALLOCATE_MEMMORY;
	}
	printf("Unesite ime osobe:");
	scanf("%s", newPerson->name);
	printf("Unesite prezime:");
	scanf("%s", newPerson->surname);
	printf("Unesite godinu rodenja:");
	scanf("%d", &newPerson->birth_year);
	newPerson->next = head->next;
	head->next = newPerson;
	return 0;
}

//Funckija za ispis liste
int printList(Position first) {
	if (first == NULL) {
		printf("Lista je prazna!\n");
		return;
	}
	printf("Lista ljudi:\n");
	Position temp = first;
	while (temp != NULL) {
		printf("%s %s %d\n", temp->name, temp->surname, temp->birth_year);
		temp = temp->next;
	}
	return 0;
}

//Funkcija koja dodaje osobu na kraj liste!
int addAtEnd(Position head) {
	Position newPerson;
	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson) {
		printf("Greska pri alokaciji memorije!\n");
		return CAN_NOT_ALLOCATE_MEMMORY;
	}
	printf("Unesite ime osobe:");
	scanf("%s", newPerson->name);
	printf("Unesite prezime:");
	scanf("%s", newPerson->surname);
	printf("Unesite godinu rodenja:");
	scanf("%d", &newPerson->birth_year);
	newPerson->next = NULL;
	Position temp = head;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = newPerson;
	return 0;
}
//funkcija za pronalazenje osobe po prezimenu!
Position findBySurname(Position first, char* surname) {
	while (first != NULL) {
		if (strcmp(first->surname, surname) == 0) {
			return first;
		}
		first = first->next;
	}
	return NULL;
}
//funkcija koja brise osobe po prezimenu!
int deleteBySurname(Position head, char* surname) {
	Position prev = head; //prethodni clan   
	Position curr = head->next; //trenutni clan
	while (curr != NULL && strcmp(curr->surname, surname) != 0) {
		prev = curr;
		curr = curr->next; //pomicemo prethodni i trenutni clan zajedno do kraja liste ili dok ne pronademo trazeno prezime
	}
	if (curr == NULL) {
		return 0;
	}
	prev->next = curr->next;
	curr->next = NULL;
	free(curr);
	return 1;
}
//dodaje osobu nakon trazene osobe
int addAfter(Position head) {
	char surname[MAX_SIZE];
	printf("Unesite prezime osobe iza koje zelite dodati novu osobu: ");
	scanf("%s", surname);

	Position found = findBySurname(head->next, surname);
	if (!found) {
		printf("Osoba s prezimenom %s nije pronadena!\n", surname);
		return 0;
	}

	Position newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson) {
		printf("Greska pri alokaciji memorije!\n");
		return CAN_NOT_ALLOCATE_MEMMORY;
	}

	printf("Unesite ime nove osobe: ");
	scanf("%s", newPerson->name);
	printf("Unesite prezime nove osobe: ");
	scanf("%s", newPerson->surname);
	printf("Unesite godinu rodenja: ");
	scanf("%d", &newPerson->birth_year);

	newPerson->next = found->next;
	found->next = newPerson;

	return 0;
}

//dodaje osobu prije trazene osobe
int addBefore(Position head) {
	char surname[MAX_SIZE];
	printf("Unesite prezime osobe ispred koje zelite dodati novu osobu: ");
	scanf("%s", surname);

	Position prev = head;
	while (prev->next != NULL && strcmp(prev->next->surname, surname) != 0) {
		prev = prev->next;
	}

	if (prev->next == NULL) {
		printf("Osoba s prezimenom %s nije pronadena!\n", surname);
		return 0;
	}

	Position newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson) {
		printf("Greska pri alokaciji memorije!\n");
		return CAN_NOT_ALLOCATE_MEMMORY;
	}

	printf("Unesite ime nove osobe: ");
	scanf("%s", newPerson->name);
	printf("Unesite prezime nove osobe: ");
	scanf("%s", newPerson->surname);
	printf("Unesite godinu rodenja: ");
	scanf("%d", &newPerson->birth_year);

	newPerson->next = prev->next;
	prev->next = newPerson;

	return 0;
}
//sortira listu po prezimenima
int sortList(Position head) {
	if (head->next == NULL || head->next->next == NULL) {
		printf("Lista ima manje od 2 elementa, nije potrebno sortiranje!\n");
		return 0;
	}

	Position end = NULL;
	Position j = NULL;
	Position prev = NULL;
	Position temp = NULL;

	while (head->next != end) {
		prev = head;
		j = head->next;
		while (j->next != end) {
			if (strcmp(j->surname, j->next->surname) > 0) {
				// zamjena èvorova
				temp = j->next;
				j->next = temp->next;
				temp->next = j;
				prev->next = temp;
				j = temp;
			}
			prev = j;
			j = j->next;
		}
		end = j;
	}
	printf("Lista je sortirana po prezimenima!\n");
	return 0;
}
//citanje iz filea
int readFromFile(Position head,char* filename) {
	FILE* fp = fopen(filename, "r");
	if (!fp) {
		printf("Greska pri otvaranju datoteke!\n");
		return -1;
	}

	while (!feof(fp)) {
		Position newPerson = (Position)malloc(sizeof(Person));
		if (!newPerson) {
			printf("Greska pri alokaciji memorije!\n");
			fclose(fp);
			return CAN_NOT_ALLOCATE_MEMMORY;
		}
		if (fscanf(fp, "%s %s %d", newPerson->name, newPerson->surname, &newPerson->birth_year) == 3) {
			newPerson->next = NULL;

			Position temp = head;
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = newPerson;
		}
		else {
			free(newPerson);
			break;
		}
	}

	fclose(fp);
	printf("Lista je uspjesno ucitana iz datoteke '%s'.\n", filename);
	return 0;
}
//pisanje u file
int writeToFile(Position first,char* filename) {
	FILE* fp = fopen(filename, "w");
	if (!fp) {
		printf("Greska pri otvaranju datoteke!\n");
		return -1;
	}

	while (first != NULL) {
		fprintf(fp, "%s %s %d\n", first->name, first->surname, first->birth_year);
		first = first->next;
	}

	fclose(fp);
	printf("Lista je uspjesno upisana u datoteku '%s'.\n", filename);
	return 0;
}
