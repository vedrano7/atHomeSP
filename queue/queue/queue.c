//red je vezana lista koja prati princip FIFO (first in, first out)

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#define FAILED_MEMORY_ALLOCATION (-1)
#define MAX (100)

typedef struct node* position;

typedef struct node {		//element reda
	int el;
	position next;
}Node;

int menu(position head);
int printQueue(position firstNode);
int enqueue(int newEl, position head);		//stavljat element na kraj reda
int dequeue(position head);					//skida element s pocetka reda
	
int main() {
	Node head = { 0,NULL };

	menu(&head);

	return EXIT_SUCCESS;
}

int menu(position head) {
	char pick = '\0';
	int newEl = 0;

	while (1) {

		printf("\nAko zelite dodati element u red upisite '1', ako zelite ispisati cijeli red upisite '2', ako zelite skinuti element iz reda upisite '3' i ako zelite izaci iz programa upisite '0'.\n");
		scanf(" %c", &pick);

		switch (pick) {
		case '1':
			printf("\nUpisite vrijednost novog elementa: ");
			scanf("%d", &newEl);

			enqueue(newEl, head);

			continue;

		case '2':
			printQueue(head->next);

			continue;

		case '3':
			dequeue(head);

			continue;

		case '0':
			printf("\nKraj programa!\n");

			break;

		default:
			printf("\nKrivi unos!\n");

			continue;
		}
		
		break;
	}

	return EXIT_SUCCESS;
}

int printQueue(position firstNode) {

	printf("\n------------\n");

	if (firstNode == NULL)
		printf("Red je prazan!\n");

	else {
		while (firstNode != NULL) {

			printf("%d\n", firstNode->el);
			firstNode = firstNode->next;
		}


	}

	printf("------------\n");

	return EXIT_SUCCESS;
}


int enqueue(int newEl, position head) {
	position newNode = NULL, current = head;

	newNode = malloc(sizeof(Node));

	if (!newNode) {
		printf("\nUnable to allocate memory for newnode\n");
		return FAILED_MEMORY_ALLOCATION;
	}

	newNode->el = newEl;

	while (current->next != NULL)
		current = current->next;

	newNode->next = current->next;
	current->next = newNode;

	printf("\nElement je dodan na kraj reda!\n");

	return EXIT_SUCCESS;
}


int dequeue(position head) {
	position temp = NULL;

	if (head->next == NULL) {
		printf("\nStog nema elemenata!\n");
	}

	else {

		temp = head->next;
		head->next = temp->next;

		free(temp);

		printf("\nElement s pocetka reda je skinut!\n");
	}

	return EXIT_SUCCESS;
}