#include "../include/Parser.h"


struct AST_NODE** parse(struct Parser* parser, int* s) {
	struct AST_NODE** head_node = get_tree();
	ast_init(head_node);
	bool ignore = true;

	for (int i = 0; i < parser -> tokenList.size; ++i) {
		switch (parser -> tokenList.tokens[i].type) {
			case T_PRINT:
				if (!(ignore)) {
					struct AST_NODE* node = (struct AST_NODE*)malloc(sizeof(struct AST_NODE));
					init_node(node, "type", "print-expression", 0, false);
					ast_insert(head_node, node, s);
				} else {
					ignore = false;
				}
		}
	}

	ast_destroy(&head_node, *s);
}


struct Token parse_peek(struct Parser p, unsigned int offset, toklist_t toklist) {
	return toklist.tokens[p.index + offset];
}
