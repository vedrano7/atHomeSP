#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (50)
#define MAX_LENGTH (1024)

void ispisBroja(int broj) {
	if (broj >= 10)
		ispisBroja(broj / 10);

	printf(" %d", broj % 10);
}
int main() {

	ispisBroja(4793);

	return EXIT_SUCCESS;
}
