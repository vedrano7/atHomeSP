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

int menu(position top);
int printStack(position top);		//rekurzivno ispisuje s vrha prema pocetku
int push(int newEl, position top);
int pop(position top);

int main() {
	Node head = { 0,NULL };		//u stogu necemo imat odvojeni head element nego ce on zapravo bit top (tj vrh stoga) i pri svakom dodavanju novog elementa cemo ga micat na novi element na vrhu

	menu(&head);

	return EXIT_SUCCESS;
}

int menu(position top) {
	char pick = '\0';
	int newEl = 0;

	while (1) {

		printf("\nAko zelite dodati element na vrh stoga upisite '1', ako zelite ispisati cijeli stog upisite '2', ako zelite skinuti element s vrha stoga  upisite '3' i ako zelite izaci iz programa upisite '0'.\n");
		scanf(" %c", &pick);

		switch (pick) {
		case '1':
			printf("\nUpisite vrijednost novog elementa: ");
			scanf("%d", &newEl);

			push(newEl, top);

			break;

		case '2':
			printStack(top);

			break;

		case '3':
			printf("\n%d",pop(top));

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

int printStack(position top) {	
	int currentStackEl = 0;


	if (top->next == NULL)
		return EXIT_SUCCESS;

	else {

		currentStackEl = top->next->el;

		printf("%d ", currentStackEl);


		pop(top);

		printStack(top);

		push(currentStackEl,top);
		
	}

	return EXIT_SUCCESS;
}


int push(int newEl, position top) {
	position newNode = NULL;

	newNode = malloc(sizeof(Node));

	if (!newNode) {
		printf("\nUnable to allocate memory for newnode\n");
		return FAILED_MEMORY_ALLOCATION;
	}

	newNode->el = newEl;

	newNode->next = top->next;
	top->next = newNode;


	return EXIT_SUCCESS;
}


int pop(position top) {
	position toDel = NULL;
	int poppedEl=0;

	if (top->next == NULL) {
		printf("\nStog nema elemenata za izbacit!\n");
	}

	else {

		toDel = top->next;
		top->next = toDel->next;

		poppedEl = toDel->el;

		free(toDel);
	}

	return poppedEl;
}