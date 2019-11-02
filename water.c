#include<stdio.h>

int main(void) {
	int minutes;
	do {
	printf("Please input the number of minutes you want to shower?\n");
	scanf("%d", &minutes);
	}while(minutes <= 0);

	printf("The number of bottles used will be %d", (192 * minutes) / 16);

	return 0;
}