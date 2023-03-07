
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <string.h>

const int max = 1000;
char stack[max];
int tos = 0;

void push(int i)
{
	if (tos >= max) {
		printf ("Stack full\n"); return;
	}
	stack[tos] = i;
	tos++;
}

int pop(void)
{
	tos--;
	if (tos < 0) {
		printf("Stack empty\n"); return 0;
	}
	return stack[tos];
}

int priorCheck(char t)
{
	if (t == '(') return 0;
	else if (t == ')') return 1;
	else if (t == '+' || t == '-' || t == '|') return 2;
	else if (t == '*' || t == '/' || t == '&') return 3;
	else if (t == '^') return 4;
	else return 5;
}

void polishCow(char text[max], FILE* f)
{
	char result[max], finalResult[max];
	int i, k = 0, pR = 0, pS = 0;
	for (i = 0; text[i] != '\0'; i++) {
		pR = priorCheck(text[i]);
		if (text[i] == '\n') {}
		else if (text[i] == ' ' || isdigit(text[i]) || isalpha(text[i])) {
			result[k++] = text[i];
		}
		else if (tos == 0 || pR == 0) {
			push(text[i]);
			pS = pR;
		}
		else if (pR == 1) {
			while (pS != 0) {
				result[k++] = ' ';
				result[k++] = pop();
				result[k++] = ' ';
				pS = priorCheck(stack[tos - 1]);
			}
			pop();
		}
		else if (pR == pS) {
			result[k++] = pop();
			push(text[i]);
		}
		else if (tos != 0 && pS < pR) {
			push(text[i]);
			pS = pR;
		}
		else if (tos != 0 && pS > pR) {
			while (tos != 0 && pS >= pR) {
				result[k++] = pop();
				pS = priorCheck(stack[tos - 1]);
			}
			push(text[i]);
			pS = pR;
		}
	}
	while (tos != 0) {
		result[k++] = ' ';
		result[k++] = pop();
	}
	result[k] = '\0';
	k = 0;
	for (i = 0; result[i] != '\0'; i++)
		if (result[i] != ' ' && isdigit(result[i + 1])) {
			finalResult[k++] = result[i];
		}
		else if (result[i] != ' ') {
			finalResult[k++] = result[i];
			finalResult[k++] = ' ';
		}
	finalResult[k] = '\0';
	fprintf(f, "%s\n", finalResult);
	stack[0] = '\0';
	tos = 0;
	return;
}

int main()
{
	FILE * f1 = fopen("input.txt", "r"), * f2 = fopen("output.txt", "w");
	char text[max];
	if (f1 == NULL || f2 == NULL) {
		printf("File error");
		return 0;
	}
	while (fgets(text, max, f1))
		polishCow(text, f2);
	fclose(f1);
	fclose(f2);
	return 0;
}
