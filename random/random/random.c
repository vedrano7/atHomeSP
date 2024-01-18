#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include <string.h>
#define MAXLINESIZE (100)
#define MAXNAMESIZE (50)

typedef struct ListNodeB* positionListNodeB;
typedef struct ListNodeB {
	char cityName[MAXNAMESIZE];
	int cityPopulation;
	positionListNodeB next;
}listNodeB;

typedef struct TreeNodeB* positionTreeNodeB;
typedef struct TreeNodeB {
	char countryName[MAXNAMESIZE];

	positionListNodeB headCities;

	positionTreeNodeB leftChild;
	positionTreeNodeB rightChild;
}treeNodeB;


int problemB();
positionTreeNodeB makeCountryTreeAndCityList(char* filename, positionTreeNodeB rootCountryTree);
positionTreeNodeB countryTreeSortInsert(positionTreeNodeB root, char* countryName);
positionTreeNodeB createTreeNodeB(char* countryName);
positionListNodeB createCityListNode(int cityPop, char* cityName);
int readFromCityFileAndMakeLists(positionTreeNodeB rootCountryTree, char* countryName, char* cityFileName);
positionTreeNodeB findCountryNode(positionTreeNodeB root, char* countryName);
int cityListSortInsert(positionListNodeB head, int cityPop, char* cityName);
positionListNodeB createCityListNode(int cityPop, char* cityName);
int inorderPrintCountryTreeAndCityLists(positionTreeNodeB root);
int printCityList(positionListNodeB firstEl);
int printCitiesWithGreaterPopulationB(positionTreeNodeB rootCountry, int inputPopNum);
positionListNodeB findGreaterPopCityB(positionListNodeB firstEl, int inputPopNum);
int printCitiesB(positionTreeNodeB countryNode, positionListNodeB firstGreaterPopCity, positionListNodeB firstEl);


int main() {
	char pick = '\0';

	printf("\nUkoliko zelite zadatak pod a) upisite 'a', a ukoliko zelite zadatak pod b) upisite 'b'\n");
	scanf("%c", &pick);

	/*if (pick == 'a')
		problemA();

	else*/
		problemB();

		return EXIT_SUCCESS;
}

int problemB() {
	positionTreeNodeB rootCountryTree = NULL;
	int inputPopNum = 0;
	
	rootCountryTree =makeCountryTreeAndCityList("drzave.txt", rootCountryTree);
	
	printf("\n---------\n");

	inorderPrintCountryTreeAndCityLists(rootCountryTree);

	printf("---------\n");
	
	printf("\nUpisite odredeni broj stanovnika i mi cemo Vam ispisati imena svih gradova ovdje upisano s vecim!\n");
	scanf("%d", &inputPopNum);
	
	printCitiesWithGreaterPopulationB(rootCountryTree, inputPopNum);
	
	return EXIT_SUCCESS;
}

positionTreeNodeB makeCountryTreeAndCityList(char* filename, positionTreeNodeB rootCountryTree) {
	FILE* countriesFile = NULL;
	char buffer[MAXNAMESIZE] = { 0 }, countryName[MAXNAMESIZE] = { 0 }, cityFileName[MAXNAMESIZE] = { 0 };


	countriesFile = fopen(filename, "r");

	if (!countriesFile) {
		printf("\nUnable to open file countriesFile!\n");
		return EXIT_FAILURE;
	}

	while (!feof(countriesFile)) {
		fgets(buffer, MAXLINESIZE, countriesFile);
		sscanf(buffer, "%s %s", countryName, cityFileName);

		rootCountryTree = countryTreeSortInsert(rootCountryTree, countryName);
		readFromCityFileAndMakeLists(rootCountryTree,countryName, cityFileName);
	}

	return rootCountryTree;
}

positionTreeNodeB countryTreeSortInsert(positionTreeNodeB root, char* countryName) {
	
	if (root == NULL)
		return createTreeNodeB(countryName);
	
	else if (strcmp(countryName, root->countryName) < 0)
		root->leftChild = countryTreeSortInsert(root->leftChild, countryName);
	
	else if (strcmp(countryName, root->countryName) > 0)
		root->rightChild = countryTreeSortInsert(root->rightChild,countryName);
	
	return root;
}
	
positionTreeNodeB createTreeNodeB(char* countryName) {
	positionTreeNodeB newNode = NULL;

	newNode = malloc(sizeof(treeNodeB));

	if (!newNode) {
		printf("\nUnable to allocate memory for newNode!\n");
		return NULL;
	}

	strcpy(newNode->countryName, countryName);

	newNode->headCities = malloc(sizeof(listNodeB));
	newNode->headCities->next = NULL;

	newNode->leftChild = NULL;
	newNode->rightChild = NULL;

	return newNode;
}

int readFromCityFileAndMakeLists(positionTreeNodeB rootCountryTree, char* countryName, char* cityFileName) {
	FILE* cityFile = NULL;
	char buffer[MAXNAMESIZE] = { 0 }, cityName[MAXNAMESIZE] = { 0 };
	int cityPopulation = 0;
	positionTreeNodeB countryNode = NULL;

	cityFile = fopen(cityFileName, "r");

	if (!cityFile) {
		printf("\nUnable to open file countriesFile!\n");
		return EXIT_FAILURE;
	}


	while (!feof(cityFile)) {
		fgets(buffer, MAXLINESIZE, cityFile);
		sscanf(buffer, "%[^,]%*c%d", cityName, &cityPopulation);	//za ime grada uzima sve do zareza onda uzima i odma odbacuje zarez i zadnje uzima broj za populaciju grada


		countryNode = findCountryNode(rootCountryTree, countryName);
		cityListSortInsert(countryNode->headCities, cityPopulation, cityName);

	}

	return EXIT_SUCCESS;
}

positionTreeNodeB findCountryNode(positionTreeNodeB root, char* countryName) {
	if (root == NULL)
		return NULL;

	else if (strcmp(countryName,root->countryName)<0)
		return findCountryNode(root->leftChild, countryName);

	else if (strcmp(countryName, root->countryName) > 0)
		return findCountryNode(root->rightChild, countryName);

	return root;
}

int cityListSortInsert(positionListNodeB head, int cityPop, char* cityName) {
	positionListNodeB newNode = NULL, current = head;

	newNode = createCityListNode(cityPop, cityName);

	while (current->next != NULL && newNode->cityPopulation > current->next->cityPopulation)
		current = current->next;

	if (current->next == NULL || newNode->cityPopulation != current->next->cityPopulation) {

		newNode->next = current->next;
		current->next = newNode;
	}
	
	else {

		while (current->next != NULL && strcmp(newNode->cityName, current->next->cityName) > 0)
			current = current->next;

		newNode->next = current->next;
		current->next = newNode;
	}

	return EXIT_SUCCESS;
}

positionListNodeB createCityListNode(int cityPop, char* cityName) {
	positionListNodeB newNode = NULL;

	newNode = malloc(sizeof(listNodeB));

	if (!newNode) {
		printf("\nNeuspjela alokacija memorije za newNode\n");
		exit(-1);
	}

	strcpy(newNode->cityName, cityName);
	newNode->cityPopulation = cityPop;
	newNode->next = NULL;

	return newNode;
}

int inorderPrintCountryTreeAndCityLists(positionTreeNodeB root) {
		
	if (root != NULL) {
		inorderPrintCountryTreeAndCityLists(root->leftChild);
		printf("%s ->", root->countryName);
		printCityList(root->headCities->next);
		printf("\n");
		inorderPrintCountryTreeAndCityLists(root->rightChild);
	}
		
	return 0;
}
	
int printCityList(positionListNodeB firstEl) {
	positionListNodeB current = firstEl;

	if (current == NULL)
		printf("Nema upisanih gradova!\n");

	else {
		while (current != NULL) {

			printf("   %s   ", current->cityName);
			current = current->next;
		}
	}

	return 0;
}

int printCitiesWithGreaterPopulationB(positionTreeNodeB rootCountry, int inputPopNum) {
	positionListNodeB greaterPopCity = NULL;
	
	if (rootCountry != NULL) {
		printCitiesWithGreaterPopulationB(rootCountry->leftChild, inputPopNum);
		greaterPopCity=findGreaterPopCityB(rootCountry->headCities->next, inputPopNum);
		printCitiesB(rootCountry->countryName,greaterPopCity,rootCountry->headCities->next);
		printCitiesWithGreaterPopulationB(rootCountry->rightChild, inputPopNum);
	}
	
	return EXIT_SUCCESS;
}

positionListNodeB findGreaterPopCityB(positionListNodeB firstEl, int inputPopNum) {
	positionListNodeB current = firstEl;

	while (current != NULL && inputPopNum >= current->cityPopulation)
		current = current->next;

	return current;
}

int printCitiesB(positionTreeNodeB countryNode, positionListNodeB firstGreaterPopCity, positionListNodeB firstEl) {
	positionListNodeB current = firstGreaterPopCity;

	if (current == NULL)
		printf("\nNema gradova s vecim brojem stanovnika upisano u fajl '%s'!\n", countryNode->countryName);

	else {
		
		printf("\nGradovi s vecim brojem gradana upisani u fajl '%s' su: ", countryNode->countryName);

		while (current != NULL) {
			
			printf("   %s	", current->cityName);

			current = current->next;
		}

		printf("\n");
	}

	return 0;
}