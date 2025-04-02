#ifndef TAXPAYER_H
#define TAXPAYER_H

#include <stdbool.h>
#include "Date.h"

struct TaxPayer {
	char name[35+1];
	struct Date dob;
	int w2_wages;
	int rental_income;
	int se_income; //Sch C, Sch E pg2
	bool eic_qualify;
};

bool taxpayers_are_equal(struct TaxPayer, struct TaxPayer);

void initialize_taxpayer(struct TaxPayer *, char[35+1]);

void add_wage_income(struct TaxPayer *, int);

void add_se_income(struct TaxPayer *, int);
#endif //TAXPAYER_H
