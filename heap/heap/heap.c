//ovo je heap implementiran pomocu niza kako bi izbjegli koristenje pokazivaca
//kljuc ovog heapa je vrijednost broja unutar svakog cvora tj. mjesta

#define	_CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_CAPACITY (50)

typedef struct HeapStruct* heapPointer;
typedef struct HeapStruct{
	int size;						// ovo je zap trenutni br elemenata u heapu
	int elArray[MAX_CAPACITY];		//popunjavanje niza pocinje od mjesta 1 (a ne 0 kao inace) kako bi mogli izvodit potrebne matematicke operacije s mjestima elemenata
}heapStruct;


int menu(heapPointer heap);
int push(heapPointer heap,int newEl);
int isFull(heapPointer heap);
int printHeap(heapPointer heap);
int pop(heapPointer heap);
int isEmpty(heapPointer heap);
int emptyEntireHeap(heapPointer heap);


int main() {
	heapStruct heap = { 0,{0}};

	menu(&heap);

	
	return EXIT_SUCCESS;
}

int menu(heapPointer heap) {
	char pick = '\0';
	int wantedEl = 0, res = 0;

	while (1) {
		printf("\nZa dodati novi element na heap (osim '0') upisite 1, za ispisati heap upisite 2, za izbrisati element iz heapa upisite 3, za isprazniti cijeli heap 4, te upisite 0 za izaci iz programa\n");
		scanf(" %c", &pick);
		switch (pick) {

		case '1':

			printf("\nUnesite element: ");
			scanf("%d", &wantedEl);

			res=push(heap, wantedEl);

			if (!res)
				printf("\nUspjesno dodan element %d u heap!\n", wantedEl);
			

			continue;

		case '2':

			printHeap(heap);

			continue;

		case '3':

			res=pop(heap);

			if (res)
				printf("\nUspjesno izbrisan element %d iz heapa!\n", res);
			

			continue;

		case '4':
			
			res= emptyEntireHeap(heap);

			if(!res)
				printf("\nUspjesno ispraznjen heap!\n");

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

int push(heapPointer heap,int newEl) {
	int i = 0;

	if (isFull(heap)==1) {
		printf("\nThe heap is full - no elements can be pushed!\n");
		return EXIT_FAILURE;
	}


	for (i = ++heap->size; heap->elArray[i / 2] > newEl; i /= 2)		// broj na poziciji i/2 je roditelj od broja na poziciji i
		heap->elArray[i] = heap->elArray[i / 2];

	heap->elArray[i] = newEl;

	return EXIT_SUCCESS;
}

int isFull(heapPointer heap) {
	int i = 0;

	if (heap->elArray[MAX_CAPACITY - 1] != 0)
		return 1;
	else
		return 0;
}

int printHeap(heapPointer heap) {
	int i = 0;
	
	printf("\n");

	if (heap->size != 0) {
		for (i = 1; i <= heap->size; i++)
			printf(" %d ", heap->elArray[i]);
		printf("\n");
	}

	else
		printf("Heap je prazan!\n");

	return EXIT_SUCCESS;
}

int pop(heapPointer heap) {
	int i = 0, poppedMinEl = heap->elArray[1], lastEl = heap->elArray[heap->size], smallerNumChildPosition = 0;

	if (isEmpty(heap) == 1) {
		printf("\nThe heap is empty - no elements can be popped!\n");
		return 0;
	}

	heap->elArray[heap->size] = 0;		//ovo dvoje odma napravimo jer predstavlja brisanje cvora zadnjeg elementa (ali s lastEl smo sacuvali njegovu vrijednost koju cemo onda sad odma nakon stavit na heap na prikladno mjesto)
	heap->size--;		

	for (i = 1;i*2<=heap->size; i = smallerNumChildPosition) {

		//trazimo manje od dvoje djece broja na poziciji i

		smallerNumChildPosition = i * 2;		// broj na poziciji i*2 je lijevo dijete od broja na poziciji i

			//moramo prvo provjerit je li broj na poziciji i uopce ima desno dijete ("smallerNumChildPosition != heap->size" nam to otkriva jer da zap ima samo lijevo dijete ono bi bilo na mjestu koje je jednako broju el na heapu)
		   //^
		if (smallerNumChildPosition != heap->size && heap->elArray[smallerNumChildPosition + 1] < heap->elArray[smallerNumChildPosition])		//broj na poziciji i*2+1 je desno dijete od broja na poziciji i
			smallerNumChildPosition++;

		//gledamo mozemo li upisat vrijednost (bivseg) zadnjeg el na mjesto praznog

		if (lastEl > heap->elArray[smallerNumChildPosition])			//uvjet ako ne mozemo
			heap->elArray[i] = heap->elArray[smallerNumChildPosition];		

		else
			break;	
	}

	if(heap->size!=0)
		heap->elArray[i] = lastEl;

	return poppedMinEl;
}

int isEmpty(heapPointer heap) {
	int i = 0;

	if (heap->size == 0)
		return 1;

	else
		return 0;
}

int emptyEntireHeap(heapPointer heap) {
	int i = 0;

	for (i = 1; heap->elArray[heap->size]; i++)
		heap->elArray[i] = 0;

	heap->size = 0;

	return heap->elArray[1];
}