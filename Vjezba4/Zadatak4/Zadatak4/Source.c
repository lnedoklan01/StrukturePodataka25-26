#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Postfix* Position;
typedef struct postfix {
	double number;
	Position next;
}Postfix;

int main() {
	Postfix head = {
	.number = 0,
	.next = NULL
	};
	FILE* fp = fopen("polinom.txt", "r");
	if (fp == NULL) {
		printf("Greska pri otvaranju datoteke!\n");
		return;
	}

}