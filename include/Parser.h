#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "Token.h"
#include "AST.h"

#define MAX_BUFFER_SIZE 120


struct Parser {
	toklist_t tokenList;
	tok_t current_token;
	unsigned int colNum;
	uint32_t lineNum;
	uint64_t index;
};



struct AST_NODE** parseAndRun(struct Parser* parser, int* s);
struct Token parse_peek(struct Parser p, unsigned int offset);


#endif
