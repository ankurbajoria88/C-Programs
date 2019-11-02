#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char shiftChar(char c, char key) {
	char* upAlpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char* lowAlpha = "abcdefghijklmnopqrstuvwxyz";
	int idxC, idxKey;

	idxKey = strchr(lowAlpha, tolower(key)) - lowAlpha;

	if (islower(c)) {
		idxC = strchr(lowAlpha, c) - lowAlpha;
		return lowAlpha[(idxC + idxKey) % 26];
	}else if (isupper(c)) {
		idxC = strchr(upAlpha, c) - upAlpha;
		return upAlpha[(idxC + idxKey) % 26];
	}
}


int main(int argc, char* argv[]) {
	char cipher[50];
	char output[50];

	printf("Enter the cipher text\n");
	fgets(cipher, sizeof(cipher), stdin);

	char* key = argv[1];

	int len = strlen(cipher);
	int len2 = strlen(key);
	int idx = 0;

	for (int i = 0; i < len; i++) {
		if (idx >= len2) {
			idx = 0;
		}
		if (isalpha(cipher[i])) {
			output[i] = shiftChar(cipher[i], key[idx]);
			idx ++;
		}else {
			output [i] = cipher[i];
		}
		printf("%c", output[i]);
	}

	printf("\n");

	return 0;
}