#include "../include/Parser.h"


struct AST_NODE** parseAndRun(struct Parser* parser, int* s) {
	struct AST_NODE** head_node = get_tree();
	struct AST_NODE* node;
	ast_init(head_node);
	bool ignore = true;

	static int i = 0;
	static bool resetI = false;

	for (i = 0; i < parser -> tokenList.size; ++i) {
		switch (parser -> tokenList.tokens[i].type) {
			case T_PRINT:
				if (!(ignore)) {
					node = (struct AST_NODE*)malloc(sizeof(struct AST_NODE));
					init_node(node, "type", "print-expression", 0, false);
					ast_insert(head_node, node, s);

					char* stringBuf = (char*)malloc(sizeof(char) * 30);
					
					/*
					node -> children = (struct AST_NODE*)calloc(1, sizeof(struct AST_NODE));
				
					init_node(node -> children, "argument", "poop", 0, false);
					printf("%s\n", node -> children -> value);

					free(node -> children);
					*/

					free(stringBuf);

				} else {
					ignore = false;
				}
		}
	}

	ast_destroy(&head_node, *s);
}


struct Token parse_peek(struct Parser p, unsigned int offset) {
	return p.tokenList.tokens[p.index + offset];
}
