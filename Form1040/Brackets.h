#ifndef BRACKETS_H
#define BRACKETS_H

#define BRACKETS_TABLE "tables/brackets.txt"


struct Brackets {
	float tax_rate[7];
	int income_limit[7];
};

extern struct Brackets brackets;

void read_brackets();
#endif //BRACKETS_H
