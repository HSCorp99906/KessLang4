#include "../include/Parser.h"


struct AST_NODE** parseAndRun(struct Parser* parser, int* s) {
	struct AST_NODE** head_node = get_tree();
	struct AST_NODE* node;
	ast_init(head_node);
	bool ignore = true;  // Ignores print statements on first run.

	static int i = 0;
	static bool resetI = false;  // Will be used later to reset index.

	for (i = 0; i < parser->tokenList.size; ++i) {
		switch (parser->tokenList.tokens[i].type) {
			case T_PRINT:
				if (!(ignore)) {
					node = (struct AST_NODE*)malloc(sizeof(struct AST_NODE));
					init_node(node, "type", "print-expression", 0, false);
					ast_insert(head_node, node, s);


					node->child = (struct AST_NODE*)calloc(1, sizeof(struct AST_NODE));
					init_node(node->child, "argument", parse_peek(*parser, 2).tok, 0, false);
				} else {
					ignore = false;
				}
		}
	}

	if (strcmp(ast_locate(head_node, "type")->value, "print-expression") == 0) {
		struct AST_NODE* printNode = ast_locate(head_node, "type");
		printf("%s\n", printNode->child->value);
	}

	free(node->child);
	ast_destroy(&head_node, *s);
}


struct Token parse_peek(struct Parser p, unsigned int offset) {
	return p.tokenList.tokens[p.index + offset];
}
