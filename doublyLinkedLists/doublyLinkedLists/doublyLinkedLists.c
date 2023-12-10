#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#define FAILED_MEMORY_ALLOCATION (-1)


typedef struct node* position;

typedef struct node {
	int el;
	position next;
	position prev;
}Node;


int menu(position head);
int insertToBeggining(position head);
int printList(position firsel);
int insertToEnd(position head);
position findElInList(position firstEl);
int delElFromList(position firstEl);
int insertAfterEl(position firstEl);
int insertBeforeEl(position firstEl);
int delAll(position head);
int sortedInput(position head);




int main() {
	Node head = { 0,NULL,NULL };

	menu(&head);

	return EXIT_SUCCESS;
}

int menu(position head) {
	char pick = '\0';
	position result;

	while (1) {
		printf("\nZa dodati novi element na pocetak liste upisite 1, za ispisati listu upisite 2, za dodati novi element na kraj liste upisite 3, za pronaci odredeni element u listi upisite 4, za izbrisati odredeni element iz liste upisite 5, za umetnuti element iza odredenog elementa upisite 6, za umetnuti element ispred odredenog elementa upisite 7, za izbrisati cijelu listu 8, za sortirani unos u listu upisite '9' te upisite 0 za izaci iz programa\n");
		scanf("\n%c", &pick);

		switch (pick) {

			case '1':

				insertToBeggining(head);

				continue;

			case '2':

				printList(head->next);

				continue;

			case '3':
				insertToEnd(head);

				continue;

			case '4':
				result=findElInList(head->next);

				if (result == NULL)
					printf("\nElement nije naden u listi!\n");

				else
					printf("\nElement %d je naden u listi na adresi %p!\n", result->el, result);

				continue;

			case '5':
				delElFromList(head->next);

				continue;

			case '6':
				insertAfterEl(head->next);

				continue;

			case '7':
				insertBeforeEl(head->next);

				continue;

			case '8':
				delAll(head);

				continue;

			case '9':
				sortedInput(head);

				continue;

			case '0':

				printf("\nKraj programa!\n");

				break;

			default:
				printf("\nKrivi unos!!\n");

				continue;
		}

		break;

	};



	return EXIT_SUCCESS;
}

int insertToBeggining(position head) {
	position newNode = NULL;

	newNode = malloc(sizeof(Node));

	if (!newNode) {
		printf("\nUnable to allocate memory for newNode\n");
		return FAILED_MEMORY_ALLOCATION;
	}

	printf("\nUnesite vrijednost novog elementa: ");
	scanf("%d", &newNode->el);


	newNode->next = head->next;
	head->next = newNode;

	newNode->prev = head;	

	if (newNode->next != NULL)			
		newNode->next->prev = newNode;		


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

	newNode = malloc(sizeof(Node));

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

position findElInList(position firstEl) {
	int wantedEl = 0;
	position current = firstEl;

	printf("\nUpisite element kojeg zelite naci u list: ");
	scanf("%d", &wantedEl);

	while (current != NULL && current->el != wantedEl)
		current = current->next;

	return current;
}

int delElFromList(position firstEl) {
	int elToDel = 0;
	position current = firstEl,temp=NULL;

	printf("\nUnesite element koji zelite izbrisati: ");
	scanf("%d", &elToDel);

	while (current!= NULL && current->el != elToDel)
		current = current->next;

	if(current==NULL)
		printf("\nTog clana nema u listi\n");

	else {

		temp = current;

		if (current->next != NULL)
			current->next->prev = temp->prev;

		current->prev->next = temp->next;

		free(temp);

		printf("\nUspjesno izbrisan element %d!\n", elToDel);
	}

	return EXIT_SUCCESS;
}

int insertAfterEl(position firstEl) {
	position newNode = NULL, current = firstEl;
	int newElToIns = 0, inFrontOfWhichElToIns = 0;

	printf("\nIza kojeg elementa zelite umetnuti element i koji to?\n");
	scanf("%d %d", &inFrontOfWhichElToIns, &newElToIns);

	while (current != NULL && current->el != inFrontOfWhichElToIns)
		current = current->next;

	if (current == NULL)
		printf("\nElement iza kojeg zelite umetnuti element nije pronaden u listi\n");

	else {
		newNode = malloc(sizeof(Node));

		if (!newNode) {
			printf("\nUnable to allocate memory for newNode\n");
			return FAILED_MEMORY_ALLOCATION;
		}

		newNode->el = newElToIns;

		newNode->next = current->next;
		newNode->prev = current;

		if (current->next != NULL)
			current->next->prev = newNode;

		current->next = newNode;

	}

	return EXIT_SUCCESS;
}

int insertBeforeEl(position firstEl) {
	position newNode = NULL, current = firstEl;
	int newElToIns = 0, behindWhichElToIns = 0;

	printf("\nIspred kojeg elementa zelite umetnuti element i koji to?\n");
	scanf("%d %d", &behindWhichElToIns, &newElToIns);

	while (current != NULL && current->el != behindWhichElToIns)
		current = current->next;

	if (current == NULL)
		printf("\nElement ispred kojeg zelite umetnuti element nije pronaden u listi\n");

	else {
		newNode = malloc(sizeof(Node));

		if (!newNode) {
			printf("\nUnable to allocate memory for newNode\n");
			return FAILED_MEMORY_ALLOCATION;
		}

		newNode->el = newElToIns;


		newNode->next = current;
		newNode->prev = current->prev;

		current->prev->next = newNode;
		current->prev = newNode;

	}

	return EXIT_SUCCESS;
}

int delAll(position head) {
	char pick = '\0';
	position current = head, temp = NULL;

	printf("\nZa izbrisati cijelu listu od pocetka upisite 'p',a za izbrisati cijelu listu od kraja upisite 'k': ");
	scanf(" %c", &pick);

	if (pick == 'p') {
	
		while (head->next != NULL) {
			
			temp = head->next;
			head->next = temp->next;
			
			if(temp->next!=NULL)
				temp->next->prev = head;
		
			free(temp);

		}
	
	}

	else {
	
		while (head->next != NULL) {

			current = head;

			while (current->next != NULL)
				current = current->next;

			temp = current;
			temp->prev->next = temp->next;

			if(temp->next!=NULL)
				temp->next->prev = temp->prev;

			free(temp);


		}
	}
}

int sortedInput(position head) {
	position newNode=NULL,current = head;

	newNode = malloc(sizeof(Node));

	if (!newNode) {
		printf("\nNeuspjela alokacija memorije za newNode\n");
		exit(-1);
	}

	printf("\nUpisite novi element: \n");
	scanf("%d", &(newNode->el));

	

	while (current->next != NULL && newNode->el > current->next->el)
		current = current->next;

	newNode->next = current->next;
	newNode->prev = current;

	if (current->next != NULL)
		current->next->prev = newNode;

	current->next = newNode;

	return EXIT_SUCCESS;
}
