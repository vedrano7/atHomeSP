
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#define MAX 99


int main() {
	int n = 5;
	int X[5] = { 0,1,2,3,4 };
	int A = 1;

	int p = 0, k = n - 1, s;
	int br = 0;

	while (p < k && br == 0)
	{
		s = (p + k) / 2;
		if (A == X[s]) br = s;
		else if (A < X[s]) k = s - 1;
		else p = s + 1;

		printf("\n%d %d\n", s, br);
	}

	if (br == 0)
		printf("\nbroj il nije naden il je prvi u nizu\n");
	else
		printf("\nbroj je na %d. mistu", br+1);

	return 0;
}