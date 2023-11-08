#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#define FAILED_MEMORY_ALLOCATION (-1)


typedef struct node* position;

typedef struct node {
	int el;
	position next;
	position prev;
}node;


int menu(position head);
int insertToBeggining(position head);
int printList(position firsel);
int insertToEnd(position head);



int main() {
	node head = { 0,NULL,NULL };

	menu(&head);

	return EXIT_SUCCESS;
}

int menu(position head) {
	char pick = '\0';
	position resultant;

	while (1) {
		printf("\nZa dodati novi element na pocetak liste upisite 1, za ispisati listu upisite 2, za dodati novi element na kraj liste upisite 3, za pronaci odredeni element u listi upisite 4, za izbrisati odredeni element iz liste upisite 5,za naci prethodnika nekog elementa upisite 6, za umetnuti element iza odredenog elementa upisite 7, za umetnuti element ispred odredenog elementa upisite 8, za izbrisati cijelu listu s pocetka upisite 9, za izbrisati cijelu listu s kraja upisite 'a', za sortiranje liste upisite 'b', za sortirani unos u listu upisite 'c' te upisite 0 za izaci iz programa\n");
		scanf("\n%c", &pick);
		switch (pick) {

		case '1':

			insertToBeggining(head);

			break;
		case '2':

			printList(head->next);

			break;

		case '3':
			insertToEnd(head);

			break;

		case '0':

			printf("\nKraj programa!\n");

			break;

		default:
			printf("\nKrivi unos!!\n");

			break;

		}

		getchar();   //doda san ovaj getchar jer kad je  bia krivi unos uvik bi osta jedan '\n' koji bi zblesia kod (mora bi dva puta upisat 0 da se program zatvori)

		if (pick == '0')
			break;

	};



	return EXIT_SUCCESS;
}

int insertToBeggining(position head) {
	position newNode = NULL;

	newNode = malloc(sizeof(node));

	if (!newNode) {
		printf("\nUnable to allocate memory for newNode\n");
		return FAILED_MEMORY_ALLOCATION;
	}

	printf("\nUnesite vrijednost novog elementa: ");
	scanf("%d", &newNode->el);


	newNode->next = head->next;
	head->next = newNode;

	newNode->prev = head;		//doublylinked-dodatak

	if (newNode->next != NULL)				//doublylinked-dodatak
		newNode->next->prev = newNode;		//doublylinked-dodatak


	return EXIT_SUCCESS;
}

int printList(position firstel) {
	position current = firstel;

	printf("\n------------\n");

	if (firstel == NULL)
		printf("Lista je prazna!\n");

	else {

		while (current != NULL) {
			printf("%d\n", current->el);
			current = current->next;
		}
	}

	printf("------------\n");

	return EXIT_SUCCESS;
}

int insertToEnd(position head) {
	position newNode = NULL;
	position current = head;

	newNode = malloc(sizeof(node));

	if (!newNode) {
		printf("\nUnable to allocate memory for newNode\n");
		return FAILED_MEMORY_ALLOCATION;
	}

	printf("\nUnesite vrijednost novog elementa: ");
	scanf("%d", &newNode->el);

	while (current->next != NULL)
		current = current->next;

	newNode->next = current->next;
	newNode->prev = current;		//doublylinked-dodatak
	current->next = newNode;

	return EXIT_SUCCESS;
}

