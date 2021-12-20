#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdbool.h>
#include "Token.h"
#include "AST.h"


struct Parser {
	toklist_t tokenList;
	tok_t current_token;
	unsigned int colNum;
	uint32_t lineNum;
	uint64_t index;
};



struct AST_NODE** parse(struct Parser*, int* s);

struct Token parse_peek(struct Parser p, unsigned int offset, toklist_t toklist);



#endif
