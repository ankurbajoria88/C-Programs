#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int printCaps(char data) {
	if (data >= 'a' && data <= 'z') {
		return (int) data - 32;
	} else {
		return (int) data;
	}
}

int main(int argc, char* argv[]) {
	char name[20];
	printf("Please enter a name\n");
	//scanf("%c", &name);
	gets(name);

	if ((name[0] >= 'a' && name[0] <= 'z') || (name[0] >= 'A' && name[0] <= 'Z')) {
		printf("%c", (char) printCaps(name[0]));
	}

	for (int i=0, n = strlen(name); i < n; i++) {
		if (name[i] == ' ' && name[i + 1] != ' ') {
			printf("%c", (char) printCaps(name[i + 1]));
		}
	}
	printf("\n");

	return 0;
}