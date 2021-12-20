#include "../include/Parser.h"


struct AST_NODE** parse(struct Parser* parser) {
	// struct AST_NODE** head_node = get_tree();
	bool ignore = true;

	for (int i = 0; i < parser -> tokenList.size; ++i) {
		switch (parser -> tokenList.tokens[i].type) {
			case T_PRINT:
				if (!(ignore)) {
					printf("PRINT\n");
				} else {
					ignore = false;
				}
		}
	}

	// ast_destroy(&head_node);
}


struct Token parse_peek(struct Parser p, unsigned int offset, toklist_t toklist) {
	return toklist.tokens[p.index + offset];
}
