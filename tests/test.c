#include <string.h>
#include <stdio.h>


int main() {
	const char* const str = "Hello World";
	char split[30][30];

	unsigned int ssidx = 0;
	unsigned int sidx = 0;

	for (int i = 0; i < strlen(str); ++i) {
		if (str[i] == ' ') {
			++ssidx;
			sidx = 0;
			continue;
		}

		split[ssidx][sidx] = str[i]; 
		++sidx;
	}

	split[ssidx][strlen(split[ssidx]) - 3] = '\0';

	printf("%s", split[1]);
}
