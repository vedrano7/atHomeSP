//binarno pretrazivanje u nizu

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX 99


int inputElements(int* array, int noEl);
int sortElements(int* array, int noEl);
int binarySearch(int* array, int noEl, int* wantedElPosition);
int printArray(int* array, int noEl);

int main() {
	int* array = NULL, noEl = 0, wantedElPosition = -1, i = 0, pick;

	printf("\nUpisite broj clanovan niza :");
	scanf("%d", &noEl);

	array = malloc(sizeof(int) * noEl);

	for (i = 0; i < noEl; i++)
		array[i] = 0;

	inputElements(array, noEl);

	printArray(array, noEl);

	sortElements(array, noEl);

	printArray(array, noEl);

	while (1) {
		printf("\nUkoliko zelite pronaci neki element upisite 1,a ako ne upisite 0: \n");
		scanf("%d", &pick);

		if (pick == 1) {
			wantedElPosition = -1;

			binarySearch(array, noEl, &wantedElPosition);

			if (wantedElPosition != -1)
				printf("\nTrazeni element se nalazi na %d. mjestu u nizu!\n", wantedElPosition + 1);

			else
				printf("\nTrazeni element nije naden u nizu!\n");
		}

		else
			break;
	}

	return EXIT_SUCCESS;
}

int inputElements(int* array, int noEl) {
	int i = 0;

	for (i = 0; i < noEl; i++) {

		printf("\nUnesite %d. novi clan niza: ", i + 1);
		scanf("%d", &array[i]);
	}

	return EXIT_SUCCESS;
}

int sortElements(int* array, int noEl) {
	int i = 0, j = 0, temp = 0;

	for (i = 0; i < noEl - 1; i++) {

		for (j = 1; j < noEl - i; j++) {

			if (array[j - 1] > array[j]) {

				temp = array[j];
				array[j] = array[j - 1];
				array[j - 1] = temp;
			}

		}
	}

	return EXIT_SUCCESS;
}


int binarySearch(int* array, int noEl, int* wantedElPosition) {
	int startPositon = 0, endPosition = noEl - 1, middlePosition = 0, wantedEl = 0;

	printf("\nUnesite element koji zelite pronaci u nizu: ");
	scanf("%d", &wantedEl);

	while (startPositon <= endPosition && *wantedElPosition == -1) {			//ovo stavimo jer zelimo da while petlja prestane ili kad prodemo cijeli niz (tad ce startPosition ili endPosition doc na poziciju izvan niza te ce time startPosition postat veci od endPosition ili obrnuto) ili kad nademo trazeni element
		middlePosition = (endPosition + startPositon) / 2;

		if (array[middlePosition] == wantedEl)
			*wantedElPosition = middlePosition;


		else if (wantedEl > array[middlePosition])
			startPositon = middlePosition + 1;


		else
			endPosition = middlePosition - 1;

	}

	return EXIT_SUCCESS;
}

int printArray(int* array, int noEl) {
	int i = 0;

	printf("\n--------------------------------\n");

	for (i = 0; i < noEl; i++)
		printf(" %d ", array[i]);

	printf("\n---------------------------------\n");

	return EXIT_SUCCESS;
}