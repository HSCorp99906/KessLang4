#include "../include/Parser.h"

void pushNode(struct AST_Collection* col, struct AST_NODE* node) {
	static bool started = true;
	col->pos = 1;

	if (started) {
		started = false;
		col->nodes = (struct AST_NODE**)malloc(sizeof(struct AST_NODE*) * 10);
		col->size = 10;
	} else if (col->pos >= col->size - 3) {
		col->size += 5;
		col->nodes = (struct AST_NODE**)realloc(col->nodes, sizeof(struct AST_NODE*) * col->size);
	}

	
	col->nodes[col->pos - 1] = node;
	++col->pos;

}


void destroy_ast_collection(struct AST_Collection* col) {
	for (int i = 0; i < col->pos; ++i) {
		free(col->nodes[i]);
	}

	free(col->nodes);
	col->nodes = NULL;
}

struct AST_NODE** parseAndRun(struct Parser* parser, int* s) {
	struct AST_NODE** head_node = get_tree();
	struct AST_NODE* node;
	ast_init(head_node);
	bool ignore = true;  // Ignores print statements on first run.

	static int i = 0;
	static bool resetI = false;

	for (i = 0; i < parser->tokenList.size; ++i) {
		switch (parser->tokenList.tokens[i].type) {
			case T_PRINT:
				if (!(ignore)) {
					node = (struct AST_NODE*)malloc(sizeof(struct AST_NODE));
					init_node(node, "type", "print-expression", 0, false);
					ast_insert(head_node, node, s);


					node->children = (struct AST_NODE*)calloc(1, sizeof(struct AST_NODE));
					init_node(node->children, "argument", parse_peek(*parser, 2).tok, 0, false);
				} else {
					ignore = false;
				}
		}
	}

	if (strcmp(ast_locate(head_node, "type")->value, "print-expression") == 0) {
		struct AST_NODE* printNode = ast_locate(head_node, "type");
		printf("%s\n", printNode->children->value);
	}

	free(node->children);
	ast_destroy(&head_node, *s);
}


struct Token parse_peek(struct Parser p, unsigned int offset) {
	return p.tokenList.tokens[p.index + offset];
}
