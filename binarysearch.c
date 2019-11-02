#include<stdio.h>

int searchSection(int values[], int size, int value, int left, int right) {
	
	int l = left;
	int r = right;
	int middle = (left + right) / 2;

	if (size < 1) {
		return -1;
	}

	if (values[middle] == value) {
		printf("Found value!!\n");
		return 0;
	}

	if (value < values[middle]) {
		// Search in left half
		r = middle - 1;
		searchSection(values, r - l + 1, value, l, r);
	}else if (value > values[middle]) {
		//Search in right half
		l = middle + 1;
		searchSection(values, r - l + 1, value, l, r);
	}

	return;
}

void main(int argc, char* argv []) {
	int values[] = {1, 3, 5, 6, 8, 9, 48, 79, 82};
	int size = sizeof(values)/sizeof(values[0]);
	int value = atoi(argv[1]);
	int left = 0;
	int right = size - 1;

	// Binary search algorithm
	int result = searchSection(values, size, value, left, right);
	printf("%d\n", result);
}