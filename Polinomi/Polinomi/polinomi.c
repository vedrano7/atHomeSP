﻿#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define maxPot 10

//Polinomi pomocu nizova

//typedef struct {
//	int nizKoef[maxPot + 1];
//	int maxKoristenaPot;
//
//}Polinom;
//
//void unos(Polinom* P);
//void ispis(Polinom P);
//void suma(Polinom P1, Polinom P2, Polinom* S);
//int produkt(Polinom P1, Polinom P2, Polinom* P);
//
//int main() {
//	Polinom A = { {0},0 }, B = { {0},0 }, C = { {0},0 }, D = { {0},0 };
//	int prodRes;
//
//	unos(&A);
//	unos(&B);
//
//	ispis(A);
//	ispis(B);
//
//	suma(A, B, &C);
//
//	ispis(C);
//
//	prodRes=produkt(A, B,&D);
//	
//	if(!prodRes)
//		ispis(D);
//
//
//	return 0;
// }
//	
//
//
//void unos(Polinom* P) {
//	int i = 0;
//
//	printf("\nKoja je najveca potencija koja se koristi u ovom polinomu?\n");
//	scanf("%d", &P->maxKoristenaPot);
//
//	while (i <= P->maxKoristenaPot) {
//		printf("\nUnesi koeficijent clana s potencijom %d:\t", i);
//		scanf("%d", &P->nizKoef[i]);
//		i++;
//	}
//}
//
//void ispis(Polinom P) {
//	int i = 0;
//
//	printf("\nPolinom je: ");
//
//	while (i <= P.maxKoristenaPot) {
//
//		if (P.nizKoef[i] != 0) {
//
//			if (i == 0) {
//				printf("%d+", P.nizKoef[i]);
//				i++;
//			}
//
//			else if (i == 1) {
//				printf("%d*x+", P.nizKoef[i]);
//				i++;
//			}
//			else if (i == P.maxKoristenaPot) {
//				printf("%d*x^%d", P.nizKoef[i], i);
//				i++;
//			}
//
//			else {
////				printf("%d*x^%d+", P.nizKoef[i], i);
//				i++;
//			
//			}
//
//		}
//
//		else
//			i++;
//	}
//}
//
//void suma(Polinom P1, Polinom P2, Polinom* S) {
//	int i = 0;
//
//	(P1.maxKoristenaPot > P2.maxKoristenaPot) ? (S->maxKoristenaPot = P1.maxKoristenaPot) : (S->maxKoristenaPot = P2.maxKoristenaPot);
//
//	while (i <= S->maxKoristenaPot) {
//		S->nizKoef[i] = P1.nizKoef[i] + P2.nizKoef[i];
//		i++;
//	}
//
//}
//
//int produkt(Polinom P1, Polinom P2, Polinom* P) {
//	int i = 0,j=0;
//
//	if ((P1.maxKoristenaPot + P2.maxKoristenaPot) > maxPot){
//		printf("\nPolinomi preveliki za mnozenje\n");
//		return 1;
//		}
//
//	else {
//
//		P->maxKoristenaPot = P1.maxKoristenaPot+P2.maxKoristenaPot;
//
//		for (i = 0; i <= P1.maxKoristenaPot; i++) {
//
//			if (P1.nizKoef[i] != 0) {
//
//				for (j = 0; j <= P2.maxKoristenaPot; j++) {
//
//					if (P2.nizKoef[j] != 0) {
//						
//						P->nizKoef[i + j] += P1.nizKoef[i] * P2.nizKoef[j];
//					}
//				}
//			}
//		}
//		
//	}
//
//	return 0;
//}


//Polinomi pomocu lista

typedef struct PolynomeElement* position;

typedef struct PolynomeElement {
	int coef;
	int exp;
	position next;
}
PolynomeElement;

int menu(position headA,position headB);
int printPolynome(position P);
int addElementToPolynome(position P, int exp, int coef);	//sortirani unosu polinom
int PolynomeSum(position P1, position P2);
int PolynomeProduct(position P1, position P2);


int main() {
	PolynomeElement headA = { 0,0,NULL };
	PolynomeElement headB = { 0,0,NULL };

	menu(&headA,&headB);

	return 0;
}

int menu(position headA,position headB) {
	char pick = '\0';
	int newCoef = 0, newExp = 0;

	while (1) {

		printf("\nZa dodati pribrojnik polinomu A upisite 1,za ispisati polinom  A stisnite 2, za dodati pribrojnik polinomu B upisite 3, za ispisati polinom  B stisnite 4, za ispisati sumu tih dvaju polinoma upisite 5, za ispisati produkt tih dvaju polinoma upisite 6 te za izaci iz programa upisite 0.\n");
		scanf(" %c", &pick);

		switch (pick) {

			case '1':

				printf("\nUnesite potenciju i koeficijent novog pribrojnika: \n");
				scanf("%d %d", &newExp, &newCoef);

				addElementToPolynome(headA,newExp,newCoef);

				break;

			case '2':
				printPolynome(headA->next);

				break;

			case '3':

				printf("\nUnesite potenciju i koeficijent novog pribrojnika: \n");
				scanf("%d %d", &newExp, &newCoef);

				addElementToPolynome(headB, newExp, newCoef);


				break;

			case '4':
				printPolynome(headB->next);


				break;

			case '5':
				PolynomeSum(headA->next, headB->next);

				break;

			case '6':
				PolynomeProduct(headA->next, headB->next);

				break;

			case '0':
				printf("\nKraj programa!\n");

				break;

			default:
				printf("\nKrivi unos!\n");

				break;
		}

		if (pick == '0')
			break;
	}


	return 0;
}

int printPolynome(position P) {

	printf("\n-----------");

	if (P == NULL)
		printf("Polinom nema elemenata!\n");

	else {

		printf("\nPolinom je: ");

		while (P != NULL) {

			if (P->next != NULL) {

				if(P->exp==0)
					printf("%d+", P->coef);

				else if(P->exp==1)
					printf("%dx+", P->coef);

				else
					printf("%dx^%d+", P->coef, P->exp);

				P = P->next;
			}

			else {

				if (P->exp == 0)
					printf("%d", P->coef);

				else if (P->exp == 1)
					printf("%dx+", P->coef);

				else
					printf("%dx^%d", P->coef, P->exp);

				P = P->next;
			}
		}

	}



	printf("\n-----------\n");

	return 0;
}

int addElementToPolynome(position P, int exp, int coef){
	position newElement = NULL;

	newElement = malloc(sizeof(PolynomeElement));

	if (!newElement) {
		printf("\Neuspjela alokacija memorije za newElement!\n");
		exit(-1);
	}

	newElement->coef = coef;
	newElement->exp = exp;

	while (P->next != NULL && newElement->exp > P->next->exp)
		P = P->next;


	if (P->next == NULL || newElement->exp < P->next->exp) {
		newElement->next = P->next;
		P->next = newElement;

	}

	else {
		P->next->coef += newElement->coef;		
		free(newElement);		//ovo radimo jer u ovom slucaju ne moramo dodavat novi element polinoma u listu nego samo nadodajemo na postojeci pa nam je newElement beskorisan
	}

	return 0;
}

int PolynomeSum(position P1, position P2) {
	/*position headS = NULL, temp = NULL;

	headS = malloc(sizeof(PolynomeElement));

	if (!headS) {
		printf("\Neuspjela alokacija memorije za headS!\n");
		exit(-1);
	}

	headS->next = NULL;

	while (P1 != NULL && P2 != NULL) {

		if (P1->exp == P2->exp) {
			addElementToPolynome(headS, P1->exp, P1->coef + P2->coef);
			P1 = P1->next;
			P2 = P2->next;
		}

		else if (P1->exp > P2->exp) {
			addElementToPolynome(headS, P2->exp, P2->coef);
			P2 = P2->next;
		}

		else {
			addElementToPolynome(headS, P1->exp, P1->coef);
			P1 = P1->next;
		}

	}

	if (P1 == NULL)
		temp = P2;

	else
		temp = P1;


	while (temp != NULL) {
		addElementToPolynome(headS, temp->exp, temp->coef);
		temp = temp->next;
	}

	printPolynome(headS->next);*/

	//vise programerski nacin za zbrojit Polynome

	position headS = NULL;

	headS = malloc(sizeof(PolynomeElement));

	if (!headS) {
		printf("\Neuspjela alokacija memorije za headS!\n");
		exit(-1);
	}

	headS->next = NULL;

	while (P1 != NULL) {
		addElementToPolynome(headS, P1->exp, P1->coef);
		P1 = P1->next;
	}

	while (P2 != NULL) {
		addElementToPolynome(headS, P2->exp, P2->coef);
		P2 = P2->next;
	}

	printPolynome(headS->next);

	return 0;
}

int PolynomeProduct(position P1, position P2) {
	position headPr = NULL,temp,refHeadP2=P2;

	headPr = malloc(sizeof(PolynomeElement));

	if (!headPr) {
		printf("\Neuspjela alokacija memorije za headPr!\n");
		exit(-1);
	}

	headPr->next = NULL;

	while (P1 != NULL) {

		while (P2 != NULL) {

			addElementToPolynome(headPr,P1->exp + P2->exp, P1->coef * P2->coef);

			P2 = P2->next;
		}

		P1 = P1->next;

		P2 = refHeadP2;
	}

	printPolynome(headPr->next);

	return 0;
}
