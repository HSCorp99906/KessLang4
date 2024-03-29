#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include "../include/Token.h"
#include "../include/Lexer.h"
#include "../include/TokenDump.h"
#include "../include/Parser.h"


int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("Usage: %s <filename>\n", argv[0]);
		return 0;
	}

	if (access(argv[1], F_OK) != 0) {
		printf("Cannot access file.\n");
		return 0;
	}

	size_t lineBufSize = 5;
	char* lineBuf = (char*)malloc(sizeof(char) * lineBufSize);

	FILE* fp = fopen(argv[1], "r");

	struct Lexer lexer = {
		.lineNum = 1,
		.error = false,
	};

	toklist_t toklist;

	init_tokenlist(&toklist);

	while (getline(&lineBuf, &lineBufSize, fp) != -1 && !(lexer.error)) {
		tokenize(&toklist, &lexer, lineBuf);
		++lexer.lineNum;
	}

	struct Parser parser = {
		.tokenList = toklist,
		.colNum = 0,
		.lineNum = 1,
	};

	if (lexer.error) {
		fclose(fp);
		destroy_tokenlist(&toklist);
		return -1;
	}


	#ifdef DEBUG
	dump_tokens(toklist);
	#endif

	int nodelistSize = 0;
	
	printf("\n");
	parseAndRun(&parser, &nodelistSize); 

	#ifdef DEBUG
	printf("%d\n", nodelistSize);
	#endif

	fclose(fp);
	destroy_tokenlist(&toklist);
}
