// SINGLY LINKED LISTS (JEDNOSTRUKE POVEZANE LISTE)

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define MAX 99

typedef struct node* position;

typedef struct node {
	int el;
	position next;
}Node;



int menu(position head);  //funkcija za biranje akcije

int printList(position P);		//ispis liste

int insertStart(position P);		 //umetanje clana  na pocetak liste

int insertEnd(position P);		//umetanje elemenata na kraj liste

position search(position P);		//trazenje nekog elementa u listi

position searchPrev(position P);		 //trazenje prethodnog elementa

int delete(position P);		 //trazenje prethodnog elementa

int insertAfterEl(position P);		 //umetanje iza odredenog elementa

int insertBehind(position P);		//umetanje ispred odredenog elementa

int delAllFromBegg(position P);		//brisanje cijele liste od pocetka

int delAllFromEnd(position P);		//brisanje cijele liste od kraja

int sortList(position P);		//sortiranje liste (NE KORISTIT U ISPITU!!!!!!!)

int sortInput(position P);		//sortirani unos elemenata u listu



int main() {
	Node head = { 0,NULL };

	menu(&head);

	return 0;
}

//menu za funkcije

int menu(position head) {
	char pick = '\0';
	position Q = NULL;

	while (1) {
		printf("\nZa dodati novi element na pocetak liste upisite 1, za ispisati listu upisite 2, za dodati novi element na kraj liste upisite 3, za pronaci odredeni element u listi upisite 4, za izbrisati odredeni element iz liste upisite 5,za naci prethodnika nekog elementa upisite 6, za umetnuti element iza odredenog elementa upisite 7, za umetnuti element ispred odredenog elementa upisite 8, za izbrisati cijelu listu s pocetka upisite 9, za izbrisati cijelu listu s kraja upisite 'a', za sortiranje liste upisite 'b', za sortirani unos u listu upisite 'c' te upisite 0 za izaci iz programa\n");
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
				Q = searchPrev(head);

				if (Q == NULL)
					printf("\nElement nije naden u listi\n");

				else {
					if (Q == head)
						printf("\nElement nema prethodnika u listi\n");
					else
						printf("\nPrethodnik trazenog elementa je %d\n", Q->el);
				}

				continue;

			case '7':
				insertAfterEl(head->next);

				continue;

			case '8':
				insertBehind(head);

				continue;

			case '9':
				delAllFromBegg(head);

				continue;

			case 'a':
				delAllFromEnd(head);

				continue;

			case 'b':
				sortList(head);

				continue;

			case 'c':
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

//ispis funkcije

int printList(position P) {

	printf("\n------------\n");

	if (P == NULL)
		printf("Lista je prazna!\n");

	else {
		while (P != NULL) {

			printf("%d\n", P->el);
			P = P->next;
		}


	}

	printf("------------\n");

	return 0;

}

//umetanje clana  na pocetak liste

int insertStart(position P) {

	position newNode = NULL;

	newNode = (Node*)malloc(sizeof(Node));

	if (!newNode) {
		printf("\nNeuspjela alokacija memorije za newNode\n");
		exit(-1);
	}

	printf("\nUnesite novi element:\n");
	scanf("%d", &newNode->el);

	//umetanje clana  na pocetak liste koja ne sadrzi elemente

	if (P->next == NULL) {
		P->next = newNode;
		newNode->next = NULL;
	}

	//umetanje clana  na pocetak liste koja sadrzi elemente

	else {
		newNode->next = P->next;
		P->next = newNode;
	}

	return 0;
}

//umetanje elemenata na kraj liste

int insertEnd(position P) {

	position newNode = NULL;

	newNode = malloc(sizeof(Node));

	if (!newNode) {
		printf("\nNeuspjela alokacija memorije za newNode\n");
		exit(-1);
	}

	printf("\nUnesite novi element:\n");
	scanf("%d", &newNode->el);

	while (P->next != NULL) {

		P = P->next;
	}

	newNode->next = P->next;
	P->next = newNode;

	return 0;
}

//trazenje nekog elementa u listi

position search(position P) {

	int wantedEl = 0;

	printf("\nUnesite trazeni element: \n");
	scanf("%d", &wantedEl);

	while (P != NULL && P->el != wantedEl) {

		P = P->next;
	}

	if (P == NULL)
		return NULL;

	else
		return P;

}

//trazenje prethodnog elementa

position searchPrev(position P) {

	//nacin sa varijablon prev

	//int wantedPrev = 0;

	//printf("\nUnesite trazeni element: \n");
	//scanf("%d", &wantedPrev);

	//Node* prev;

	//prev = P;
	//
	//P = P->next;    //ovo moramo stavit jer cemo prev morat postavit kao clan prije P a prije nego sta ovo napravimo P je head koji nema clan prije njega

	//prev->next = P;

	//

	//while (P != NULL && P->el != y) {

	   //	prev=P;
	   //	P = P->next;
	//}

	//if (P == NULL)
	   // return NULL;

	//else
	   // return prev;



	//nacin bez prev

	int wantedPrev = 0;

	printf("\nUnesite trazeni element: \n");
	scanf("%d", &wantedPrev);

	while (P->next != NULL && P->next->el != wantedPrev)
		P = P->next;


	if (P->next == NULL)
		return NULL;


	else
		return P;




}

//brisanje odredenog elementa

int delete(position P) {

	//nacin koji koristi trazenje prethodnika

	/*
	int wantedToDel = 0;
	position prev=NULL,temp=NULL;

	printf("\nUnesite element koji zelite izbrisati iz liste:\n");
	scanf("%d%", &wantedToDel);

	prev = searchPrev(P,wantedToDel);

	if (!prev)
		printf("\nElement nije pronaden u listi\n");

	else {

	   temp = prev->next;
	   prev->next = temp->next;
	   free(temp);

	}*/

	//nacin bez trazenja prethodnika

	int wantedToDel = 0;
	position temp = NULL;

	printf("\nUnesite element koji zelite izbrisati iz liste:\n");
	scanf("%d%", &wantedToDel);

	while (P->next != NULL && P->next->el != wantedToDel) {

		P = P->next;

	}

	if (P->next == NULL)
		printf("\nTog clana nema u listi\n");

	else {

		temp = P->next;
		P->next = temp->next;
		printf("\nElement %d je obrisan!\n", wantedToDel);
	}

	free(temp);

	return 0;
}

//umetanje iza odredenog elementa

int insertAfterEl(position P) {

	//nacin koji koristi trazenje

   /* int afterWhichElToInsert = 0, newElToIns = 0;
	position newNode = NULL;

	printf("\nIza kojeg elementa zelite umetnuti element i koji to?\n");
	scanf("%d %d", &afterWhichElToInsert, &newElToIns);

	P = search(P, afterWhichElToInsert);

	if (P==NULL)
		printf("\nElement iza kojeg zelite umetnuti element nije pronaden u listi\n");

	else {
		newNode = malloc(sizeof(Node));
		newNode->el = newElToIns;

		newNode->next = P->next;
		P->next = newNode;

	}*/

	//nacin bez trazenja

	int afterWhichElToInsert = 0, newElToIns = 0;
	position newNode = NULL;

	printf("\nIza kojeg elementa zelite umetnuti element i koji to?\n");
	scanf("%d %d", &afterWhichElToInsert, &newElToIns);

	while (P != NULL && P->el != afterWhichElToInsert) {
		P = P->next;
	}

	if (P == NULL)
		printf("\nElement iza kojeg zelite umetnuti element nije pronaden u listi\n");

	else {
		newNode = malloc(sizeof(Node));

		if (!newNode) {
			printf("\nNeuspjela alokacija memorije za newNode\n");
			exit(-1);
		}

		newNode->el = newElToIns;

		newNode->next = P->next;
		P->next = newNode;

	}


	return 0;
}

//umetanje ispred odredenog elementa

int insertBehind(position P) {

	//nacin koji koristi trazenje prethodnika

	/*
	int behindWhichElToIns = 0, wantedElToIns = 0;
	position newNode=NULL;

	printf("\nIspred kojeg elementa zelite umetnuti element i koji to?\n");
	scanf("%d %d", &behindWhichElToIns, &wantedElToIns);

	P = searchPrev(P, behindWhichElToIns);

	if(!P)
		printf("\nElement ispred kojeg zelite umetnuti element nije pronaden u listi\n");

	else {
		newNode = malloc(sizeof(Node));
		newNode->el = wantedElToIns;

		newNode->next = P->next;
		P->next = newNode;

	}*/

	//nacin bez trazenja prethodnika

	int behindWhichElToIns = 0, wantedElToIns = 0;
	position newNode = NULL;

	printf("\nIspred kojeg elementa zelite umetnuti element i koji to?\n");
	scanf("%d %d", &behindWhichElToIns, &wantedElToIns);

	while (P->next != NULL && P->next->el != behindWhichElToIns) {
		P = P->next;
	}

	if (P->next == NULL)
		printf("\nElement ispred kojeg zelite umetnuti element nije pronaden u listi\n");

	else {
		newNode = malloc(sizeof(Node));

		if (!newNode) {
			printf("\nNeuspjela alokacija memorije za newNode\n");
			exit(-1);
		}

		newNode->el = wantedElToIns;

		newNode->next = P->next;
		P->next = newNode;

	}
	return 0;
}

//brisanje cijele liste od početka

int delAllFromBegg(position P) {
	position temp = NULL;

	while (P->next != NULL) {
		temp = P->next;
		P->next = temp->next;
		free(temp);
	}

	return 0;
}

//brisanje cijele liste od kraja

int delAllFromEnd(position P) {
	position temp = NULL;
	position head = P;

	while (P->next != NULL) {
		while (P->next->next != NULL)
			P = P->next;

		temp = P->next;
		P->next = temp->next;

		free(temp);

		P = head;

	}

	return 0;
}

//sortiranje liste

int sortList(position P) {
	position j = NULL, prev_j = NULL, temp = NULL, end = NULL;



	while (P->next!= end) {		//mogli smo i stavit while(P->next->next!=end) jer ako sortiramo sve osim jednog elementa i taj jedan sigurno mora bit sortiran (zato u bubble sortu za niz vanjska for petlja ide do N-1) 

		prev_j = P;
		j = P->next;


		while (j->next != end) {


			if (j->el > j->next->el) {

				temp = j->next;

				prev_j->next = temp;
				j->next = temp->next;
				temp->next = j;

				j = temp;		//ovo radimo zato sto je nakon zamjene redoslijed: prev_j pa temp pa j , sto ne bi trebalo bit jer nastavak koda nebi imao smisla (j bi uvijek trebao bit poslije prev_j) pa zato j pripisujemo adresu tempa
			}

			prev_j = j;
			j = j->next;


		}

		end = j;		//postavljamo kraj na j jer je j->next sada zapravo najveci element koji je doveden na kraj (ili NULL ako je prva iteracija) prema principu bubble sorta pa u slijedecoj iteraciji unutarnje while petlje kada j->next dode na tu vrijednost izac ce iz petlje jer nema svrhe da gledamo je li njegov prethodnik veci od njega kad znamo da je on najveci u listi (u prvoj iteraciji kraj ide sa NULL na zadnji el i onda se samo mice za jedan el prema lijevo pri svakoj iteraciji sve dok ne dode do prvog el)
	}					//takoder s time priblizavamo kraj vanjskoj while petlji tako da ona zna kad smo sortirali sve elemente


	return 0;
}

////sortirani unos u listu

int sortInput(position P) {
	position newNode = NULL;

	newNode = malloc(sizeof(Node));

	if (!newNode) {
		printf("\nNeuspjela alokacija memorije za newNode\n");
		exit(-1);
	}

	printf("\nUpisite novi element: \n");
	scanf("%d", &(newNode->el));

	while (P->next != NULL && P->next->el < newNode->el)
		P = P->next;

	newNode->next = P->next;
	P->next = newNode;

	return 0;
}
