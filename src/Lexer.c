#include "../include/Lexer.h"


//  Peek is mainly used for debugging.
char* peek(struct Lexer* lexer, int offset, char* line) {
	static char* peekedChar;

	peekedChar = strtok(line, " ");

	for (int col = 0; col < lexer->colNum + offset; ++col) {
		peekedChar = strtok(NULL, " ");
	}

	return peekedChar;
}


void advance(struct Lexer* lexer, char* line) {
	++lexer->colNum;
	lexer->curChar = line[lexer->colNum];
}


toklist_t tokenize(toklist_t* toklist, struct Lexer* lexer, char* line) {
	char linecpy[strlen(line)]; // Creates a copy of the line.

	strcpy(linecpy, line);

	strcat(linecpy, " EOL \0");
	linecpy[strlen(linecpy) - 6] = ' ';  // Removes newline.

	char* part = strtok(linecpy, " ");
	lexer->curPart = part;
	lexer->curChar = line[0];
	
	bool submitPrint = false;

	while (part != NULL) {
		bool digitFound = false;
		bool quoteFound = false;

		for (int i = 0; i < strlen(line); ++i) {
			switch (line[i]) {
				case '"':
					quoteFound = true;
					break;
			}
		}

		if (strcmp(part, "print") == 0) {
			add_element(toklist, create_token(part, T_PRINT, false));
		} else if (strcmp(part, "let") == 0) {
			add_element(toklist, create_token(part, T_VAR_DEC, false));
		} else if (strchr(part, '"') != NULL) {
			bool sq_reached = false;

			add_element(toklist, create_token("\"", T_QUOTE, false));
            
			size_t lineBufSize = 30;
			char* lineBuf = (char*)calloc(lineBufSize, sizeof(char));

			unsigned int lbidx = 0;

			for (int i = lexer->colNum; i < strlen(line); ++i) {
				// printf("%c", line[i]);
				lineBuf[lbidx] = line[i];
				++lbidx;
			}

			if (lineBuf[strlen(lineBuf) - 2] == '"' || lineBuf[strlen(lineBuf) - 2] == ';') {
				sq_reached = true;
				lineBuf[0] = 8;
				lineBuf[strlen(lineBuf) - 3] = '\0';
			}

			char finalLine[strlen(lineBuf)];
			strcpy(finalLine, lineBuf);
			free(lineBuf);

			if (!(sq_reached)) {
				printf("MissingEndOfStringError: Missing end quote.\n");
				lexer->error = true;
				break;
			}
			
			if (!(submitPrint)) {
				submitPrint = true;
				add_element(toklist, create_token(finalLine, T_STR, false));
			}
		}

		for (int i = 0; i < strlen(part); ++i) {
			switch (part[i]) {
				case '0':
				case '1':
				case '2':
				case '3':
				case '4':
				case '5':
				case '6':
				case '7':
				case '8':
				case '9':
					add_element(toklist, create_token(&part[i], T_INT, true));
					break;
			}
		}
	
		lexer->colNum += strlen(part) + 1;
		part = strtok(NULL, " ");
	}
}
