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

	strcat(linecpy, " EOL \0");
	linecpy[strlen(linecpy) - 6] = ' ';  // Removes newline.

	char* part = strtok(linecpy, " ");
	lexer -> curPart = part;
	lexer -> curChar = line[0];

	while (part != NULL) {
		if (strcmp(part, "print") == 0) {
			add_element(toklist, create_token(part, T_PRINT));
		} else if (strcmp(part, "let") == 0) {
			add_element(toklist, create_token(part, T_VAR_DEC));
		} else if (strchr(part, '"') != NULL) {
			bool sq_reached = false;

			add_element(toklist, create_token("\"", T_QUOTE));
			for (int i = lexer -> colNum + 1; i < strlen(line); ++i) {
				if (line[i] == '"') {
					sq_reached = true;
					break;
				}
			}

			if (!(sq_reached)) {
				printf("MissingEndOfStringError: Missing end quote.\n");
				lexer -> error = true;
			}
		}
	
		lexer -> colNum += strlen(part) + 1;

		part = strtok(NULL, " ");
	}
}
