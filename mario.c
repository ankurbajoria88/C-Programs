#include<stdio.h>

int main(void) {
	int height;
	printf("Please enter the height\n");
	scanf("%d", &height);

	for (int i=1; i <= height; i++) {
		for (int k=height - i + 1; k >=0; k--) {
			printf(" ");
		}
		for (int j=height; j >= height - i + 1; j--) {
			printf("#");
		}
		printf("  ");
		for (int j=height; j >= height - i + 1; j--) {
			printf("#");
		}
		printf("\n");
	}
	return 0;
}