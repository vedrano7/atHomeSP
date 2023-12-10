//Program koji provjerava jesu li sve zagrade u kodu pravilno zatvorene


#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#define FAILED_MEMORY_ALLOCATION (-1)

typedef struct node* position;

typedef struct node {		
	char bracket;
	position next;
}Node;

int readCodeAndCheckAFter(FILE* fileName,position top);
int push(char cFromFIle, position top);
int pop(position top);
int check(char cFromFile, position top);

int main() {
	Node head = { '\0' ,NULL};
	FILE* fileName=NULL;

	readCodeAndCheckAFter(fileName,&head);

	return EXIT_SUCCESS;
}

int readCodeAndCheckAFter(FILE* fileName, position top) {
	char c = '\0';

	fileName = fopen("check_code.txt", "r");

	while (!feof(fileName)) {
		c = fgetc(fileName);

		if (c == '(' || c == '[' || c == '{') {

			push(c, top);
		}

		else if (c == ')' || c == ']' || c == '}') {

			check(c, top);
		}

		else
			continue;

	}

	

	if(top->next!=NULL)											//s ovime provjerama imaju li neke otvorene zagrade same u stogu (to ce bit ako su one zadnje napisane u kodu) jer ako ima to znaci da nemaju para u kodu jer bi inace bile popane i time bi bia prazan stog
		printf("\nSyntax error regarding brackets in code!\n");

	fclose(fileName);

	return EXIT_SUCCESS;
}

int push(char cFromFile, position top) {
	position newNode = NULL;

	newNode = malloc(sizeof(Node));

	if (!newNode) {
		printf("\nUnable to allocate memory for newnode\n");
		return FAILED_MEMORY_ALLOCATION;
	}

	newNode->bracket = cFromFile;

	newNode->next = top->next;
	top->next = newNode;


	return EXIT_SUCCESS;
}

int check(char cFromFile, position top) {
	int status = 0;

	if (top->next == NULL)
		printf("\nSyntax error regarding brackets in code!\n");

	else {

		if ((top->next->bracket == '(' && cFromFile == ')') || (top->next->bracket == '[' && cFromFile == ']') || (top->next->bracket == '{' && cFromFile == '}'))
			pop(top);

		else
			printf("\nSyntax error regarding brackets in code!\n");

	}

	return EXIT_SUCCESS;
}

int pop(position top) {
	position temp = NULL;

	temp = top->next;
	top->next = temp->next;

	free(temp);

	return EXIT_SUCCESS;
}