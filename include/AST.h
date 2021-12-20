#ifndef AST_H
#define AST_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define START_SIZE 10


struct AST_NODE {
	char* key;
	char* value;
	int32_t valueINT;
	uint32_t checksum;
	bool usingValueINT;
	struct AST_NODE* children;
};


struct AST_NODE** get_tree();
void init_ast(struct AST_NODE** nodes);
bool ast_insert(struct AST_NODE** dest, struct AST_NODE* src);
struct AST_NODE* ast_locate(struct AST_NODE** node, char key[]);
uint32_t ast_hash(char* key);
void init_node(struct AST_NODE* node, char* key, char* value, int32_t valueINT, bool uvi);
void ast_destroy(struct AST_NODE*** nodes);

#endif
