#include <stdio.h>

#include "Brackets.h"


void read_brackets()
{
	FILE *f = fopen(BRACKETS_TABLE, "r");

	if (f == NULL) { return; }

	for (int i = 0; i < 7; i++) {
		fscanf(f, "%f,%d", &brackets.tax_rate[i], &brackets.income_limit[i]);
	}
	fclose(f);
}
