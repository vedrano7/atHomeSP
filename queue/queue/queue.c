//red (queue) je lista koja prati princip FIFO (first in, first out -> upisivanje se radi na kraj liste, a skidanje se radi s početka liste)

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#define FAILED_MEMORY_ALLOCATION (-1)
#define MAX (100)

//red realiziran pomocu niza

typedef struct Queue {
	int capacity;		//max broj el koji moze bit u nizu
	int size;			//trenutni br elemenata u nizu
	int front;
	int rear;
	int* elArray;
}queue;


int main() {
	queue q = { 0,0,0,0,NULL };
	int capacity = 0, newEl = 0, i = 0, counter = 0;
	char pick = '\0';

	printf("\nUnesite maksimalni br elemenata koji moze biti u nizu: ");
	scanf("%d", &capacity);

	q.capacity = capacity;
	q.elArray = malloc(capacity * sizeof(int));

	if (!q.elArray) {
		printf("\nUnable to alocate memory for elArray in struct q!\n");
		return EXIT_FAILURE;
	}

	for (i = 0; i < q.capacity; i++)
		q.elArray[i] = 0;

	while (1) {
		printf("\nAko zelite dodati element u red upisite '1', ako zelite ispisati cijeli red upisite '2', ako zelite skinuti element iz reda upisite '3' i ako zelite izaci iz programa upisite '0'.\n");
		scanf(" %c", &pick);

		switch (pick) {

			case '1':
				printf("\nUpisite vrijednost novog elementa: ");
				scanf("%d", &newEl);

				if(q.front==q.rear && q.elArray[q.front]==0)
					q.elArray[q.rear] = newEl;

				else
					q.elArray[++q.rear] = newEl;

				printf("\nElement je dodan na kraj reda!\n");

				q.size++;

				continue;

			case '2':

				if (q.front == q.rear && q.elArray[q.front]==0) {
					printf("\nRed je prazan!\n");
				}

				else {

					printf("\n------------\n");

					for (i = q.front; i <= q.rear; i++) {

						printf("%d\n", q.elArray[i]);
					}

					printf("------------\n");
				}

				continue;

			case '3':

				if (q.front == q.rear && q.elArray[q.front] == 0) {
					printf("\nRed je prazan!\n");
					continue;
				}
				

				if (q.front == q.rear) {
					q.front++;
					q.rear++;
					q.size--;
					printf("\nElement je skinut s pocetka reda!\n");
				}

				else {
					q.front++;
					q.size--;
					printf("\nElement je skinut s pocetka reda!\n");
				}

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


//red realiziran pomocu vezane liste

/*typedef struct node* position;

typedef struct node {		//element reda
	int el;
	position next;
}Node;

position front = NULL, rear = NULL;		//umjesto globalnih varijabli mogli smo koristit i duple pokazivace i onda njih slat u funkcije

int printQueue();
int enqueue(int newEl);		//stavlja element na kraj reda
int dequeue();				//skida element s pocetka reda
	
int main() {

	char pick = '\0';
	int newEl = 0;

	while (1) {

		printf("\nAko zelite dodati element u red upisite '1', ako zelite ispisati cijeli red upisite '2', ako zelite skinuti element iz reda upisite '3' i ako zelite izaci iz programa upisite '0'.\n");
		scanf(" %c", &pick);

		switch (pick) {
		case '1':
			printf("\nUpisite vrijednost novog elementa: ");
			scanf("%d", &newEl);

			enqueue(newEl);

			continue;

		case '2':
			printQueue(front);

			continue;

		case '3':
			dequeue();

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


int printQueue() {
	position current = front;

	printf("\n------------\n");

	if (front == NULL)
		printf("Red je prazan!\n");

	else {
		while (current != NULL) {

			printf("%d\n", current->el);
			current = current->next;
		}


	}

	printf("------------\n");

	return EXIT_SUCCESS;
}


int enqueue(int newEl) {
	position newNode = NULL;

	newNode = malloc(sizeof(Node));

	if (!newNode) {
		printf("\nUnable to allocate memory for newnode\n");
		return FAILED_MEMORY_ALLOCATION;
	}

	newNode->el = newEl;
	newNode->next = NULL;

	if (front == NULL && rear == NULL) {

		front = rear = newNode;		//zbog ovoga moramo koristit globalne var (ili duple pokazivace) jer da smo inicijalizirali front i rear u mainu i slali ih u f-fju onda bi s ovime mijenjali adrese na koje pokazuju kopije pokazivaca front i rear, koje nastaju u f-ji kad ih posaljemo u nju, a ta se radnja napravi uvijek samo u tom bloku tj lokalno pa bi izvan ove fje front i rear jos uvijek bili NULL (kad su varijable globalne ne moramo ih slat u f-ju tj nema potrebe za kopijama varijabli unutar f-ja jer je njima cijeli kod podatkovni blok)
	}

	else {
	
		rear->next = newNode;

		rear = newNode;

	}

	printf("\nElement je dodan na kraj reda!\n");

	return EXIT_SUCCESS;
}


int dequeue() {
	position temp = NULL;

	if (front== NULL) {
		printf("\nStog nema elemenata!\n");
	}

	else {

		temp = front;

		front = front->next;

		if (front == NULL)
			rear = NULL;

		free(temp);

		printf("\nElement s pocetka reda je skinut!\n");
	}

	return EXIT_SUCCESS;
}*/