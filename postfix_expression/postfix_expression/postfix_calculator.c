#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>
#define FAILED_MEMORY_ALLOCATION (-1)
#define MAX_EQUATION_SIZE (100)

//"infix to postfix stack element"

typedef struct iftPfStackEl* positionIftPf;

typedef struct iftPfStackEl {		
	char el;
	positionIftPf next;

}IftPfStackEl;


//"postfix stack element"

typedef struct pfStackEl* positionP;

typedef struct pfStackEl {		
	int el;
	positionP next;

}PfStackEl;

int infixToPostfix(char* infixEq,char* postfixEq, positionIftPf headPtF);	//pretvaranje infix izraza u postfix izraz

int postfixCalculator(char* postfixEq, positionP headP);					//racunanje postfix izraza

int pushIftPf(char newEl, positionIftPf headPtF);
int popIftPf(positionIftPf headPtF);

int pushP(int newEl, positionP headP);
int popP(positionP headP);

int main() {
	IftPfStackEl headIftPF = { '\0',NULL };
	PfStackEl headP= {0,NULL };
	char infixEquation[MAX_EQUATION_SIZE] = { '\0' }, postfixEq[MAX_EQUATION_SIZE] = { '\0' };

	printf("\nUnesite zeljeni matematicki izraz:  ");
	fgets(infixEquation, MAX_EQUATION_SIZE, stdin);

	infixToPostfix(infixEquation,postfixEq,&headIftPF);

	printf("\n");
	puts(postfixEq);
	printf("\n");

	postfixCalculator(postfixEq, &headP);
	
	return EXIT_SUCCESS;
}

infixToPostfix(char* infixEq, char* postfixEq, positionIftPf headIftPF) {
	char temp = '\0';
	int numBytes = 0, status = 0, i = 0;
	positionIftPf current = headIftPF;

	while (strlen(infixEq) > 0) {

		sscanf(infixEq, "%c%n", &temp, &numBytes);

		if (temp == '(')
			pushIftPf(temp, headIftPF);

		else if (temp == '+') {

			status = 0;

			while (1) {

				current = headIftPF;

				while (current->next != NULL)
					current = current->next;

				if (headIftPF->next != NULL) {
					switch (current->el) {

						case '+':
							postfixEq[i] = current->el;;
							i++;

							popIftPf(headIftPF);

							status = 0;

							break;

						case '-':
							postfixEq[i] = current->el;;
							i++;

							popIftPf(headIftPF);

							status = 0;

							break;

						case '*':
							postfixEq[i] = current->el;;
							i++;

							popIftPf(headIftPF);

							status = 0;

							break;

						case '/':
							postfixEq[i] = current->el;;
							i++;

							popIftPf(headIftPF);

							status = 0;

							break;

						case '(':
							pushIftPf(temp, headIftPF);
							status = 1;

							break;
					}
				}

				else {
					pushIftPf(temp, headIftPF);

					break;

				}

				if (status == 1)
					break;
			}

		}

		else if (temp == '-') {

			status = 0;

			while (1) {

				current = headIftPF;

				while (current->next != NULL)
					current = current->next;

				if (headIftPF->next != NULL) {
					switch (current->el) {

						case '-':
							postfixEq[i] = current->el;;
							i++;

							popIftPf(headIftPF);

							status = 0;

							break;

						case '+':
							postfixEq[i] = current->el;;
							i++;

							popIftPf(headIftPF);

							status = 0;

							break;

						case '*':
							postfixEq[i] = current->el;;
							i++;

							popIftPf(headIftPF);

							status = 0;

							break;

						case '/':
							postfixEq[i] = current->el;;
							i++;

							popIftPf(headIftPF);

							status = 0;
							break;

						case '(':
							pushIftPf(temp, headIftPF);
							status = 1;

							break;
					}
				}


				else {
					pushIftPf(temp, headIftPF);

					break;

				}

				if (status == 1)
					break;
			}

		}

		else if (temp == '*') {

			status = 0;

			while (1) {

				current = headIftPF;

				while (current->next != NULL)
					current = current->next;

				if (headIftPF->next != NULL) {
					switch (current->el) {

						case '*':
							postfixEq[i] = current->el;;
							i++;

							popIftPf(headIftPF);

							status = 0;
							
							break;

						case '/':
							postfixEq[i] = current->el;;
							i++;

							popIftPf(headIftPF);

							status = 0;

							break;

						case '+':
							pushIftPf(temp, headIftPF);
							status = 1;

							break;

						case '-':
							pushIftPf(temp, headIftPF);
							status = 1;

							break;

						case '(':
							pushIftPf(temp, headIftPF);
							status = 1;

							break;
					}
				}

				else {
					pushIftPf(temp, headIftPF);

					break;
				}


				if (status == 1)
					break;
			}

		}


		else if (temp == '/') {

			status = 0;

			while (1) {

				current = headIftPF;

				while (current->next != NULL)
					current = current->next;

				if (headIftPF->next != NULL) {
					switch (current->el) {

						case '/':
							postfixEq[i] = current->el;;
							i++;

							popIftPf(headIftPF);

							status = 0;

							break;

						case '*':
							postfixEq[i] = current->el;;
							i++;

							popIftPf(headIftPF);

							status = 0;

							break;

						case '+':
							pushIftPf(temp, headIftPF);
							status = 1;

							break;

						case '-':
							pushIftPf(temp, headIftPF);
							status = 1;

							break;

						case '(':
							pushIftPf(temp, headIftPF);
							status = 1;

							break;
					}
				}

				else {
					pushIftPf(temp, headIftPF);

					break;
				}

				if (status == 1)
					break;
			}

		}

		else if (temp == ')') {

			status = 0;

			while (1) {

				current = headIftPF;

				while (current->next != NULL)
					current = current->next;

				if (current->el != '(') {

					postfixEq[i] = current->el;
					popIftPf(headIftPF);
					i++;
				}

				else {

					popIftPf(headIftPF);
					status = 1;

					break;
				}

				if (status == 1)
					break;

				current = headIftPF;
			}
		}

		else {

			if (temp == '\n')
				break;

			postfixEq[i] = temp;
			i++;
		}

		infixEq += numBytes;


	}

		if (headIftPF->next != NULL) {

			while (headIftPF->next != NULL) {

				current = headIftPF;

				while (current->next != NULL)
					current = current->next;

				postfixEq[i] = current->el;
				i++;

				popIftPf(headIftPF);
			}
		}

		return EXIT_SUCCESS;
}

int pushIftPf(char newEl, positionIftPf headIftPF) {
	positionIftPf newIftPfStackEl = NULL, current = headIftPF;

	newIftPfStackEl = malloc(sizeof(IftPfStackEl));

	if (!newIftPfStackEl) {
		printf("\nUnable to allocate memory for newPFfStackEl\n");
		return FAILED_MEMORY_ALLOCATION;
	}

	newIftPfStackEl->el = newEl;

	while (current->next != NULL)
		current = current->next;

	newIftPfStackEl->next = current->next;
	current->next = newIftPfStackEl;


	return EXIT_SUCCESS;
}

int popIftPf(positionIftPf headIftPF) {
	positionIftPf current = headIftPF, temp = NULL;


	while (current->next->next != NULL)
		current = current->next;

	temp = current->next;
	current->next = temp->next;
	free(temp);

	return EXIT_SUCCESS;
}

int postfixCalculator(char* postfixEq, positionP headP) {
	char temp = '\0';
	int numBytes = 0, resultant = 0, counter = 0,number=0;
	positionP current = headP;

	while (strlen(postfixEq) > 0) {

		sscanf(postfixEq, "%c%n", &temp, &numBytes);

	
		if (isdigit(temp)!=0){		//provjerava je li char broj
			number = temp - 48;			//za dobit brojcanu vrijednost nekog broja zapisanog u charu najlakse mu je oduzet ASCII vrijednost nule, a to je 48

			pushP(number, headP);
		}

		else if (temp == '+') {

			resultant = 0;

			for (counter = 0; counter < 2; counter++) {

				current = headP;

				while (current->next != NULL)
					current = current->next;

				if (resultant == 0)
					resultant = current->el;
				
				else
					resultant += current->el;

				popP(headP);
			}

			pushP(resultant, headP);

		}


		else if (temp == '-') {

			resultant = 0;

			for (counter = 0; counter < 2; counter++) {

				current = headP;

				while (current->next != NULL)
					current = current->next;

				if (resultant == 0)
					resultant = current->el;

				else
					resultant = current->el-resultant;	//moramo ovako jer oduzimanje nije komutativno!! (prvi je u stog stavljen onaj od kojeg se oduzima, a poslije njega onaj kojeg oduzimamo pa ih mi odi izvlacimo u obrnuton smjeru)

				popP(headP);

			}

			pushP(resultant, headP);

		}

		else if (temp == '*') {

			resultant = 0;

			for (counter = 0; counter < 2; counter++) {

				current = headP;

				while (current->next != NULL)
					current = current->next;

				if (resultant == 0)
					resultant = current->el;

				else
					resultant *= current->el;

				popP(headP);

			}

			pushP(resultant, headP);

		}

		else if (temp == '/') {

			resultant = 0;

			for (counter = 0; counter < 2; counter++) {

				current = headP;

				while (current->next != NULL)
					current = current->next;

				if (resultant == 0)
					resultant = current->el;

				else
					resultant = current->el/resultant;		//moramo ovako jer dijeljenje nije komutativno!! (prvi je u stog stavljen djeljenik, a poslije djelitelj pa ih mi odi izvlacimo u obrnuton smjeru)

				popP(headP);

			}

			pushP(resultant, headP);

		}
	

		postfixEq += numBytes;
	}

	printf("\nRezultat je: %d\n", headP->next->el);
	popP(headP);		//da ispraznimo stog do kraja
}

int pushP(int newEl, positionP headP) {
	positionP newPfStackEl = NULL, current = headP;

	newPfStackEl = malloc(sizeof(PfStackEl));

	if (!newPfStackEl) {
		printf("\nUnable to allocate memory for newPFfStackEl\n");
		return FAILED_MEMORY_ALLOCATION;
	}

	newPfStackEl->el = newEl;

	while (current->next != NULL)
		current = current->next;

	newPfStackEl->next = current->next;
	current->next = newPfStackEl;


	return EXIT_SUCCESS;
}

int popP(positionP headP) {
	positionP current = headP, temp = NULL;


	while (current->next->next != NULL)
		current = current->next;

	temp = current->next;
	current->next = temp->next;
	free(temp);

	return EXIT_SUCCESS;
}

