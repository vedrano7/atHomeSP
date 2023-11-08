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

int readCodeAndCheckAFter(FILE* fileName,position head);
int push(char cFromFIle, position head);
int pop(position prevToLastEl);
int check(char cFromFile, position head);

//int pop(char cFromFile, position head);
//int check(char cFromFile, char cFromList);

int main() {
	Node head = { '\0' ,NULL};
	FILE* fileName=NULL;

	readCodeAndCheckAFter(fileName,&head);

	return EXIT_SUCCESS;
}

int readCodeAndCheckAFter(FILE* fileName, position head) {
	char c = '\0';

	fileName = fopen("check_code.txt", "r");

	while (!feof(fileName)) {
		c = fgetc(fileName);

		if (c == '(' || c == '[' || c == '{') {

			push(c, head);
		}

		else if (c == ')' || c == ']' || c == '}') {

			check(c, head);
		}

		else
			continue;

	}

	

	if(head->next!=NULL)											//s ovime provjerama imaju li neke otvorene zagrade same u stogu (to ce bit ako su one zadnje napisane u kodu) jer ako ima to znaci da nemaju para u kodu jer bi inace bile popane i time bi bia prazan stog
		printf("\nSyntax error regarding brackets in code!\n");

	fclose(fileName);

	return EXIT_SUCCESS;
}


int push(char cFromFile, position head) {
	position newNode = NULL, current = head;

	newNode = malloc(sizeof(Node));

	if (!newNode) {
		printf("\nUnable to allocate memory for newnode\n");
		return FAILED_MEMORY_ALLOCATION;
	}

	newNode->bracket = cFromFile;

	while (current->next != NULL)
		current = current->next;

	newNode->next = current->next;
	current->next = newNode;


	return EXIT_SUCCESS;
}

int check(char cFromFile, position head) {
	position current = head;
	int status = 0;

	if (head->next == NULL)
		printf("\nSyntax error regarding brackets in code!\n");

	else {

		while (current->next->next != NULL)
			current = current->next;

		if ((current->next->bracket == '(' && cFromFile == ')') || (current->next->bracket == '[' && cFromFile == ']') || (current->next->bracket == '{' && cFromFile == '}'))
			pop(current);

		else
			printf("\nSyntax error regarding brackets in code!\n");

	}

	return EXIT_SUCCESS;
}

int pop(position prevToLastEl) {
	position temp = NULL;
	int status = 0;

	temp = prevToLastEl->next;
	prevToLastEl->next = temp->next;

	free(temp);

	return EXIT_SUCCESS;
}