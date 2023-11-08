#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#define FAILED_MEMORY_ALLOCATION (-1)
#define MAX (100)

//implementacija stoga pomocu nizova (tu je velicina niza predefinirana) -> u ovoj verziji se vrh stoga (top) gleda kao pozicija povise zadnjeg elementa (kad je stog pun top=MAX), a mogli smo risavat i da gledamo da ga gledamo kao poziciju zadnjeg elementa (kad je stog pun top=MAX-1)

//typedef struct stackData{
//	int maxNoEl;
//	int top;
//	int *elArray;
//}stack;
//
//typedef struct stackData* stackP;
//
//int menu(stackP s);
//int printStack(stackP s);
//int push(int newEl, stackP s);
//int pop(stackP s);
//
//int main() {
//	stack s = { 0,0,NULL };
//
//	printf("\nUnesite koliko clanova moze maksimalno stat u stog :");
//	scanf("%d", &s.maxNoEl);
//
//	s.elArray = malloc(s.maxNoEl * sizeof(int));
//
//	if (!s.elArray) {
//		printf("\nUnable to allocate memory for elArray in struct s\n");
//		return FAILED_MEMORY_ALLOCATION;
//	}
//	
//	menu(&s);
//
//	return EXIT_SUCCESS;
//}
//
//int menu(stackP s) {
//	char pick = '\0';
//	int newEl = 0;
//
//	while (1) {
//
//		printf("\nAko zelite dodati element na vrh stoga upisite '1', ako zelite ispisati cijeli stog upisite '2', ako zelite skinuti element s vrha stoga  upisite '3' i ako zelite izaci iz programa upisite '0'.\n");
//		scanf(" %c", &pick);
//
//		switch (pick) {
//		case '1':
//			printf("\nUpisite vrijednost novog elementa: ");
//			scanf("%d", &newEl);
//
//			push(newEl, s);
//
//			break;
//
//		case '2':
//			printStack(s);
//
//			break;
//
//		case '3':
//			pop(s);
//
//			break;
//
//		case '0':
//			printf("\nKraj programa!\n");
//
//			break;
//
//		default:
//			printf("\nKrivi unos!\n");
//
//			break;
//		}
//
//		if (pick == '0')
//			break;
//	}
//
//	return EXIT_SUCCESS;
//}
//
//int printStack(stackP s) {
//	int i = 0;
//
//	printf("\n------------\n");
//
//	if (s->top == 0)
//		printf("Stog je prazan!\n");
//
//	else {
//		for(i=0; i<(s->top); i++)
//			printf("%d\n", s->elArray[i]);
//	}
//
//
//	printf("------------\n");
//
//	return EXIT_SUCCESS;
//}
//
//
//int push(int newEl, stackP s) {
//	
//	if (s->top == s->maxNoEl) {
//		printf("\nStog je vec pun!\n");
//		
//	}
//
//	else if (s->top == 0) {
//		s->elArray[0] = newEl;
//		(s->top)++;
//	}
//
//	else {
//		s->elArray[s->top] = newEl;
//		(s->top)++;
//	
//	}
//
//	return EXIT_SUCCESS;
//}
//
//
//int pop(stackP s) {
//	
//	if (s->top == 0) {
//		printf("\nStog je prazan!\n");
//
//	}
//
//
//	else {
//		s->elArray[(s->top)-1] = 0;
//		(s->top)--;
//
//		printf("\nSkinut je element sa stoga!\n");
//	}
//
//	return EXIT_SUCCESS;
//}


//implementacija stoga pomocu listi

typedef struct node* position;

typedef struct node{		//element stoga
	int el;
	position next;
}Node;

int menu(position head);
int printStack(position firstNode);
int push(int newEl, position head);
int pop(position head);

int main() {
	Node head = { 0,NULL };

	menu(&head);

	return EXIT_SUCCESS;
}

int menu(position head) {
	char pick = '\0';
	int newEl = 0;

	while (1) {

		printf("\nAko zelite dodati element na vrh stoga upisite '1', ako zelite ispisati cijeli stog upisite '2', ako zelite skinuti element s vrha stoga  upisite '3' i ako zelite izaci iz programa upisite '0'.\n");
		scanf(" %c", &pick);

		switch (pick) {
		case '1':
			printf("\nUpisite vrijednost novog elementa: ");
			scanf("%d", &newEl);

			push(newEl, head);

			break;

		case '2':
			printStack(head->next);

			break;

		case '3':
			pop(head);

			break;

		case '0':
			printf("\nKraj programa!\n");

			break;

		default:
			printf("\nKrivi unos!\n");

			break;
		}

		if (pick == '0')
			break;
	}

	return EXIT_SUCCESS;
}

int printStack(position firstNode) {

	printf("\n------------\n");

	if (firstNode == NULL)
		printf("Stog je prazan!\n");

	else {
		while (firstNode != NULL) {

			printf("%d\n", firstNode->el);
			firstNode = firstNode->next;
		}


	}

	printf("------------\n");

	return EXIT_SUCCESS;
}


int push(int newEl, position head) {
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


	return EXIT_SUCCESS;
}


int pop(position head) {
	position current = head, temp = NULL;

	if (head->next == NULL) {
		printf("\nStog nema elemenata!\n");
	}

	else {

		while (current->next->next != NULL)
			current = current->next;

		temp = current->next;
		current->next = temp->next;
		free(temp);

		printf("\nElement s vrha je skinut!\n");
	}

	return EXIT_SUCCESS;
}