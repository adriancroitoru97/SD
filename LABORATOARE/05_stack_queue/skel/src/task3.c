#include <stdio.h>
#include <string.h>
#include "Stack.h"

int main()
{
	int ver = 1;
	char string[128];
	stack_t *st = st_create(sizeof(char));

	fgets(string, 128, stdin);
	for (int i = 0; i < strlen(string) - 1; i++) {
		if (string[i] == '(' || string[i] == '[' || string[i] == '{') {
			st_push(st, &string[i]);
		} else if (string[i] == ')' || string[i] == ']' || string[i] == '}') {
			if (i == 0) {
				ver = 0;
				break;
			}
			char current = *(char *)st_peek(st);
			if (string[i] == ')' && current != '(') {
				ver = 0;
				break;
			} else if (string[i] == ']' && current != '[') {
				ver = 0;
				break;
			} else if (string[i] == '}' && current != '{') {
				ver = 0;
				break;
			}
			st_pop(st);
		}
	}

	if (ver && st_is_empty(st))
		printf("Corect parantezat!\n");
	else
		printf("Gresit parantezat!\n");

	st_free(st);

	return 0;
}
