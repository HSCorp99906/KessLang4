#include "../include/Lexer.h"


//  Peek is mainly used for debugging.
char* peek(struct Lexer* lexer, int offset, char* line) {
	static char* peekedChar;

	peekedChar = strtok(line, " ");

	for (int col = 0; col < lexer -> colNum + offset; ++col) {
		peekedChar = strtok(NULL, " ");
	}

	return peekedChar;
}


void advance(struct Lexer* lexer, char* line) {
	++lexer -> colNum;
	lexer -> curChar = line[lexer -> colNum];
}


toklist_t tokenize(toklist_t* toklist, struct Lexer* lexer, char* line) {
	char linecpy[strlen(line)]; // Creates a copy of the line.

	strcpy(linecpy, line);
	lexer -> error = false;

	strcat(linecpy, " EOL \0");
	linecpy[strlen(linecpy) - 6] = ' ';  // Removes newline.

	char* part = strtok(linecpy, " ");
	bool scan = false;
	lexer -> curPart = part;
	lexer -> curChar = line[0];
	bool quote = false;

	while (part != NULL && !(lexer -> error)) {
		for (int i = 0; i < strlen(line); ++i) {
			switch (line[i]) {
				case 0:
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
				case 9:
					add_element(toklist, create_token(&line[i], T_INT, false));
					break;
				case ';':
					add_element(toklist, create_token(&line[i], T_END_STATEMENT, false));
					break;
				case '"':
					if (!(quote)) {
						quote = true;
					} else if (quote) {
						quote = false;
					}
					break;
				case ' ':
					break;
				case '\n':
					break;
				default:
					if (!(quote) && isalpha(line[i]) == 0) {
						if (!(lexer -> error)) {
					    	printf("UnexpectedTokenError: Found stray '%c' near line %d, col %d.\n", line[i], lexer -> lineNum, lexer -> colNum);
						}

						add_element(toklist, create_token("\0\0\0", T_UNKNOWN, false));
						lexer -> error = true;
					}

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

			for (int i = lexer -> colNum; i < strlen(line); ++i) {
				// printf("%c", line[i]);
				lineBuf[lbidx] = line[i];
				++lbidx;
			}

			for (int i = strlen(lineBuf - 1); i > -1; ++i) {
				if (isalpha(lineBuf[i]) != 0) {
					break;
				} else if (lineBuf[i] == '"') {
					sq_reached = true;
					lineBuf[i + 1] = '\0';
					break;
				}
			}

			lineBuf[0] = 8;

			char finalLine[strlen(lineBuf)];
			strcpy(finalLine, lineBuf);
			free(lineBuf);

			finalLine[strlen(finalLine)] = '\0';

			char* liney = finalLine;

			add_element(toklist, create_token(liney, T_STR, false));

			if (!(sq_reached)) {
				printf("MissingEndOfStringError: Missing end quote near line %d, col %d\n", lexer -> lineNum, lexer -> colNum);
				lexer -> error = true;
			}
		}
		
		lexer -> colNum += strlen(part) + 1;
		part = strtok(NULL, " ");

		if (lexer -> error) {
			break;
		}
	}
}
