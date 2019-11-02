#include<stdio.h>
#include<string.h>

char shiftChar(char c, int modKey) {
	char* upAlpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char* lowAlpha = "abcdefghijklmnopqrstuvwxyz";

	if (isalpha(c)) {
		if (islower(c)) {
			return lowAlpha[((strchr(lowAlpha, c) - lowAlpha + modKey) % 26)];
		}else if (isupper(c)){
			return upAlpha[((strchr(upAlpha, c) - upAlpha + modKey) % 26)];
		}
	}else {
		return c;
	}
}


int main(int argc, char* argv[]) {
	int key;
	char cipher[50];
	char output[50];

	printf("Enter the cipher text\n");
	gets(cipher);

	do {
	printf("Please enter a number for the key\n");
	scanf("%d", &key);
	}while (key < 1);

	int len = strlen(cipher);

	for (int i = 0; i < len; i++) {
		output[i] = shiftChar(cipher[i], key);
	}

	printf("The output is: %s\n", output);

	return 0;
}