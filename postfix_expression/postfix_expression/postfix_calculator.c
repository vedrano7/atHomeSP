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

int infixToPostfix(char* infixEq,char* postfixEq, positionIftPf topPtF);	//pretvaranje infix izraza u postfix izraz

int postfixCalculator(char* postfixEq, positionP topP);					//racunanje postfix izraza

int pushIftPf(char newEl, positionIftPf topPtF);
int popIftPf(positionIftPf topPtF);

int pushP(int newEl, positionP topP);
int popP(positionP topP);

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

infixToPostfix(char* infixEq, char* postfixEq, positionIftPf topIftPF) {
	char temp = '\0';
	int numBytes = 0, i = 0;

	while (strlen(infixEq) > 0) {

		sscanf(infixEq, "%c%n", &temp, &numBytes);

		if (temp == '(')
			pushIftPf(temp, topIftPF);

		else if (temp == '+') {

			while (1) {

				if (topIftPF->next != NULL) {
					switch (topIftPF->next->el) {

						case '+':
							postfixEq[i++] = topIftPF->next->el;

							popIftPf(topIftPF);

							continue;

						case '-':
							postfixEq[i++] = topIftPF->next->el;

							popIftPf(topIftPF);

							continue;

						case '*':
							postfixEq[i++] = topIftPF->next->el;

							popIftPf(topIftPF);

							continue;

						case '/':
							postfixEq[i++] = topIftPF->next->el;

							popIftPf(topIftPF);

							continue;

						case '(':
							pushIftPf(temp, topIftPF);

							break;
					}
				}

				else {
					pushIftPf(temp, topIftPF);

					break;
				}

				
				break;
			}

		}

		else if (temp == '-') {

			while (1) {

				if (topIftPF->next != NULL) {
					switch (topIftPF->next->el) {

						case '-':
							postfixEq[i++] = topIftPF->next->el;

							popIftPf(topIftPF);

							continue;

						case '+':
							postfixEq[i++] = topIftPF->next->el;

							popIftPf(topIftPF);

							continue;

						case '*':
							postfixEq[i++] = topIftPF->next->el;

							popIftPf(topIftPF);

							continue;

						case '/':
							postfixEq[i++] = topIftPF->next->el;

							popIftPf(topIftPF);

							continue;

						case '(':
							pushIftPf(temp, topIftPF);

							break;
						}
				}

				else {
					pushIftPf(temp, topIftPF);

					break;
				}


				break;
			}
		}


		else if (temp == '*') {

			while (1) {

				if (topIftPF->next != NULL) {
					switch (topIftPF->next->el) {

						case '*':
							postfixEq[i++] = topIftPF->next->el;

							popIftPf(topIftPF);

							continue;

						case '/':
							postfixEq[i++] = topIftPF->next->el;

							popIftPf(topIftPF);

							continue;

						case '-':
							postfixEq[i++] = topIftPF->next->el;

							pushIftPf(temp, topIftPF);

							break;

						case '+':
							postfixEq[i++] = topIftPF->next->el;

							pushIftPf(temp, topIftPF);

							break;

						case '(':
							pushIftPf(temp, topIftPF);

							break;
					}
				}

				else {
					pushIftPf(temp, topIftPF);

					break;
				}


				break;

			}
		}


		else if (temp == '/') {

			while (1) {

				if (topIftPF->next != NULL) {
					switch (topIftPF->next->el) {

						case '/':
							postfixEq[i++] = topIftPF->next->el;

							popIftPf(topIftPF);

							continue;

						case '*':
							postfixEq[i++] = topIftPF->next->el;

							popIftPf(topIftPF);

							continue;

						case '-':
							postfixEq[i++] = topIftPF->next->el;

							pushIftPf(temp, topIftPF);

							break;

						case '+':
							postfixEq[i++] = topIftPF->next->el;

							pushIftPf(temp, topIftPF);

							break;

						case '(':
							pushIftPf(temp, topIftPF);

							break;
					}
				}

				else {
					pushIftPf(temp, topIftPF);

					break;
				}


				break;

			}
		}

		else if (temp == ')') {

			while (1) {

				if (topIftPF->next->el != '(') {

					postfixEq[i++] = topIftPF->next->el;

					popIftPf(topIftPF);
				}

				else {

					popIftPf(topIftPF);

					break;
				}

			}
		}

		else {		//ovo je slucaj kad skeniramo brojeve

			if (temp != '\n')		//ovo stavljamo jer nezelimo ubacit znak za novi red koji je osta pri unosu infix niza s tipkovnice u novi postfix niz
				postfixEq[i++] = temp;
		}

		infixEq += numBytes;


	}

	if (topIftPF->next!= NULL) {		//kad dodemo do kraja infix izraza trebamo izbacit sve operande koji su ostali u stogu

		while (topIftPF->next != NULL) {

			postfixEq[i++] = topIftPF->next->el;

			popIftPf(topIftPF);
		}
	}

	return EXIT_SUCCESS;
}

int pushIftPf(char newEl, positionIftPf topIftPF) {
	positionIftPf newIftPfStackEl = NULL;

	newIftPfStackEl = malloc(sizeof(IftPfStackEl));

	if (!newIftPfStackEl) {
		printf("\nUnable to allocate memory for newPFfStackEl\n");
		return FAILED_MEMORY_ALLOCATION;
	}

	newIftPfStackEl->el = newEl;

	newIftPfStackEl->next = topIftPF->next;
	topIftPF->next = newIftPfStackEl;

	return EXIT_SUCCESS;
}

int popIftPf(positionIftPf topIftPF) {
	positionIftPf toDel = NULL;
	int poppedEl = 0;

	toDel = topIftPF->next;
	topIftPF->next = toDel->next;

	free(toDel);

	return poppedEl;
}

int postfixCalculator(char* postfixEq, positionP topP) {
	char temp = '\0';
	int numBytes = 0, resultant = 0, counter = 0,number=0;

	while (strlen(postfixEq) > 0) {

		sscanf(postfixEq, "%c%n", &temp, &numBytes);

	
		if (isdigit(temp)!=0){		//provjerava je li char broj
			number = temp - 48;			//za dobit brojcanu vrijednost nekog broja zapisanog u charu najlakse mu je oduzet ASCII vrijednost nule, a to je 48
											//umjesto ovog bolje koristit onu verziju sa provjeravanjen povratne vrijednosti sscanf koju iman na lab4 
			pushP(number, topP);
		}

		else if (temp == '+') {

			resultant = 0;

			for (counter = 0; counter < 2; counter++) {

				if (resultant == 0)
					resultant = topP->next->el;
				
				else
					resultant += topP->next->el;

				popP(topP);
			}

			pushP(resultant, topP);

		}


		else if (temp == '-') {

			resultant = 0;

			for (counter = 0; counter < 2; counter++) {

				if (resultant == 0)
					resultant = topP->next->el;

				else
					resultant = topP->next->el - resultant;	//moramo ovako jer oduzimanje nije komutativno!! (prvi je u stog stavljen onaj od kojeg se oduzima, a poslije njega onaj kojeg oduzimamo pa ih mi odi izvlacimo u obrnuton smjeru)

				popP(topP);

			}

			pushP(resultant, topP);

		}

		else if (temp == '*') {

			resultant = 0;

			for (counter = 0; counter < 2; counter++) {

				if (resultant == 0)
					resultant = topP->next->el;

				else
					resultant *= topP->next->el;

				popP(topP);

			}

			pushP(resultant, topP);

		}

		else if (temp == '/') {

			resultant = 0;

			for (counter = 0; counter < 2; counter++) {

				if (resultant == 0)
					resultant = topP->next->el;

				else
					resultant = topP->next->el /resultant;		//moramo ovako jer dijeljenje nije komutativno!! (prvi je u stog stavljen djeljenik, a poslije djelitelj pa ih mi odi izvlacimo u obrnuton smjeru)

				popP(topP);

			}

			pushP(resultant, topP);

		}
	

		postfixEq += numBytes;
	}

	printf("\nRezultat je: %d\n", topP->next->el);
	popP(topP);		//da ispraznimo stog do kraja (jer je osta rezultat kao jedini clan stoga)
}

int pushP(int newEl, positionP topP) {
	positionP newPfStackEl = NULL;

	newPfStackEl = malloc(sizeof(PfStackEl));

	if (!newPfStackEl) {
		printf("\nUnable to allocate memory for newPFfStackEl\n");
		return FAILED_MEMORY_ALLOCATION;
	}

	newPfStackEl->el = newEl;

	newPfStackEl->next = topP->next;
	topP->next = newPfStackEl;


	return EXIT_SUCCESS;
}

int popP(positionP topP) {
	positionP toDel = NULL;
	int poppedEl = 0;


	toDel = topP->next;
	topP->next = toDel->next;

	free(toDel);

	return poppedEl;
}

