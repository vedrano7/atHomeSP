#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>

typedef struct TreeNode* position;
typedef struct TreeNode {
	int el;
	position leftChild, rightChild;
}treeNode;


int menu(position root);
position createEmpty(position root);
position findMin(position root);
position findMax(position root);
position find(position root,int wantedEl);
position insert(position root, int newEl);
position createNode(int newEl);
position delete(position root, int elToDel);
int inorderPrint(position root);
int postorderPrint(position root);
int preorderPrint(position root);
int levelorderPrint(position root);


int main() {
	//treeNode treeHead = { 0,NULL,NULL };		//mozemo i bez head-a her nam je redudantan
	position root = NULL;
	int rootVal = 0;
	
	printf("\nUnesite vrijednost korijena: ");		
	scanf("%d", &rootVal);

	root = insert(root, rootVal);

	//treeHead.leftChild = &root;

	menu(root);

	return EXIT_SUCCESS;
}

int menu(position root) {
	char pick = '\0';
	int el = 0;
	position result = NULL;

	while (1) {
		printf("\nUpisite '1' za kreirati prazno stablo, '2' za naci minimalan element u stablu, '3' za naci maksimalan element u stablu, '4' za naci odreden element u stablu, '5' za dodati novi element u stablo, '6' za izbrisati element iz stabla, '7' za ispisati stablo u inorder obliku, '8' za ispisati stablo u postorder obliku, '9' za ispisati stablo u preorder obliku,'a' za ispisati stablo u levelorder obliku a 0 za izaci iz programa\n");
		scanf(" %c", &pick);

		switch (pick) {
			case '0':

				printf("\nKraj programa!\n");

				break;

			case '1':
				result = createEmpty(root);

				if (result == NULL) {
					printf("\nUspjesno kreirano prazno stablo!\n");
					root = NULL;									//ovo dodajemo kako root ne bi bio neka trash vrijednost
						
					printf("Unesite novu vrijednost korijena: ");
					scanf("%d", &el);

					root = insert(root, el);
				}

				else
					printf("\nNespjesno kreiranje praznog stabla!\n");

				continue;

			case '2':
				result=findMin(root);

				if (result != NULL)
					printf("\nNajmanji element u stablu je: %d\n", result->el);

				else
					printf("\nNeuspjelo pronalazanje minimalnog elementa!\n");

				continue;

			case '3':
				result = findMax(root);

				if (result != NULL)
					printf("\nNajveci element u stablu je: %d\n", result->el);

				else
					printf("\nNeuspjelo pronalazanje maksimalnog elementa!\n");

				continue;

			case '4':

				printf("\nUnesite vrijednost elementa kojeg zelite pronaci u stablu: ");
				scanf("%d", &el);
				
				result = find(root,el);

				if (result != NULL)
					printf("\Element %d se nalazi na adresi %p\n", el,result);

				else
					printf("\nNeuspjelo pronalazanje elementa %d!\n",el);

				continue;

			case '5':

				//kod u slucaju da BST (binary search tree) ne dopusta duple vrijednosti u stablu

				
				printf("\nUnesite vrijednost elementa kojeg zelite dodati u stablo: ");
				scanf("%d", &el);

				result = find(root, el);

				if (result != NULL)
					printf("\nElement %d se vec nalazi u stablu!\n", el);

				else
					root=insert(root, el);
				

				//kod u slucaju da BTS dopusta duple vrijednosti u stablu

				/*printf("\nUnesite vrijednost elementa kojeg zelite dodati u stablo: ");
				scanf("%d", &el);

				root=insert(root, el);*/
				
				continue;

			case '6':

				printf("\nUnesite vrijednost elementa kojeg zelite izbrisati iz stabla: ");
				scanf("%d", &el);

				root=delete(root, el);		//moramo povratnu vrijednost delete funckije pridijelit root-u jer ako izbrisemo root na levelu 0 onda ce se promjena adrese na koju root pokazuje promijenit samo u lokalnoj kopiji root-a ali ne i na pravi root u main-u

				continue;

			case '7':

				//u ovom kodu name ne treba provjera je li stablo prazno jer ce uvijek imat bar root cvor tkd nikad nece bit prazno

				inorderPrint(root);

				continue;


			case '8':

				//u ovom kodu name ne treba provjera je li stablo prazno jer ce uvijek imat bar root cvor tkd nikad nece bit prazno

				postorderPrint(root);

				continue;

			case '9':

				//u ovom kodu name ne treba provjera je li stablo prazno jer ce uvijek imat bar root cvor tkd nikad nece bit prazno

				preorderPrint(root);

				continue;
			
			case 'a':

				//u ovom kodu name ne treba provjera je li stablo prazno jer ce uvijek imat bar root cvor tkd nikad nece bit prazno

				levelorderPrint(root);

				continue;

			default:

				printf("\nKrivi unos!!\n");

				continue;
		}
	
		break;
	}

	return EXIT_SUCCESS;
}

position createEmpty(position root) {

	if (root == NULL)
		return NULL;

	
	createEmpty(root->leftChild);
	createEmpty(root->rightChild);

	free(root);
	
	return NULL;
}

position findMin(position root) {

	if (root == NULL)
		return NULL;

	else {

		if (root->leftChild == NULL)
			return root;
		else
			return findMin(root->leftChild);
	}
}

position findMax(position root) {

	if (root == NULL)
		return NULL;

	else {

		if (root->rightChild == NULL)
			return root;
		else
			return findMin(root->rightChild);
	}
}

position find(position root, int wantedEl) {
	if (root == NULL)
		return NULL;

	else if (wantedEl < root->el)
		return find(root->leftChild, wantedEl);

	else if (wantedEl > root->el)
		return find(root->rightChild, wantedEl);

	return root;
}

position insert(position root, int newEl) {		

	if (root == NULL)
		return createNode(newEl);

	//kod u slucaju da BTS ne dopusta duple vrijednosti u stablu

	else if (newEl < root->el)							
		root->leftChild = insert(root->leftChild, newEl);

	else if (newEl > root->el)									 
		root->rightChild = insert(root->rightChild, newEl);		

	//kod u slucaju da BTS dopusta duple vrijednosti u stablu (1. opcija)

	/*else if (newEl <= root->el)
		root->leftChild = insert(root->leftChild, newEl);

	else if (newEl > root->el)
		root->rightChild = insert(root->rightChild, newEl);*/

	//kod u slucaju da bts dopusta duple vrijednosti u stablu (2.opcija)

	/*else if (newEl < root->el)
		root->leftChild = insert(root->leftChild, newEl);

	else if (newEl >= root->el)
		root->rightChild = insert(root->rightChild, newEl);*/

	return root;
}

position createNode(int newEl) {
	position newNode = NULL;

	newNode = malloc(sizeof(treeNode));

	if (!newNode) {
		printf("\nNeuspjela alokacija memorije za newNode!\n");
		return NULL;
	}

	newNode->el = newEl;
	newNode->leftChild = NULL;
	newNode->rightChild= NULL;

	return newNode;
}

position delete(position root, int elToDel) {	//moramo napisat kod za scenarij brisanja cvora bez djece, s jedim djeteto i s dvoje djece
	position temp;

	//ovaj dio je za pronac element kojeg zelimo izbrisat i za pobrinit se da su veze ocuvane
	
	if (root == NULL) 
		printf("\nElement kojeg zelite obrisati se ne nalazi u stablu!\n");
	

	else if (elToDel < root->el)
		root->leftChild=delete(root->leftChild, elToDel);		//ovo radimo kako bi rekurzivno odrzali veze izmedu cvorova nakon brisanja trazenog cvora

	else if(elToDel>root->el)
		root->rightChild = delete(root->rightChild, elToDel);	//ovo radimo kako bi rekurzivno odrzali veze izmedu cvorova nakon brisanja trazenog cvora

	//sad smo ga nasli i idemo provjerit koliko djece ima prije nego sto ga izbrisemo

	else if (root->leftChild != NULL && root->rightChild != NULL) {				//ako je ovo ispunjeno znaci da ima dvoje djece

		//1.opcija
		
		//trazimo najmanji element u desnom podstablu ciju vrijednost pridjeljujemo sadasnjem root-u

		temp = root->rightChild;

		while (temp->leftChild != NULL)
			temp = temp->leftChild;

		root->el = temp->el;

		//brisemo duplikat da stablo bude tocno

		root->rightChild = delete(root->rightChild, temp->el);

		//2.opcija
		/*
		//trazimo najveci element u lijevom podstablu ciju vrijednost pridjeljujemo sadasnjem root-u

		temp = root->leftChild;

		while (temp->rightChild != NULL)
			temp = temp->rightChild;

		root->el = temp->el;

		//brisemo duplikat da stablo bude tocno

		root->leftChild = delete(root->leftChild, temp->el);*/

	}

	else {			//ako je ovo znaci da nema djece ili ima jedno dijete
	
		temp = root;

		if (root->leftChild != NULL)
			root = root->leftChild;		//ova promjena adrese na koju pointer pokazuje ce biti ucinjena samo lokalno (globalne su samo promjene vrijednosti na adresi na koju pointeri pokazuju)

		else
			root = root->rightChild;	//ova promjena adrese na koju pointer pokazuje ce biti ucinjena samo lokalno (globalne su samo promjene vrijednosti na adresi na koju pointeri pokazuju)

		free(temp);
	}

	return root;
}

int inorderPrint(position root) {

	if (root != NULL) {
		inorderPrint(root->leftChild);
		printf("%d ", root->el);
		inorderPrint(root->rightChild);
	}

	return EXIT_SUCCESS;
}

int postorderPrint(position root) {

	if (root != NULL) {
		postorderPrint(root->leftChild);
		postorderPrint(root->rightChild);
		printf("%d ", root->el);

	}

	return EXIT_SUCCESS;
}

int preorderPrint(position root) {

	if (root != NULL) {
		printf("%d ", root->el);
		preorderPrint(root->leftChild);
		preorderPrint(root->rightChild);

	}

	return EXIT_SUCCESS;
}

int levelorderPrint(position root) {
	position current = NULL, queue[100] = { NULL };		//za levelorder ispis nam treba red (odi cemo ga realizirat pomocu niza od 100 clanova jer je to velika velicina pa bi nam svi clanovi trebali stat)
	int front = 0, rear = 0;

	queue[rear] = root;		//dodaje se na kraj jer je to princip reda - FIFO ,ali kako je to prvo dodavanje u red front i rear su na istoj poziciji u nizu tkd oboje sadrze root

	while (front <= rear) {
	
		current = queue[front];		

		printf("%d ", current->el);

		if (current->leftChild != NULL)
			queue[++rear] = current->leftChild;
		
		if (current->rightChild != NULL)
			queue[++rear] = current->rightChild;

		front++;				//kao da izbacujemo ovaj root sad iz reda
	}

	return EXIT_SUCCESS;
}