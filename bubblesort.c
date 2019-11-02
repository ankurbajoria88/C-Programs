#include<stdio.h>

void swap(int idx1, int idx2, int values[]) {
    int tmp = values[idx1];
    values[idx1] = values[idx2];
    values[idx2] = tmp;
    
}

void main(int argc, char* argv[]) {
	int values[] = {9, 8, 7, 0, 6, 20, 5, 4, 3, 2, 1};
	int size = sizeof(values)/sizeof(values[0]);

	for (int a = 0; a < size; a++) {
   		for (int i = 0; i < size; i++) {
   			if (i != size - 1) {
   				int j = i + 1;
       			if (values[j] < values[i]) {
       				swap(i, j, values);
       			}
       		}
    	}
	}

    for (int i = 0; i < size; i++) {
        printf("Sorted array is: %d \n", values[i]);
    }
    
    return;	
}