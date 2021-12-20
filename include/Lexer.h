#ifndef LEXER_H
#define LEXER_H

#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "Token.h"


struct Lexer {
	uint32_t lineNum;
	uint32_t colNum;
	char* curPart;
	char curChar;
	bool error;
};


toklist_t tokenize(toklist_t* toklist, struct Lexer* lexer, char* line);

char* peek(struct Lexer* lexer, int offset, char* line);


void advance(struct Lexer* lexer, char* line);

#endif
