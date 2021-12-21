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


struct AST_Collection {
	struct AST_NODE** nodes;
	size_t size;
	unsigned int pos;
};


struct AST_NODE** parseAndRun(struct Parser* parser, int* s);
struct Token parse_peek(struct Parser p, unsigned int offset);
void pushNode(struct AST_Collection* col, struct AST_NODE* node);
void destroy_ast_collection(struct AST_Collection* col);


#endif
