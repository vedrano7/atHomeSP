
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define MAX 99

void ispis(int br) {
	if (br >= 10)
		ispis(br / 10);
	
	printf("\n%d\n", br % 10);
}

void main() {
	int x = 4793;

	ispis(4793);


}