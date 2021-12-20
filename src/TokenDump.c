#include "../include/TokenDump.h"



void dump_tokens(toklist_t token_list) {
	static bool ignore = true;  // Fixes false token bug.

	for (int i = 0; i < token_list.size; ++i) {
		switch (token_list.tokens[i].type) {
			case T_PRINT:
				if (!(ignore)) {
					printf("PRINT STATEMENT -> print\n");
				} else {
					ignore = false;
				}
				break;
			case T_VAR_DEC:
				printf("VAR DEC -> let\n");
				break;
			case T_INT:
				printf("INTEGER LITERAL -> %s\n", token_list.tokens[i].tok);
				break;
			case T_FLOAT:
				printf("FLOAT -> %s\n", token_list.tokens[i].tok);
				break;
			case T_STR:
				printf("STRING LITERAL -> %s\n", token_list.tokens[i].tok);
				break;
		}
	}
}
