#include<stdio.h>

char main(void) {
	int number[16];
	printf("Please enter a valid credit card number.\n");
	scanf("%d", &number);

	//TODO: Add more logic for checking the numbers that the card starts with 
	for(int i=0; i <= 16; i++) {
		printf("%d\n", number[i]);
	}
}
