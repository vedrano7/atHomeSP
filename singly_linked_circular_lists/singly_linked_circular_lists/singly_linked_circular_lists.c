#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define MAX 99

typedef struct node* position;

typedef struct node {
	int el;
	position next;
}Node;



int menu(position head);
int printList(position firstEl);

int insertStart(position head);

int insertEnd(position head);

position search(position firstEl);

int delete(position head);

int insertAfterEl(position head);

int insertBehindEl(position head);

int delAll(position head);

int sortInput(position head);



int main() {
	Node head = { 0,NULL };

	menu(&head);

	return 0;
}


int menu(position head) {
	char pick = '\0';
	position Q = NULL;

	while (1) {
		printf("\nZa dodati novi element na pocetak liste upisite 1, za ispisati listu upisite 2, za dodati novi element na kraj liste upisite 3, za pronaci odredeni element u listi upisite 4, za izbrisati odredeni element iz liste upisite 5,za umetnuti element iza odredenog elementa upisite 6, za umetnuti element ispred odredenog elementa upisite 7, za izbrisati cijelu listu upisite 8, za sortirani unos u listu upisite 9 te upisite 0 za izaci iz programa\n");
		scanf("\n%c", &pick);
		switch (pick) {

		case '1':

			insertStart(head);

			continue;

		case '2':

			printList(head->next);

			continue;

		case '3':

			insertEnd(head);

			continue;

		case '4':
			Q = search(head->next);
			if (Q == NULL)
				printf("\nElement nije naden u listi\n");
			else
				printf("\nElement %d je naden na adresi %p\n", Q->el, Q);;

			continue;

		case '5':
			delete(head);

			continue;

		case '6':
			insertAfterEl(head);

			continue;

		case '7':
			insertBehindEl(head);

			continue;

		case '8':
			delAll(head);

			continue;

		case '9':
			sortInput(head);

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


	return 0;
}


int printList(position firstEl) {
	position current = firstEl;

	printf("\n------------\n");

	if (firstEl == NULL)
		printf("Lista je prazna!\n");

	else {

		do {
			printf("%d\n", current->el);
			current = current->next;

		} while (current != firstEl);


	}

	printf("------------\n");

	return 0;

}

int insertStart(position head) {
	position newNode = NULL, current = head->next;

	newNode = malloc(sizeof(Node));

	if (!newNode) {
		printf("\nUnable to allocate memory for newNode\n");
		return -1;
	}

	printf("\nUnesite vrijednost novog elementa: ");
	scanf("%d", &newNode->el);

	newNode->next = head->next;
	head->next = newNode;

	if (newNode->next == NULL)
		newNode->next = newNode;


	else {

		do {
			current = current->next;
		} while (current->next != newNode->next);

		current->next = newNode;
	}


	return 0;
}

int insertEnd(position head) {

	position newNode = NULL, refToFirstEl = head->next, current = head->next;

	newNode = malloc(sizeof(Node));

	if (!newNode) {
		printf("\nNeuspjela alokacija memorije za newNode\n");
		exit(-1);
	}

	printf("\nUnesite novi element:\n");
	scanf("%d", &newNode->el);

	if (head->next == NULL) {
		head->next = newNode;
		newNode->next = newNode;
	}

	else {

		do {
			current = current->next;
		} while (current->next != refToFirstEl);

		current->next = newNode;
		newNode->next = refToFirstEl;

	}

	return 0;
}

position search(position firstEl) {

	int wantedEl = 0;
	position current = firstEl, refToFirstEl = firstEl;

	printf("\nUnesite trazeni element: \n");
	scanf("%d", &wantedEl);


	do {

		current = current->next;

	} while (current != refToFirstEl && current->el != wantedEl);

	if (current->el == wantedEl)
		return current;

	else
		return NULL;
}

int delete(position head) {

	int wantedToDel = 0;
	position toDel = NULL, current = head, refToFirstEl = head->next, prev = NULL;

	printf("\nUnesite element koji zelite izbrisati iz liste:\n");
	scanf("%d", &wantedToDel);

	do {

		prev = current;
		current = current->next;

	} while (current->next != refToFirstEl && current->el != wantedToDel);


	if (current->el == wantedToDel) {

		if (current == refToFirstEl) {
			toDel = current;

			if (toDel->next != toDel) {

				head->next = toDel->next;

				do {

					current = current->next;
				} while (current->next != toDel);

				current->next = head->next;
			}

			else
				head->next = NULL;

			free(toDel);

			printf("\nElement %d je obrisan!\n", wantedToDel);

		}

		else {

			toDel = current;
			prev->next = toDel->next;
			free(toDel);

			printf("\nElement %d je obrisan!\n", wantedToDel);

		}

	}


	else
		printf("\nTog clana nema u listi\n");

	return 0;
}

int insertAfterEl(position head) {

	int afterWhichElToInsert = 0, newElToIns = 0;
	position newNode = NULL, current = head, refToFirstEl = head->next;

	printf("\nIza kojeg elementa zelite umetnuti element i koji to?\n");
	scanf("%d %d", &afterWhichElToInsert, &newElToIns);

	do {
		current = current->next;
	} while (current->next != refToFirstEl && current->el != afterWhichElToInsert);


	if (current->el == afterWhichElToInsert) {

		newNode = malloc(sizeof(Node));

		if (!newNode) {
			printf("\nNeuspjela alokacija memorije za newNode\n");
			exit(-1);
		}

		newNode->el = newElToIns;

		newNode->next = current->next;
		current->next = newNode;



	}

	else
		printf("\nElement iza kojeg zelite umetnuti element nije pronaden u listi\n");


	return 0;
}

int insertBehindEl(position head) {


	int behindWhichElToIns = 0, newElToIns = 0;
	position newNode = NULL, current = head, refToFirstEl = head->next;

	printf("\nIspred kojeg elementa zelite umetnuti element i koji to?\n");
	scanf("%d %d", &behindWhichElToIns, &newElToIns);

	do {
		current = current->next;
	} while (current->next != refToFirstEl && current->next->el != behindWhichElToIns);


	if (current->next->el == behindWhichElToIns) {

		newNode = malloc(sizeof(Node));

		if (!newNode) {
			printf("\nNeuspjela alokacija memorije za newNode\n");
			exit(-1);
		}

		newNode->el = newElToIns;


		newNode->next = current->next;
		current->next = newNode;

		if (behindWhichElToIns == refToFirstEl->el)
			head->next = newNode;
	}

	else
		printf("\nElement ispred kojeg zelite umetnuti element nije pronaden u listi\n");


	return 0;
}

int delAll(position head) {
	position toDel = NULL, current = head;


	while (head->next != NULL) {

		toDel = head->next;

		if (toDel->next != toDel) {

			current = head;

			head->next = toDel->next;

			do {

				current = current->next;
			} while (current->next != toDel);

			current->next = head->next;
		}

		else
			head->next = NULL;

		free(toDel);


	}


	return 0;
}

int sortInput(position head) {
	position newNode = NULL, current = head, refToFirstEl = head->next;

	newNode = malloc(sizeof(Node));

	if (!newNode) {
		printf("\nNeuspjela alokacija memorije za newNode\n");
		exit(-1);
	}

	printf("\nUpisite novi element: \n");
	scanf("%d", &(newNode->el));

	if (head->next == NULL) {

		head->next = newNode;
		newNode->next = newNode;

	}

	else {

		do {

			current = current->next;

		} while (current->next != refToFirstEl && current->next->el < newNode->el);


		if (current->next->el >= newNode->el) {		//kad dodajemo prije nekog clana

			if (refToFirstEl->el >= newNode->el) {	//kad je to prije prvog clana

				head->next = newNode;
				newNode->next = refToFirstEl;

				//ne moramo stavljat current=refToFirstEl zato sto ce uvjeti vanjskog i unutarnjeg if-a bit zadovoljeni samo kad je current->next->el veci od novog elementa i ako je prvi element veci od novog elementa a to ce bit odma prvi prvoj iteraciji u do-while petlji jer ako je novi element manji od prvog elementa logicno da je i manji od svih ostalih pa compiler izade iz do-while petlje odma nakon sta ude i current ostaje prvi element
				do {
					current = current->next;
				} while (current->next != refToFirstEl);

				current->next = newNode;
			}

			else {								//kad je to prije nekog clana koji nije prvi

				newNode->next = current->next;
				current->next = newNode;

			}

		}

		else {								//kad dodajemo poslije svih (tj. poslije zadnjeg clana)

			newNode->next = current->next;
			current->next = newNode;
		}
	}

	return 0;
}
