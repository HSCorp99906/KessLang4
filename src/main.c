#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("Usage: %s <filename>\n", argv[0]);
		return 0;
	}

	if (access(argv[1], F_OK) != 0) {
		printf("Cannot access file.\n");
		return 1;
	}
	
	size_t lineBufSize = 5;
	char* lineBuf = (char*)malloc(sizeof(char) * lineBufSize);

	FILE* fp = fopen(argv[1], "r");

	while (getline(&lineBuf, &lineBufSize, fp) != -1) {
		printf("%s", lineBuf); // Just a test for now.
	}

	fclose(fp);
}
