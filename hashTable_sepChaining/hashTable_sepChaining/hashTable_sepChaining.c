//hash tablica s implementiranim zasebnim redovima kako bi se riješio problem jednoznačnosti preslikavanja
//ova hash tablica je napravljena s idejom da su njene ulazne vrijednosti brojevi (elementi ce bit cjelobrojni brojevi)

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include <math.h>

typedef struct ListNode* position;
typedef struct ListNode {
	int el;
	position next;	//ListNode pointer se odi koristi za povezivanje svake vezane liste tj redova
}listNode;

typedef struct ListNode* listPointer;			//definiramo ovo samo da nan bude lakse razlikovat različitu ulogu ListNode pointera u obje strukture

typedef struct HashTable* hashTabPointer;		//koristit ce se samo za slat tablicu u funkcije
typedef struct HashTable{
	int tabSize;
	listPointer* hashList;	//ListNode pointer se odi koristi za inicijaliziranje niza pointera na ListNode elemente (to cemo napravit dinamickom alokacijom poslije prema velTab) sto zap predstavlja niz elemenata hash tablice, a svaki od njih je zap head od svoje vezane liste sto sluzi u slucaju da dode do kolizija
}hashTable;


int menu(hashTabPointer hashT);
hashTabPointer initializeHashTab(int wantedTabSize);
int nextPrimeNum(int wantedTabSize);					//fja koja vraca prvi broje veci od wantedTabSize koji je ujedno i prost -> sluzi kako bi velicina tablice nakraju bila dovoljno velika za sve elemente (jer ce bit veca od wantedTabSize) i da (s velicinom koja je prost broj) dolazi do manje kolizija
int addElement(hashTabPointer hashT, int el);
int hashFunction(int key, int tabSize);					//fja preslikavanja koja vraca indeks mjesta na kojeg ce se broj kojeg ubacujemo u hash tablicu upisat (odi ce nama kljuc bit samo cjelobrojna vrijednost elementa (broja) koji se ubacuje u tablicu)
position findElement(hashTabPointer hashT,int wantedEl);			//fja koja trazi trazeni element u tablici (nizu) i vraca adresu cvora u kojem se taj element nalazi
int delHashT(hashTabPointer hashT);
int delLinkedList(position firstEl);

int main() {
	hashTable hashT = { 0,NULL };
	
	menu(&hashT);
	
	return EXIT_SUCCESS;
}

int menu(hashTabPointer hashT) {
	char pick = '\0';
	int num = 0;

	printf("\nUnesite zeljenu velicinu hash tablice: ");
	scanf("%d", &num);

	hashT = initializeHashTab(num);

	if (hashT != NULL)
		printf("\nUspjesno inicijalizirana hash tablica velicine %d!\n", hashT->tabSize);
	else
		printf("\nNespjesno inicijalizirana hash tablica!\n");

	while (1) {
		printf("\nZa dodati element u hash tablicu unesite 1, za naci element u njoj unesite 2, za inicijalizirat novu praznu hash tablicu da zamijeni trenutnu unesite 3, a za izaci iz programa unesite 0.\n");
		scanf(" %c", &pick);

		switch (pick) {

		case '0':

			printf("\nKraj programa!\n");

			break;

		case '1':
			
			printf("\nUnesite element koji zelite dodat: ");
			scanf("%d", &num);

			if (addElement(hashT, num) == EXIT_SUCCESS)
				printf("\nElement %d uspjesno dodan u tablicu na poziciju indeksa %d\n", num, hashFunction(num, hashT->tabSize));
			
			continue;

		case '2':

			printf("\nUnesite element kojeg zelite naci u tablici: ");
			scanf("%d", &num);

			if (findElement(hashT, num) != NULL)
				printf("\nElement %d uspjesno naden na adresi %p koja je vezana za poziciju indeksa %d u tablici\n", num, findElement(hashT, num), hashFunction(num, hashT->tabSize));

			else
				printf("\nElement %d se ne nalazi u tablici ili je tablica prazna!\n", num);

			continue;

		case '3':

			delHashT(hashT);

			printf("\nUnesite zeljenu velicinu nove hash tablice: ");
			scanf("%d", &num);

			hashT = initializeHashTab(num);

			if (hashT != NULL)
				printf("\nUspjesno inicijalizirana hash tablica velicine %d!\n", hashT->tabSize);
			else
				printf("\nNespjesno inicijalizirana hash tablica!\n");

			continue;

		default:
			printf("\nKrivi unos!!\n");

			continue;
		}

		break;

	}

	return EXIT_SUCCESS;
}

hashTabPointer initializeHashTab(int wantedTabSize) {
	hashTabPointer hashT = NULL;
	int i = 0;

	hashT = malloc(sizeof(hashTable));

	if (hashT == NULL) {
		printf("\nUnable to allocate memory for hashT!");
		return EXIT_FAILURE;
	}

	hashT->tabSize = nextPrimeNum(wantedTabSize);

	hashT->hashList = malloc(sizeof(listNode) * (hashT->tabSize));

	if (hashT->hashList == NULL) {
		printf("\nUnable to allocate memory for hashT->hashList!");
		free(hashT);
		return EXIT_FAILURE;
	}

	for (i=0; i < hashT->tabSize; i++)
		hashT->hashList[i] = NULL;

	return hashT;
}

int nextPrimeNum(int wantedTabSize) {
	int num = wantedTabSize, i = 0, isPrime = 1;

	while (1) {
		isPrime = 1;		//moramo pri svakom novom num resetirat na 1 zato sto ako to ne napravimo prime ce ostat 0 od proslog prolaska kroz petlju i tako ce se petlja vrtit zauvijek jer unutar nje se ne moze nikako promijenit na 1

		for (i = 2; i <= sqrt(num); i++) {		// iz matematike znamo da nemoramo provjeravat brojeve nakon korijena iz n za vidit je li broj prost
			if (num % i == 0) {
				isPrime = 0;
				break;
			}
		
		}

		if (isPrime == 1)
			break;

		num++;
	}
	
	return num;
}

int addElement(hashTabPointer hashT, int el) {
	position newHashTableEl;	//nazivamo ga ovako jer kao sto cemo vidjeti on ce postati onaj koji ce biti bas unutar tablice tj niza

	newHashTableEl = malloc(sizeof(listNode));

	if (newHashTableEl == NULL) {
		printf("\nUnable to allocate memory for newHashTableEl!");
		return EXIT_FAILURE;
	}

	newHashTableEl->el = el;

	//kada se u hash tablicu ostvarenu pomocu zasebnih redova dodaje element na neku poziciju koja je vec zauzeta onda se on UVIJEK dodaju na pocetak vezane liste tog reda (pozicije) i time zap zauzima mjesto prethodnog u tablici tj nizu, dok taj prethodni zajedno s ostaktom vezanih elemenata bude izvan tablice povezan samo s vezama vezane liste

	newHashTableEl->next = hashT->hashList[hashFunction(el, hashT->tabSize)];
	hashT->hashList[hashFunction(el, hashT->tabSize)] = newHashTableEl;

	return EXIT_SUCCESS;
}

int hashFunction(int key, int tabSize) {		//ovakva je fja preslikavanja uvijek kad su ulazne vrijednosti cijeli brojevi 
	return key % tabSize;
}

position findElement(hashTabPointer hashT, int wantedEl) {			//funkcionira tako da deklariramo pokazivac na listu kojem pridijelimo adresu pozicije u hash tablici na kojem bi se trazeni element nalazio u slucaju da je u tablici i onda prodemo cijelu vezanu listu te pozicije i trazimo ga
	listPointer wantedList=NULL, current=NULL;		

	wantedList = hashT->hashList[hashFunction(wantedEl, hashT->tabSize)];

	current = wantedList;

	while (current != NULL && current->el != wantedEl)
		current = current->next;

	return current;
}

int delHashT(hashTabPointer hashT) {
	int i = 0;

	for (; i < hashT->tabSize; i++) {
		if (hashT->hashList[i] != NULL)
			delLinkedList(hashT->hashList[i]);
	}

	free(hashT->hashList);

	free(hashT);

	return EXIT_SUCCESS;
}

int delLinkedList(position firstEl) {
	position current=firstEl,nodeToDel = NULL;

	while (current!= NULL) {
		nodeToDel = current;
		current= nodeToDel->next;
		free(nodeToDel);
	}

	return 0;
}
