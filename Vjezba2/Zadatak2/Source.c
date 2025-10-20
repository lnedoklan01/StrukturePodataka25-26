//Definirati strukturu osoba(ime, prezime, godina roðenja) i napisati program koji :
//A.dinamièki dodaje novi element na poèetak liste,
//B.ispisuje listu,
//C.dinamièki dodaje novi element na kraj liste,
//D.pronalazi element u listi(po prezimenu),
//E.briše odreðeni element iz liste,
//U zadatku se ne smiju koristiti globalne varijable.



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
	while (1){
		printf("Choose an option:\n");
		printf("1-Add at beggining\n");
		printf("2-Print list\n");
		printf("3-Add at the end\n");
		printf("4-Find by surname\n");
		printf("5-Delete by surname\n");
		printf("6-Exit the program!\n");

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
		default:
			printf("Krivi unos, pokusajte ponovno!\n");
		}
	}
}

//Funkcija koja dodaje osobu na pocetak liste
int addAtBeggining(Position head){
	Position newPerson;
	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson) {
		printf("Neuspjela alokacije memorije!\n");
		return CAN_NOT_ALLOCATE_MEMMORY;
	}
	printf("Unesite ime osobe:");
	scanf("%s",newPerson->name);
	printf("Unesite prezime:");
	scanf("%s",newPerson->surname);
	printf("Unesite godinu rodenja:");
	scanf("%d",&newPerson->birth_year);
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
	scanf("%s",newPerson->surname);
	printf("Unesite godinu rodenja:");
	scanf("%d",&newPerson->birth_year);
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
		if (strcmp(first->surname, surname)==0) {
			return first;
		}
		first = first->next;
	}
	return NULL;
}
//funkcija koja brise osobe po prezimenu!
int deleteBySurname(Position head, char* surname) {
	Position prev = head; //trenutni clan      
	Position curr = head->next; //sljedeci clan
	while (curr != NULL && strcmp(curr->surname, surname) != 0) {
		prev = curr;
		curr = curr->next; //pomicemo trenutni i sljedeci clan zajedno do kraja liste ili dok ne pronademo trazeno prezime
	}
	if (curr == NULL) {
		return 0;
	}
	prev->next = curr->next;
	free(curr);
	return 1;
}