#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>

typedef struct TreeNode* position;
typedef struct TreeNode {
	int el;
	position leftChild, rightChild;
}treeNode;

int menu(position treeHead);
position createEmpty(position firstRoot);
position findMin(position firstRoot);
position findMax(position firstRoot);



int main() {
	treeNode treeHead = { 0,NULL,NULL };

	menu(&treeHead);



	return EXIT_SUCCESS;
}

int menu(position treeHead) {
	char pick = '\0';
	position result = NULL;

	while (1) {
		printf("\nUpisite 1 za kreirati prazno stablo, 2 za naci minimalan element u stablu, 3 za naci maksimalan element u stablu a 0 za izaci iz programa\n");
		scanf(" %c", &pick);

		switch (pick) {
			case '0':

				printf("\nKraj programa!\n");

				break;

			case '1':
				result = createEmpty(treeHead->leftChild);

				if (result == NULL)
					printf("\nUspjesno kreirano prazno stablo!\n");

				else
					printf("\nNespjesno kreiranje praznog stabla!\n");

				continue;

			case '2':
				result=findMin(treeHead->leftChild);

				if (result != NULL)
					printf("\nNajmanji clan u stablu je: %d\n", result->el);

				else
					printf("\nNeuspjelo pronalazanje minimalnog elementa!\n");

				continue;

			case '3':
				result = findMax(treeHead->leftChild);

				if (result != NULL)
					printf("\nNajveci clan u stablu je: %d\n", result->el);

				else
					printf("\nNeuspjelo pronalazanje maksimalnog elementa!\n");

				continue;

			default:

				printf("\nKrivi unos!!\n");

				continue;
		}
	
		break;
	}

	return EXIT_SUCCESS;
}

position createEmpty(position firstRoot) {
	position currentRoot = firstRoot;

	if (currentRoot == NULL)
		return NULL;

	else {
		createEmpty(currentRoot->leftChild);
		createEmpty(currentRoot->rightChild);
		free(currentRoot);
	}

	return NULL;
}

position findMin(position firstRoot) {
	position currentRoot = firstRoot;

	if (currentRoot == NULL)
		return NULL;

	else {

		if (currentRoot->leftChild == NULL)
			return currentRoot;
		else
			return(findMin(currentRoot->leftChild));
	}
}

position findMax(position firstRoot) {
	position currentRoot = firstRoot;

	if (currentRoot == NULL)
		return NULL;

	else {

		if (currentRoot->rightChild == NULL)
			return currentRoot;
		else
			return(findMin(currentRoot->rightChild));
	}
}

