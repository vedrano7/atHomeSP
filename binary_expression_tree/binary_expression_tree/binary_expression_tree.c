#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#define FAILED_MEMORY_ALLOCATION (-1)
#define MAX_LENGTH (100)
#define MAX_LINE (1024)

typedef struct TreeNode* positionTreeNode;		//struktura cvora binarnog stabla
typedef struct TreeNode {						
	char el;
	positionTreeNode leftChild;
	positionTreeNode rightChild;
}treeNode;

typedef struct StackNode* positionStackNode;	//struktura cvora stoga ciji elementi sadrze pokazivac na odredeni list stabla ("list" zato sto stavljamo samo operande na stog a oni su u stablu proracuna lisca jer nemaju djece) i pokazivac na sljedeci clan stoga
typedef struct StackNode {
	positionTreeNode treeLeaf;
	positionStackNode next;
}stackNode;


int readAndParsePostfixExpression(char* filename, positionTreeNode treeHead,positionStackNode stackTop,char* buffer);
positionTreeNode analyzeAndImplementChar(char c, positionStackNode stackTop);
int push(positionStackNode top,positionTreeNode newTreeNode);
positionTreeNode createTreeNode(char c);
positionTreeNode pop(positionStackNode stackTop );
int printTree(positionTreeNode root);



int main() {
	treeNode treeHead = { '\0',NULL,NULL };
	stackNode stackHead = { NULL,NULL };
	char buffer[MAX_LINE] = { '\0' };

	readAndParsePostfixExpression("postfixExpression.txt",&treeHead,&stackHead,buffer);

	printTree(treeHead.leftChild);

	return EXIT_SUCCESS;
}

int readAndParsePostfixExpression(char* filename,positionTreeNode treeHead, positionStackNode stackTop, char* buffer) {
	FILE* file = fopen(filename, "r");
	char c = '\0';
	int noBytes = 0;

	if (!file) {
		printf("\nUnable to open file %s", filename);
		return -1;
	}


	fgets(buffer, MAX_LINE, file);

	while (strlen(buffer) > 0) {
	
		sscanf(buffer, " %c %n", &c, &noBytes);

		treeHead->leftChild=analyzeAndImplementChar(c,stackTop);

		buffer += noBytes;
	}

	return EXIT_SUCCESS;
}

positionTreeNode analyzeAndImplementChar(char c, positionStackNode stackTop) {
	positionTreeNode newTreeNode = NULL, poppedOperand = NULL;
	int current = 0;

	if (c == '+' || c == '*' || c == '/' || c == '-') {
		newTreeNode = createTreeNode(c);
		for (current=0; current < 2; current++) {
			poppedOperand=pop(stackTop);
		
			if (current == 0)									//prva vrijednost koju poppamo ce bit desno dijete, a druga lijevo dijete jer kako se na stog stavlja na vrh onda ce u njemu lijevo dijete bit ispod desnog
				newTreeNode->rightChild = poppedOperand;

			else
				newTreeNode->leftChild = poppedOperand;

		}

		push(stackTop, newTreeNode);		// stavljamo ovaj cvor na stog zato sto ce on bit desna/lijeva grana sljedecem cvoru
	}


	else{

		if (c != '\n' && c!=" ") {
			newTreeNode = createTreeNode(c);
			push(stackTop, newTreeNode);
		}

		else
			return NULL;
	}

	return newTreeNode;
}

positionTreeNode createTreeNode(char c) {
	positionTreeNode newTreeNode = NULL;

	newTreeNode = malloc(sizeof(treeNode));

	newTreeNode->el = c;
	newTreeNode->rightChild = NULL;
	newTreeNode->leftChild = NULL;

	return newTreeNode;
}

positionTreeNode pop(positionStackNode stackTop) {
	positionTreeNode poppedOperand = NULL;
	positionStackNode toDel = stackTop->next;

	if (toDel == NULL) {
		printf("\nNothing to pop, stack empty!\n");
		return NULL;
	}

	poppedOperand =toDel->treeLeaf;

	stackTop->next = toDel->next;

	free(toDel);

	return poppedOperand;
}


int push(positionStackNode top, positionTreeNode newTreeNode){
	positionStackNode newStackNode = NULL;

	newStackNode = malloc(sizeof(stackNode));

	newStackNode->treeLeaf = newTreeNode;
	newStackNode->next = NULL;

	newStackNode->next = top->next;
	top->next = newStackNode;

	return EXIT_SUCCESS;
}


int printTree(positionTreeNode root) {

	if (root == NULL) {
		printf("\nTree is empty!\n");
		return EXIT_FAILURE;
	}
	
	if (root->leftChild== NULL)
		printf(" %c ", root->el);

	else {
		printf("(");
		printTree(root->leftChild);
		printf(" %c ", root->el);
		printTree(root->rightChild);
		printf(")");
	}

	return EXIT_SUCCESS;
}

